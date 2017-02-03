#include <fstream>
#include <iostream>
#include <cstdint>
#include "DMGCPU.h"
#include "MEM.h"
#include "GPU.h"
//#include "Emulator.h"

using namespace std;

/*
uint8_t cart[0x8000];
uint8_t sram[0x2000];
uint8_t io[0x100];

uint8_t vram[0x2000];	//8k video ram
uint8_t oam[0x100];
uint8_t wram[0x2000];
uint8_t hram[0x80];
*/

MEM::MEM(){
	//load rom
	//loadRom("test.gb");
	//run bios
	//load bios into memory
	for (int i = 0; i < 256; i++) {
		rom[0][i] = BIOS[i];
	}
	
	biosLoaded = 1;
}

MEM::~MEM() {}





uint8_t MEM::ReadByte(uint16_t addr){
	
	if (addr >= 0x0000 && addr <= 0x3FFF)		//permanent rom bank
		return rom[0][addr];
		//return rom[0][addr];
	
	else if(addr >= 0x4000 && addr <= 0x7FFF)	//Area of switchable rom banks
		return rom[activeRomBank-1][addr];
		
	else if(addr >= 0x8000 && addr <= 0x9FFF)	//read from video ram
		return vram[addr-0x8000];
	
	else if(addr >= 0xA000 && addr <= 0xBFFF)	//read from external ram
		return eram[addr-0xA000];	
	
	else if(addr >= 0xC000 && addr <= 0xCFFF)	//read from work ram
		return wram[addr-0xC000];
		
	else if(addr >= 0xD000 && addr <= 0xDFFF)
		return bram[activeRomBank][addr-0xD000];
	
	else if(addr >= 0xE000 && addr <= 0xEFFF)	//mirror of work ram
		return wram[addr-0xE000];
		
	else if(addr >= 0xF000 && addr <= 0xFDFF)
		return bram[activeRomBank][addr-0xF000];

	else if(addr >= 0xFE00 && addr <= 0xFE9F)	//Sprite attribute table
		return oam[addr-0xFE00];
	
	else if(addr >= 0xFF00 && addr <= 0xFF7F)	//I/O registers
		return zram[addr-0xFF00];
	
	else if(addr >= 0xFF80 && addr <= 0xFFFE)	//High Ram (stack)
		return hram[addr-0xFF80];
	
	else if(addr == 0xFFFF)						//Interrupts enable register
		return intFlag;
	
	return 0;
}

uint16_t MEM::ReadWord(uint16_t addr){
	return (ReadByte(addr) | (ReadByte(addr+1) << 8)); 
}

void MEM::WriteByte(uint16_t addr, uint8_t data){
	if(addr < 0x8000)		//signals bank switch
		handleBanking(addr, data);
		
	else if(addr == 0xFF04)	//if written to, sets it to 0
		zram[0x0004] = 0;
	
	else if (addr >= 0xFEA0 && addr < 0xFEFF)	//read only stuff
		return;

	else if (addr >= 0x8000 && addr <= 0x9FFF)	//write to video ram
		vram[addr - 0x2000] = data;
	
	else if(addr >= 0xA000 && addr <= 0xBFFF)	//write to external ram
		eram[addr-0xA000] = data;	
	
	else if(addr >= 0xC000 && addr <= 0xDFFF)	//write to work ram
		wram[addr-0xC000] = data;
	
	else if(addr >= 0xE000 && addr <= 0xFDFF)	//mirror of work ram
		wram[addr-0xE000] = data;

	else if(addr >= 0xFE00 && addr <= 0xFE9F)	//Sprite attribute table
		oam[addr-0xFE00] = data;
	
	else if(addr >= 0xFF80 && addr <= 0xFFFE)	//High Ram (stack)
		hram[addr-0xFF80] = data;
	
	else if(addr == 0xFFFF)						//Interrupts enable register
		intEnable = data;
	
	else if(addr == 0xFF0F)
		intFlag = data;
	
	else if(addr >= 0xFF00 && addr <= 0xFF7F)	//I/O registers
		zram[addr-0xFF00] = data;
		
	return;
}

void MEM::WriteWord(uint16_t addr, uint16_t data){
	WriteByte(addr, (data & 0xFF));
	WriteByte(addr+1, (data >> 8));
}

