#include "DMGCPU.h"
#include "MEM.h"

/*
uint8_t cart[0x8000];
uint8_t sram[0x2000];
uint8_t io[0x100];

uint8_t vram[0x2000];	//8k video ram
uint8_t oam[0x100];
uint8_t wram[0x2000];
uint8_t hram[0x80];
*/

const uint8_t BIOS[0x100] = {
0x31, 0xFE, 0xFF, 0xAF, 0x21, 0xFF, 0x9F, 0x32, 0xCB, 0x7C, 0x20, 0xFB, 0x21, 0x26, 0xFF, 0x0E, 0x11, 0x3E, 0x80, 0x32, 0xE2, 0x0C, 0x3E, 0xF3, 0xE2, 0x32, 0x3E, 0x77, 0x77, 0x3E, 0xFC, 0xE0, 0x47, 0x11, 0x04, 0x01, 0x21, 0x10, 0x80, 0x1A, 0xCD, 0x95, 0x00, 0xCD, 0x96, 0x00, 0x13, 0x7B, 0xFE, 0x34, 0x20, 0xF3, 0x11, 0xD8, 0x00, 0x06, 0x08, 0x1A, 0x13, 0x22, 0x23, 0x05, 0x20, 0xF9, 0x3E, 0x19, 0xEA, 0x10, 0x99, 0x21, 0x2F, 0x99, 0x0E, 0x0C, 0x3D, 0x28, 0x08, 0x32, 0x0D, 0x20, 0xF9, 0x2E, 0x0F, 0x18, 0xF3, 0x67, 0x3E, 0x64, 0x57, 0xE0, 0x42, 0x3E, 0x91, 0xE0, 0x40, 0x04, 0x1E, 0x02, 0x0E, 0x0C, 0xF0, 0x44, 0xFE, 0x90, 0x20, 0xFA, 0x0D, 0x20, 0xF7, 0x1D, 0x20, 0xF2, 0x0E, 0x13, 0x24, 0x7C, 0x1E, 0x83, 0xFE, 0x62, 0x28, 0x06, 0x1E, 0xC1, 0xFE, 0x64, 0x20, 0x06, 0x7B, 0xE2, 0x0C, 0x3E, 0x87, 0xE2, 0xF0, 0x42, 0x90, 0xE0, 0x42, 0x15, 0x20, 0xD2, 0x05, 0x20, 0x4F, 0x16, 0x20, 0x18, 0xCB, 0x4F, 0x06, 0x04, 0xC5, 0xCB, 0x11, 0x17, 0xC1, 0xCB, 0x11, 0x17, 0x05, 0x20, 0xF5, 0x22, 0x23, 0x22, 0x23, 0xC9, 0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E, 0x3C, 0x42, 0xB9, 0xA5, 0xB9, 0xA5, 0x42, 0x3C, 0x21, 0x04, 0x01, 0x11, 0xA8, 0x00, 0x1A, 0x13, 0xBE, 0x20, 0xFE, 0x23, 0x7D, 0xFE, 0x34, 0x20, 0xF5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20, 0xFB, 0x86, 0x20, 0xFE, 0x3E, 0x01, 0xE0, 0x50};


c_MEM::c_MEM(){
	biosLoaded = 0;
	memcpy(cartReset, BIOS, sizeof(cartReset));	//load bios into memory
	//load rom
	//run bios
	biosLoaded = 1;
	
	stackPointer = 0xFFFE;
}

c_MEM::~c_MEM();

uint8_t c_MEM::ReadByte(uint16_t addr){
	
	if(addr >= 0x0000 && addr <= 0x3FFF)		//permanent rom bank
		return rom[0][addr];
	
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

uint16_t c_MEM::ReadWord(uint16_t addr){
	return (ReadByte(addr) | (ReadByte(addr+1) << 8)); 
}

void c_MEM::WriteByte(uint16_t addr, uint8_t data){
	if(addr < 0x8000)		//signals bank switch
		handleBanking(addr, data);
		
	else if(addr == 0xFF04)	//if written to, sets it to 0
		zram[0x0004] = 0;
	
	else if(addr >= 0xFEA0 && addr < 0xFEFF)	//read only stuff
		return 0;
	
	else if(addr >= 0x8000 && addr <= 0x9FFF)	//write to video ram
		vram[addr-0x8000] = data;
	
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
		
	return 0;
}

void c_MEM::WriteWord(uint16_t addr, uint16_t data){
	WriteByte(addr, (data & 0xFF));
	WriteByte(addr+1, (data >> 8));
}

void c_MEM::handleBanking(uint16_t addr, uint8_t data){
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
	
	else if(address >= 0x6000 && address < 0x8000)
		if(romBankType == 1)
			ChangeROMRAMMode(data);
}

void c_MEM::RAMBankEnable(uint16_t addr, uint8_t data){
	uint8_t temp;
	
	if(romBankType == 2)
		if(addr >> 4 & 1)	//find function
			return 0;
	
	temp = data & 0xF;
	
	if(temp == 0xA)
		ramEnable = 1;	
	else if(temp == 0x0)
		ramEnable = 0;	
}

void c_MEM::ChangeLoRomBank(uint8_t data){
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

void c_MEM::ChangeHiRomBank(uint8_t data){
	activeRomBank &= 31;
	
	data &= 224;
	activeRomBank |= data;
	if(activeRomBank == 0)
		activeRomBank ++;
}

void c_MEM::RamBankChange(uint8_t data){
	activeRAmBank = data & 0x3;
}

void c_MEM::ChangeROMRAMMode(uint8_t data){
	uint8_t temp;
	
	temp = data & 0x1;
	
	if(!data)
		activeRAmBank = 0;
}

void c_MEM::loadRom(const char *fname){
	FILE *f;
	uint8_t *buffer, romType, ramSize, numBanks, i,k;
	uint16_t rombank;
	unsigned long fileLen;
	
	f = fopen(fname, "rb");
	if(f==NULL){
		//file error
		return 1;
	}
	fseek(f, 0, SEEK_END);
	fileLen = ftell(f);
	fseek(f, 0, SEEK_SET);
	
	buffer = (uint8_t *)malloc(fileLen+1);
	assert(buffer);
	
	fread(buffer, fileLen, 1, f);
	fclose(file);
	
	switch(buffer[]){
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
			numBanks = 256;
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
	
	free(buffer);
}

void c_MEM::pushtoStack(uint16_t word){
	uint8_t hi;
	uint8_t lo;
	
	hi = addr >> 8;
	lo = addr & 0xFF;
	stackPointer.reg--;
	WriteByte(stackPointer, hi);
	stackPointer.reg--;
	WriteByte(stackPointer, lo);
}

uint16_t c_MEM::popoffStack(){
	uint16_t temp;
	temp = ReadByte(stackPointer+1) << 8;
	temp |= ReadByte(stackPointer);
	stackPointer += 2;
	
	return temp;	
}





















