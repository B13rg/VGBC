#include <stdio.h>
#include <cstdint>
#include "../include/Emulator.h"
#include "../include/mem.h"
#include "../include/gpu.h"
#include "../include/cpu.h"


using namespace std;

Emulator::Emulator(){
	mem = new MEM();
	Cpu = new CPU(mem);
	gpu = new GPU(mem);
	cyclesThisUpdate = 0;
	timerCounter = 1024;
	//platform();
}

Emulator::~Emulator() {}

void Emulator::platform(){

}

void Emulator::update(uint8_t * pixels){

	
	while(cyclesThisUpdate < MAXCYCLES){
		//ExecuteNextOpcode
		Cpu->tick();
		cyclesThisUpdate += Cpu->getClock();
		updateTimers(cyclesThisUpdate);
		//gpu->Tick(cyclesThisUpdate, pixels);
		doInterupts();
	}

	mem->WriteByte(0xFF00, 0);	//reset controller input

	//gpu->get_Texture(pixels);
}

void Emulator::updateTimers(int cycles){
	uint8_t temp;
	
	DoDividerRegister(cycles);
	
	if(true){	//clock enabled
		timerCounter -= cycles;
		if(timerCounter <= 0){
			setClockFreq();
			temp = mem->ReadByte(0xFF05);
			
			if(temp == 255){
				mem->WriteByte(0xFF05, 255);
				requestInterrupt(2);
			} else
				mem->WriteByte(0xFF05, temp+1);
		}
	}
	
}

void Emulator::DoDividerRegister(int cycles){
	dividerCounter += cycles;
	
	if(dividerCounter >= 255){
		dividerCounter = 0;
		mem->WriteByte(0xFF04, mem->ReadByte(0xFF04)+1);
	}
}

void Emulator::setClockFreq(){
	uint8_t freq;
	
	freq = mem->ReadByte(0xFF07 & 0x3);
	
	switch(freq){
		case 0:
			timerCounter = 1024;
			break;
		case 1:
			timerCounter = 16;
			break;
		case 2:
			timerCounter = 64;
			break;
		case 3:
			timerCounter = 256;
			break;
	}
}

void Emulator::requestInterrupt(int id){
	uint8_t req;
	
	req = mem->ReadByte(0xFF0F);
	req = req << id;
	mem->WriteByte(0xFF0F, req);
}

void Emulator::doInterupts(){
	uint8_t req, enabled;
	
	req = mem->ReadByte(0xFF0F);
	enabled = mem->ReadByte(0xFFFF);
	
	if(req)
		for(int i =0; i < 5; i++)
			if((req >> i) & 1)
				if((enabled >> i) & 1)
					serviceInterrupt(i);
}

void Emulator::serviceInterrupt(int interrupt){
	uint8_t req;
		
	interruptMaster = 0;
	req = mem->ReadByte(0xFF0F);
	
	req |= 0 << interrupt;
	
	mem->WriteByte(0xFF0F, req);
	
	mem->pushtoStack(Cpu->getPC());
	
	switch(interrupt){
		case 0:		//V-Blank
			Cpu->setPC(0x40);
			break;
		case 1:		//LCD
			Cpu->setPC(0x48);
			break;
		case 2:		//Timer
			Cpu->setPC(0x50);
			break;
		case 4:		//Joypad
			Cpu->setPC(0x60);
			break;
	}
}