void MEM::handleBanking(uint16_t addr, uint8_t data){
	//Enabling ram
	if(addr < 0x2000)
		if(romBankType)
			RAMBankEnable(addr, data);
	
	//Rom bank change
	else if(addr >= 0x2000 && addr < 0x4000)
		if(romBankType)
			ChangeLoRomBank(data);
	
	//do ROM or RAM bank change
	else if(addr >= 0x4000 && addr < 0x6000)
		if(romBankType == 1)
			ChangeHiRomBank(data);
		else	
			RamBankChange(data);
	
	else if(addr >= 0x6000 && addr < 0x8000)
		if(romBankType == 1)
			ChangeROMRAMMode(data);
}

void MEM::RAMBankEnable(uint16_t addr, uint8_t data){
	uint8_t temp;
	
	if(romBankType == 2)
		if(addr >> 4 & 1)	//find function
			return;
	
	temp = data & 0xF;
	
	if(temp == 0xA)
		ramEnable = 1;	
	else if(temp == 0x0)
		ramEnable = 0;	
}

void MEM::ChangeLoRomBank(uint8_t data){
	uint8_t temp;
	
	if(romBankType == 2){
		activeRomBank = data & 0xF;
		if(activeRomBank == 0){
			activeRomBank ++;
			return;
		}
	}
	
	temp = data & 31;
	activeRomBank &= 224;
	activeRomBank |= temp;
	
	if(activeRomBank == 0)
		activeRomBank ++;
}

void MEM::ChangeHiRomBank(uint8_t data){
	activeRomBank &= 31;
	
	data &= 224;
	activeRomBank |= data;
	if(activeRomBank == 0)
		activeRomBank ++;
}

void MEM::RamBankChange(uint8_t data){
	activeRAmBank = data & 0x3;
}

void MEM::ChangeROMRAMMode(uint8_t data){
	uint8_t temp;
	
	temp = data & 0x1;
	
	if(!data)
		activeRAmBank = 0;
}

void MEM::loadRom(string filename){
	fstream file(filename, ios::in | ios::binary | ios::ate);
	streampos size;
	uint8_t romType, ramSize, numBanks, i, k;
	char * buffer;
	uint16_t rombank;
	unsigned long fileLen;
	
	if (file.is_open()) {
		size = file.tellg();
		buffer = new char[size];
		file.seekg(0, ios::beg);
		file.read(buffer, size);
		file.close();
		cout << "File contents in memory" << endl;
	}
	else {
		cout << "Error opening file" << endl;
		return;
	}

	
	switch(buffer[0x0147]){
		case 1:
			romBankType = 1;
			break;
		case 2:
			romBankType = 1;
			break;		
		case 3:
			romBankType = 1;
			break;		
		case 5:
			romBankType = 2;
			break;		
		case 6:
			romBankType = 2;
			break;		
	}
	
	
	switch(buffer[0x0148]){		//Get ROM size		
		case 0x00:		//2 banks
			numBanks = 2;
			break;
		case 0x01:		//4 banks
			numBanks = 4;
			break;
		case 0x02:		//8 banks
			numBanks = 8;
			break;		
		case 0x03:		//16 banks
			numBanks = 16;
			break;		
		case 0x04:		//32 banks
			numBanks = 32;
			break;		
		case 0x05:		//64 banks
			numBanks = 64;
			break;		
		case 0x06:		//128 banks
			numBanks = 128;
			break;		
		case 0x07:		//256 banks
			numBanks = 255;
			break;		
		case 0x52:	//72 banks
			numBanks = 72;
			break;		
		case 0x53:	//80 banks
			numBanks = 80;
			break;		
		case 0x54:	//96 banks
			numBanks = 96;
			break;		
	}
	
	for(k = 0; k < numBanks; k++)	//copy rom data into banks
		for(i = 0; i<4000; i++)
			rom[k][i] = buffer[i+(k*0x4000)];

	switch(buffer[0x0149]){	//get RAM size
		case 0x00:		//none
			break;
		case 0x01:		//16kbit
			ramBankSize = 1;
			break;
		case 0x02:		//64kbit
			ramBankSize = 1;
			break;		
		case 0x03:		//256kbit
			ramBankSize = 4;
			break;		
		case 0x04:		//1Mbit
			ramBankSize = 16;
			break;		
		default: break;
	}
	
	delete [] buffer;
}

void MEM::pushtoStack(uint16_t addr){
	uint8_t hi;
	uint8_t lo;
	
	hi = addr >> 8;
	lo = addr & 0xFF;
	stackPointer--;
	WriteByte(stackPointer, hi);
	stackPointer--;
	WriteByte(stackPointer, lo);
}

uint16_t MEM::popoffStack(){
	uint16_t temp;
	temp = ReadByte(stackPointer+1) << 8;
	temp |= ReadByte(stackPointer);
	stackPointer += 2;
	
	return temp;	
}





















