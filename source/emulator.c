#include "Emulator.h"
#include "MEM.h"
#include "GPU.h"
#include "DMGCPU.h"
Emulator::Emulator(){
	cyclesThisUpdate = 0;
	timerCounter = 1024;
	c_MEM mem;
	CPU cpu;
}


void Emulator::update(){
	int cycles;
	
	while(cyclesThisUpdate < MAXCYCLES){
		ExecuteNextOpcode();
		cyclesThisUpdate += getClock();
		updateTimers(cycles);
		updateGraphics(cycles);
		doInterupts();
	}
	RenderScreen();
}

void Emulator::updateTimers(int cycles){
	uint8_t temp;
	
	DoDividerRegister();
	
	if(clock_enabled){
		timerCounter -= cycles;
		if(timerCounter <= 0){
			setClockFreq();
			temp = mem.ReadByte(0xFF05);
			
			if(temp == 255){
				mem.WriteByte(0xFF05, 255);
				requestInterrupt(2);
			} else
				WriteByte(0xFF05, temp+1)
		}
	}
	
}

void Emulator::DoDividerRegister(){
	dividerRegister += cycles;
	
	if(dividerCounter >= 255){
		dividerCounter = 0;
		mem.WriteByte(0xFF04, mem.ReadByte(0xFF04)+1);
	}
}

void Emulator::setClockFreq(){
	uint8_t freq;
	
	freq = mem.ReadByte(0xFF07 & 0x3)
	
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

void requestInterrupt(int id){
	uint8_t = req;
	
	req = mem.ReadByte(0xFF0F);
	req = req << id;
	mem.WriteByte(0xFF0F, req);
}

void doInterupts(){
	uint8_t req, enabled;
	
	req = mem.ReadByte(0xFF0F);
	enabled = mem.ReadByte(0xFFFF);
	
	if(req)
		for(i =0; i < 5; i++)
			if((req >> i) & 1)
				if((enabled >> i) & 1)
					serviceInterrupt(i);
}

void serviceInterrupt(int interrupt){
	uint8_t req;
		
	interruptMaster = 0;
	req = mem.ReadByte(0xFF0F);
	
	req |= 0 << interrupt;
	
	mem.WriteByte(0xFF0F, req);
	
	pushtoStack(cpu.getPC());
	
	switch(interrupt){
		case 0:		//V-Blank
			cpu.setPC(0x40);
			break;
		case 1:		//LCD
			cpu.setPC(0x48);
			break;
		case 2:		//Timer
			cpu.setPC(0x50);
			break;
		case 4:		//Joypad
			cpu.setPC(0x60);
			break;
	}
}