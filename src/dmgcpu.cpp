#include <stdio.h>
#include <cstdint>
#include DMGCPU.h
#include "Emulator.h"
#include "MEM.h"
#include "GPU.h"


using namespace std;


CPU::CPU(MEM* MEM){
	mem = MEM;
	opCodeInit();
	tick();
}


CPU::~CPU();

void CPU::tick();

CPU::uint32_t getClock(){
	return Clock.m;
}

CPU::uint16_t getPC();







/*
Counter = InterruptPeriod
PC = InitialPC

for(;){
	//Fetch instruction
	Opcode = Memory[PC++];
	Counter -= Cycles[OpCode];
	
	//decode and execute instruction
	
	
	if(Counter <= 0){
		// check for interrupts
		// cyclic tasks
		//
		Counter += InterruptPeriod;
		if(ExitRequired) break;
	}
}
*/

void CPU::resetFlags(){	//sets all flags to zero
	Flag.Z = 0;
	Flag.N = 0;
	Flag.H = 0;
	Flag.C = 0;
}

void CPU::opCodeInit(){	//sets up OpCode connections
	opCodes[0x00] = &CPU::opCode0x00;
    opCodes[0x01] = &CPU::opCode0x01;
    opCodes[0x02] = &CPU::opCode0x02;
    opCodes[0x03] = &CPU::opCode0x03;
    opCodes[0x04] = &CPU::opCode0x04;
    opCodes[0x05] = &CPU::opCode0x05;
    opCodes[0x06] = &CPU::opCode0x06;
    opCodes[0x07] = &CPU::opCode0x07;
    opCodes[0x08] = &CPU::opCode0x08;
    opCodes[0x09] = &CPU::opCode0x09;
    opCodes[0x0A] = &CPU::opCode0x0A;
    opCodes[0x0B] = &CPU::opCode0x0B;
    opCodes[0x0C] = &CPU::opCode0x0C;
    opCodes[0x0D] = &CPU::opCode0x0D;
    opCodes[0x0E] = &CPU::opCode0x0E;
    opCodes[0x0F] = &CPU::opCode0x0F;
    opCodes[0x10] = &CPU::opCode0x10;
    opCodes[0x11] = &CPU::opCode0x11;
    opCodes[0x12] = &CPU::opCode0x12;
    opCodes[0x13] = &CPU::opCode0x13;
    opCodes[0x14] = &CPU::opCode0x14;
    opCodes[0x15] = &CPU::opCode0x15;
    opCodes[0x16] = &CPU::opCode0x16;
    opCodes[0x17] = &CPU::opCode0x17;
    opCodes[0x18] = &CPU::opCode0x18;
    opCodes[0x19] = &CPU::opCode0x19;
    opCodes[0x1A] = &CPU::opCode0x1A;
    opCodes[0x1B] = &CPU::opCode0x1B;
    opCodes[0x1C] = &CPU::opCode0x1C;
    opCodes[0x1D] = &CPU::opCode0x1D;
    opCodes[0x1E] = &CPU::opCode0x1E;
    opCodes[0x1F] = &CPU::opCode0x1F;
    opCodes[0x20] = &CPU::opCode0x20;
    opCodes[0x21] = &CPU::opCode0x21;
    opCodes[0x22] = &CPU::opCode0x22;
    opCodes[0x23] = &CPU::opCode0x23;
    opCodes[0x24] = &CPU::opCode0x24;
    opCodes[0x25] = &CPU::opCode0x25;
    opCodes[0x26] = &CPU::opCode0x26;
    opCodes[0x27] = &CPU::opCode0x27;
    opCodes[0x28] = &CPU::opCode0x28;
    opCodes[0x29] = &CPU::opCode0x29;
    opCodes[0x2A] = &CPU::opCode0x2A;
    opCodes[0x2B] = &CPU::opCode0x2B;
    opCodes[0x2C] = &CPU::opCode0x2C;
    opCodes[0x2D] = &CPU::opCode0x2D;
    opCodes[0x2E] = &CPU::opCode0x2E;
    opCodes[0x2F] = &CPU::opCode0x2F;
    opCodes[0x30] = &CPU::opCode0x30;
    opCodes[0x31] = &CPU::opCode0x31;
    opCodes[0x32] = &CPU::opCode0x32;
    opCodes[0x33] = &CPU::opCode0x33;
    opCodes[0x34] = &CPU::opCode0x34;
    opCodes[0x35] = &CPU::opCode0x35;
    opCodes[0x36] = &CPU::opCode0x36;
    opCodes[0x37] = &CPU::opCode0x37;
    opCodes[0x38] = &CPU::opCode0x38;
    opCodes[0x39] = &CPU::opCode0x39;
    opCodes[0x3A] = &CPU::opCode0x3A;
    opCodes[0x3B] = &CPU::opCode0x3B;
    opCodes[0x3C] = &CPU::opCode0x3C;
    opCodes[0x3D] = &CPU::opCode0x3D;
    opCodes[0x3E] = &CPU::opCode0x3E;
    opCodes[0x3F] = &CPU::opCode0x3F;
    opCodes[0x40] = &CPU::opCode0x40;
    opCodes[0x41] = &CPU::opCode0x41;
    opCodes[0x42] = &CPU::opCode0x42;
    opCodes[0x43] = &CPU::opCode0x43;
    opCodes[0x44] = &CPU::opCode0x44;
    opCodes[0x45] = &CPU::opCode0x45;
    opCodes[0x46] = &CPU::opCode0x46;
    opCodes[0x47] = &CPU::opCode0x47;
    opCodes[0x48] = &CPU::opCode0x48;
    opCodes[0x49] = &CPU::opCode0x49;
    opCodes[0x4A] = &CPU::opCode0x4A;
    opCodes[0x4B] = &CPU::opCode0x4B;
    opCodes[0x4C] = &CPU::opCode0x4C;
    opCodes[0x4D] = &CPU::opCode0x4D;
    opCodes[0x4E] = &CPU::opCode0x4E;
    opCodes[0x4F] = &CPU::opCode0x4F;
    opCodes[0x50] = &CPU::opCode0x50;
    opCodes[0x51] = &CPU::opCode0x51;
    opCodes[0x52] = &CPU::opCode0x52
    opCodes[0x53] = &CPU::opCode0x53;
    opCodes[0x54] = &CPU::opCode0x54;
    opCodes[0x55] = &CPU::opCode0x55;
    opCodes[0x56] = &CPU::opCode0x56;
    opCodes[0x57] = &CPU::opCode0x57;
    opCodes[0x58] = &CPU::opCode0x58;
    opCodes[0x59] = &CPU::opCode0x59;
    opCodes[0x5A] = &CPU::opCode0x5A;
    opCodes[0x5B] = &CPU::opCode0x5B;
    opCodes[0x5C] = &CPU::opCode0x5C;
    opCodes[0x5D] = &CPU::opCode0x5D;
    opCodes[0x5E] = &CPU::opCode0x5E;
    opCodes[0x5F] = &CPU::opCode0x5F;
    opCodes[0x60] = &CPU::opCode0x60;
    opCodes[0x61] = &CPU::opCode0x61;
    opCodes[0x62] = &CPU::opCode0x62;
    opCodes[0x63] = &CPU::opCode0x63;
    opCodes[0x64] = &CPU::opCode0x64;
    opCodes[0x65] = &CPU::opCode0x65;
    opCodes[0x66] = &CPU::opCode0x66;
    opCodes[0x67] = &CPU::opCode0x67;
    opCodes[0x68] = &CPU::opCode0x68;
    opCodes[0x69] = &CPU::opCode0x69;
    opCodes[0x6A] = &CPU::opCode0x6A;
    opCodes[0x6B] = &CPU::opCode0x6B;
    opCodes[0x6C] = &CPU::opCode0x6C;
    opCodes[0x6D] = &CPU::opCode0x6D;
    opCodes[0x6E] = &CPU::opCode0x6E;
    opCodes[0x6F] = &CPU::opCode0x6F;
    opCodes[0x70] = &CPU::opCode0x70;
    opCodes[0x71] = &CPU::opCode0x71;
    opCodes[0x72] = &CPU::opCode0x72;
    opCodes[0x73] = &CPU::opCode0x73;
    opCodes[0x74] = &CPU::opCode0x74;
    opCodes[0x75] = &CPU::opCode0x75;
    opCodes[0x76] = &CPU::opCode0x76;
    opCodes[0x77] = &CPU::opCode0x77;
    opCodes[0x78] = &CPU::opCode0x78;
    opCodes[0x79] = &CPU::opCode0x79;
    opCodes[0x7A] = &CPU::opCode0x7A;
    opCodes[0x7B] = &CPU::opCode0x7B;
    opCodes[0x7C] = &CPU::opCode0x7C;
    opCodes[0x7D] = &CPU::opCode0x7D;
    opCodes[0x7E] = &CPU::opCode0x7E;
    opCodes[0x7F] = &CPU::opCode0x7F;
    opCodes[0x80] = &CPU::opCode0x80;
    opCodes[0x81] = &CPU::opCode0x81;
    opCodes[0x82] = &CPU::opCode0x82;
    opCodes[0x83] = &CPU::opCode0x83;
    opCodes[0x84] = &CPU::opCode0x84;
    opCodes[0x85] = &CPU::opCode0x85;
    opCodes[0x86] = &CPU::opCode0x86;
    opCodes[0x87] = &CPU::opCode0x87;
    opCodes[0x88] = &CPU::opCode0x88;
    opCodes[0x89] = &CPU::opCode0x89;
    opCodes[0x8A] = &CPU::opCode0x8A;
    opCodes[0x8B] = &CPU::opCode0x8B;
    opCodes[0x8C] = &CPU::opCode0x8C;
    opCodes[0x8D] = &CPU::opCode0x8D;
    opCodes[0x8E] = &CPU::opCode0x8E;
    opCodes[0x8F] = &CPU::opCode0x8F;
    opCodes[0x90] = &CPU::opCode0x90;
    opCodes[0x91] = &CPU::opCode0x91;
    opCodes[0x92] = &CPU::opCode0x92;
    opCodes[0x93] = &CPU::opCode0x93;
    opCodes[0x94] = &CPU::opCode0x94;
    opCodes[0x95] = &CPU::opCode0x95;
    opCodes[0x96] = &CPU::opCode0x96;
    opCodes[0x97] = &CPU::opCode0x97;
    opCodes[0x98] = &CPU::opCode0x98;
    opCodes[0x99] = &CPU::opCode0x99;
    opCodes[0x9A] = &CPU::opCode0x9A;
    opCodes[0x9B] = &CPU::opCode0x9B;
    opCodes[0x9C] = &CPU::opCode0x9C;
    opCodes[0x9D] = &CPU::opCode0x9D;
    opCodes[0x9E] = &CPU::opCode0x9E;
    opCodes[0x9F] = &CPU::opCode0x9F;
    opCodes[0xA0] = &CPU::opCode0xA0;
    opCodes[0xA1] = &CPU::opCode0xA1;
    opCodes[0xA2] = &CPU::opCode0xA2;
    opCodes[0xA3] = &CPU::opCode0xA3;
    opCodes[0xA4] = &CPU::opCode0xA4;
    opCodes[0xA5] = &CPU::opCode0xA5;
    opCodes[0xA6] = &CPU::opCode0xA6;
    opCodes[0xA7] = &CPU::opCode0xA7;
    opCodes[0xA8] = &CPU::opCode0xA8;
    opCodes[0xA9] = &CPU::opCode0xA9;
    opCodes[0xAA] = &CPU::opCode0xAA;
    opCodes[0xAB] = &CPU::opCode0xAB;
    opCodes[0xAC] = &CPU::opCode0xAC;
    opCodes[0xAD] = &CPU::opCode0xAD;
    opCodes[0xAE] = &CPU::opCode0xAE;
    opCodes[0xAF] = &CPU::opCode0xAF;
    opCodes[0xB0] = &CPU::opCode0xB0;
    opCodes[0xB1] = &CPU::opCode0xB1;
    opCodes[0xB2] = &CPU::opCode0xB2;
    opCodes[0xB3] = &CPU::opCode0xB3;
    opCodes[0xB4] = &CPU::opCode0xB4;
    opCodes[0xB5] = &CPU::opCode0xB5;
    opCodes[0xB6] = &CPU::opCode0xB6;
    opCodes[0xB7] = &CPU::opCode0xB7;
    opCodes[0xB8] = &CPU::opCode0xB8;
    opCodes[0xB9] = &CPU::opCode0xB9;
    opCodes[0xBA] = &CPU::opCode0xBA;
    opCodes[0xBB] = &CPU::opCode0xBB;
    opCodes[0xBC] = &CPU::opCode0xBC;
    opCodes[0xBD] = &CPU::opCode0xBD;
    opCodes[0xBE] = &CPU::opCode0xBE;
    opCodes[0xBF] = &CPU::opCode0xBF;
    opCodes[0xC0] = &CPU::opCode0xC0;
    opCodes[0xC1] = &CPU::opCode0xC1;
    opCodes[0xC2] = &CPU::opCode0xC2;
    opCodes[0xC3] = &CPU::opCode0xC3;
    opCodes[0xC4] = &CPU::opCode0xC4;
    opCodes[0xC5] = &CPU::opCode0xC5;
    opCodes[0xC6] = &CPU::opCode0xC6;
    opCodes[0xC7] = &CPU::opCode0xC7;
    opCodes[0xC8] = &CPU::opCode0xC8;
    opCodes[0xC9] = &CPU::opCode0xC9;
    opCodes[0xCA] = &CPU::opCode0xCA;
    
	//CB switch function goes here
		
    opCodes[0xCC] = &CPU::opCode0xCC;
    opCodes[0xCD] = &CPU::opCode0xCD;
    opCodes[0xCE] = &CPU::opCode0xCE;
    opCodes[0xCF] = &CPU::opCode0xCF;
    opCodes[0xD0] = &CPU::opCode0xD0;
    opCodes[0xD1] = &CPU::opCode0xD1;
    opCodes[0xD2] = &CPU::opCode0xD2;
    opCodes[0xD3] = NULL;
    opCodes[0xD4] = &CPU::opCode0xD4;
    opCodes[0xD5] = &CPU::opCode0xD5;
    opCodes[0xD6] = &CPU::opCode0xD6;
    opCodes[0xD7] = &CPU::opCode0xD7;
    opCodes[0xD8] = &CPU::opCode0xD8;
    opCodes[0xD9] = &CPU::opCode0xD9;
    opCodes[0xDA] = &CPU::opCode0xDA;
    opCodes[0xDB] = NULL;
    opCodes[0xDC] = &CPU::opCode0xDC;
    opCodes[0xDD] = NULL;
    opCodes[0xDE] = &CPU::opCode0xDE;
    opCodes[0xDF] = &CPU::opCode0xDF;
    opCodes[0xE0] = &CPU::opCode0xE0;
    opCodes[0xE1] = &CPU::opCode0xE1;
    opCodes[0xE2] = &CPU::opCode0xE2;
    opCodes[0xE3] = NULL;
    opCodes[0xE4] = NULL;
    opCodes[0xE5] = &CPU::opCode0xE5;
    opCodes[0xE6] = &CPU::opCode0xE6;
    opCodes[0xE7] = &CPU::opCode0xE7;
    opCodes[0xE8] = &CPU::opCode0xE8;
    opCodes[0xE9] = &CPU::opCode0xE9;
    opCodes[0xEA] = &CPU::opCode0xEA;
    opCodes[0xEB] = NULL;
    opCodes[0xEC] = NULL;
    opCodes[0xED] = NULL;
    opCodes[0xEE] = &CPU::opCode0xEE;
    opCodes[0xEF] = &CPU::opCode0xEF;
    opCodes[0xF0] = &CPU::opCode0xF0;
    opCodes[0xF1] = &CPU::opCode0xF1;
    opCodes[0xF2] = &CPU::opCode0xF2;
    opCodes[0xF3] = &CPU::opCode0xF3;
    opCodes[0xF4] = NULL;
    opCodes[0xF5] = &CPU::opCode0xF5;
    opCodes[0xF6] = &CPU::opCode0xF6;
    opCodes[0xF7] = &CPU::opCode0xF7;
    opCodes[0xF8] = &CPU::opCode0xF8;
    opCodes[0xF9] = &CPU::opCode0xF9;
    opCodes[0xFA] = &CPU::opCode0xFA;
    opCodes[0xFB] = &CPU::opCode0xFB;
    opCodes[0xFC] = NULL;
    opCodes[0xFD] = NULL;
    opCodes[0xFE] = &CPU::opCode0xFE;
    opCodes[0xFF] = &CPU::opCode0xFF;

    //CB opcode table need to implement fully
    uint8_t i;
    for(i = 0; i < 0xFF; i++){
        opCodesCB[i] = NULL;
    }
    opCodesCB[0x11] = &CPU::OPCodeCB0x11;
    opCodesCB[0x17] = &CPU::OPCodeCB0x17;
    opCodesCB[0x23] = &CPU::OPCodeCB0x23;
    opCodesCB[0x27] = &CPU::OPCodeCB0x27;
    opCodesCB[0x33] = &CPU::OPCodeCB0x33;
    opCodesCB[0x37] = &CPU::OPCodeCB0x37;
    opCodesCB[0x38] = &CPU::OPCodeCB0x38;
    opCodesCB[0x3F] = &CPU::OPCodeCB0x3F;
    opCodesCB[0x40] = &CPU::OPCodeCB0x40;
    opCodesCB[0x41] = &CPU::OPCodeCB0x41;
    opCodesCB[0x47] = &CPU::OPCodeCB0x47;
    opCodesCB[0x50] = &CPU::OPCodeCB0x50;
    opCodesCB[0x5F] = &CPU::OPCodeCB0x5F;
    opCodesCB[0x67] = &CPU::OPCodeCB0x67;
    opCodesCB[0x6F] = &CPU::OPCodeCB0x6F;
    opCodesCB[0x77] = &CPU::OPCodeCB0x77;
    opCodesCB[0x7C] = &CPU::OPCodeCB0x7C;
    opCodesCB[0x7E] = &CPU::OPCodeCB0x7E;
    opCodesCB[0x7F] = &CPU::OPCodeCB0x7F;
    opCodesCB[0x86] = &CPU::OPCodeCB0x86;
    opCodesCB[0x87] = &CPU::OPCodeCB0x87;
    opCodesCB[0xFE] = &CPU::OPCodeCB0xFE;

}

void CPU::*opCodes[0xFF](void);
void CPU::*opCodesCB[0xFF](void);
/* Opcode Function Structure
void CPU::opCode0x##(){; Function; Cycles
	Do the opcode function

	Set flags 

	Set instruction size
	Set instruction cycles
	Increment instruction pointer
} */

void CPU::opCode0x00(){//NOP; 4
	Clock.m = 1;	//instruction size ??
	Clock.t = 4;	//Number of cycles
	Registers.PC.word ++;  //size of instruction, 1 byte
}

void CPU::opCode0x01(){ //LD BC, d16; 12
	Registers.BC.word = MEM->Readword(Registers.PC.word + 1);

	Clock.m = 3;
	Clock.t = 12;
	Registers.PC.word += 3;
}

void CPU::opCode0x02(){ //LD (BC), A; 8
	MEM->Writeword(Registers.BC.word, Registers.AF.hi);

	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;	
}

void CPU::opCode0x03(){ //INC BC; 8
	Registers.BC.word ++;

	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;	
}

void CPU::opCode0x04(){ //INC B; 4
	Registers.BC.hi ++;

	Flag.N =0;

	if(!Registers.BC.hi)
		Flag.Z = 1;
	if(Registers.BC.hi & 0xF)
		Flag.H = 0;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x05(){ //DEC B; 4
	Registers.BC.hi --;

	Flag.N = 1;
	if(!Registers.BC.hi)
		Flag.Z = 1;
	if(Registers.BC.hi & 0xF)
		Flag.H = 0;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;	
}

void CPU::opCode0x06(){ //LD B, d8; 8
	Registers.BC.hi = MEM->ReadByte(Registers.PC.word + 1);
	
	Clock.m =2;
	Clock.t = 8;
	Registers.PC.word += 2;
}

void CPU::opCode0x07(){ //RLCA; 4
	// Needs to be tested
	uint8_t carryi = (Registers.AF.hi >> 7) & 1;	//check if Carry flag is set

	resetFlags();	//reset all flags

	Registers.AF.hi = (Registers.AF.hi << 1);	//shift bits left 1 spot
	Registers.AF.hi |= carryi;
	Flag.C = carryi;
	
	Clock.m = 1;
	Clock.c = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x08(){ //LD (a16), SP; 20
	MEM->Writeword(Registers.SP.word, MEM->ReadWord(Registers.PC.word + 1));
	
	Clock.m = 3;
	Clock.t = 20;
	Registers.PC.word += 3;
}

void CPU::opCode0x09(){	//ADD HL, BC; 8
	Flag.N = 0;
	Flag.H = 0;
	Flag.C = 0;
	
	if(((Registers.HL.word & 0x0FFF)+(Registers.BC.word & 0x0FFF))> 0x0FFF)
		Flag.H = 1;
	if((Registers.HL.word + Registers.BC.word ) > 0x0FFF)
		Flag.C = 1;
	
	Registers.HL.word += Registers.BC.word;
	
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void CPU::opCode0x0A(){ //LD A, (BC); 8
	Registers.AF.hi = MEM->ReadByte(Registers.BC.word);

	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void CPU::opCode0x0B(){ //DEC BC; 8
	Registers.BC.word --;
	
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void CPU::opCode0x0C(){ //INC C; 4
	Registers.BC.lo ++;
	
	Flag.N = 0;
	
	if(Registers.BC.lo == 0)
		Flag.Z =1;
	if(Registers.BC.lo > 0x0FFF)
		Flag.H = 1;
	
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x0D(){ //DEC C; 4
	Registers.BC.lo --;
	
	Flag.N = 1;
	
	if(Registers.BC.lo == 0)
		Flag.Z =1;
	if(Registers.BC.lo > 0x0FFF)
		Flag.C = 1;
	
	Clock.m = 1;
	Clock.t 4;
	Registers.PC.word ++;
}

void CPU::opCode0x0E(){ //LD C, d8; 8
	Registers.BC.lo = MEM->ReadByte(Registers.PC.word + 1);
	
	Clock.m = 2;
	Clock.t = 8;
	Registers.PC.word += 2;
}

void CPU::opCode0x0F(){ //RRCA; 4
	uint8_t carryi = (Registers.AF.hi >> 0) & 1;	//get 7th bit of A register

	resetFlags();	//reset all flags

	Registers.AF.hi = (Registers.AF.hi >>> 1);	//shift bits right 1 spot
	Registers.AF.hi |= carryi;
	Flag.C = carryi;
	
	Clock.m = 1;
	Clock.c = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x10(){	//STOP 0; 4
	while(Registers.AF.hi == 0 || MEM->ReadByte(0xFF00) == 0);
	
	Clock.m = 1;
	Clock.t = 4;
	
	if(MEM->ReadByte(Registers.PC.word + 1) == 0x00)
		Registers.PC.word += 2;
	else
		Registers.PC.word ++;
}

void CPU::opCode0x11(){	//LD DE, D16; 12
	Registers.DE.word = MEM->Readword(Registers.PC.word + 1);

	Clock.m = 3;
	Clock.t = 12;
	Registers.PC.word += 3;
}

void CPU::opCode0x12(){	//LD (DE), A; 8
	MEM->Writeword(Registers.DE.word, Registers.AF.hi);

	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void CPU::opCode0x13(){	//INC DE; 8
	Registers.DE.word ++;

	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void CPU::opCode0x14(){	//INC D; 4
	Registers.DE.hi ++;
	
	Flag.N = 0;
	
	if(Registers.DE.hi == 0)
		Flag.Z =1;
	if(Registers.DE.hi > 0x0FFF)
		Flag.H = 1;
	
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x15(){	//DEC D; 4
	Registers.DE.hi --;

	Flag.N = 1;
	
	if(!Registers.DE.hi)
		Flag.Z = 1;
	if(Registers.DE.hi & 0xF)
		Flag.H = 0;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x16(){	//LD D, D8; 8
	Registers.DE.hi = MEM->ReadByte(registers.PC.word + 1);
	
	Clock.m = 2;
	Clock.t = 8;
	Registers.PC.word += 2;
}

void CPU::opCode0x17();//RLA; 4
void CPU::opCode0x18(){	//JR r8; 12
	Registers.PC.word += (uint8_t)(MEM->ReadByte(Registers.PC.word + 1)) + 2;
	Clock.m = 2;
	Clock.t = 12;
}

void CPU::opCode0x19(){	//ADD HL, DE; 8
	Flag.N = 0;
	Flag.H = 0;
	Flag.C = 0;
	
	if(((Registers.HL.word & 0x0FFF)+(Registers.DE.word & 0x0FFF))> 0x0FFF)
		Flag.H = 1;
	if((Registers.HL.word + Registers.DE.word ) > 0x0FFF)
		Flag.C = 1;
	
	Registers.HL.word += Registers.DE.word;
	
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void CPU::opCode0x1A(){	//LD A, (DE); 8
	Registers.AF.hi = MEM->ReadByte(Registers.DE.word);

	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void CPU::opCode0x1B(){//DEC DE; 8
	Registers.DE.word --;
	
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void CPU::opCode0x1C(){	//INC E; 4
	Registers.DE.lo ++;
	
	Flag.N = 0;
	
	if(Registers.DE.lo == 0)
		Flag.Z =1;
	if(Registers.DE.lo > 0x0FFF)
		Flag.H = 1;
	
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x1D(){	//DEC E; 4
	Registers.DE.lo --;

	Flag.N = 1;
	
	if(!Registers.DE.lo)
		Flag.Z = 1;
	if(Registers.DE.lo & 0xF)
		Flag.H = 0;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x1E(){	//LD E, d8; 8
	Registers.DE.lo = MEM->ReadByte(Registers.PC.word + 1);
	
	Clock.m = 2;
	Clock.t = 8;
	Registers.PC.word += 2;
}

void CPU::opCode0x1F();//RRA; 4

void CPU::opCode0x20(){	//JR NZ, r8; 12/8
	Clock.m = 2;
	Clock.t = 8;
	if(!Flag.Z){
		Registers.PC.word += (uint8_t)(MEM->ReadByte(Registers.PC.word + 1)) + 2;
		Clock.t = 12;
	}
}

void CPU::opCode0x21(){	//LD HL, d16; 12
	Registers.HL.word = MEM->Readword(Registers.PC.word + 1);

	Clock.m = 3;
	Clock.t = 12;
	Registers.PC.word += 3;
}

void CPU::opCode0x22(){	//LD(HL+), A; 8
	MEM->WriteByte(Registers.HL.word, Registers.AF.hi);
	Registers.GL.word ++;
	
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void CPU::opCode0x23(){	//INC HL; 8
	Registers.HL.word ++;

	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void CPU::opCode0x24(){	//INC H; 4
	Registers.HL.hi ++;
	
	Flag.N = 0;
	
	if(Registers.HL.hi == 0)
		Flag.Z =1;
	if(Registers.HL.hi > 0x0FFF)
		Flag.H = 1;
	
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x25(){	//DEC H; 4
	Registers.HL.hi --;

	Flag.N = 1;
	
	if(!Registers.HL.hi)
		Flag.Z = 1;
	if(Registers.HL.hi & 0xF)
		Flag.H = 0;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x26(){	//LD H, d8; 8
	Registers.HL.hi = MEM->ReadByte(Registers.PC.word + 1);
	
	Clock.m = 2;
	Clock.t = 8;
	Registers.PC.word += 2;
}

void CPU::opCode0x27(){	//DAA; 4
	uint8_t value = Registers.AF.hi;
	
	//addition portion
	if(!Flag.N){
		if((value & 0x0F)  > 9)
			value = value + 6;
		if((value > 0x9F) || (Flag.C)){
			value = value + 0x60;
			Flag.C = 1;
		}	else 
			Flag.C = 0;
	} else {	//subtraction portion
		if((value & 0x0F)  > 9 || Flag.H){
			value -= 6;
		}
		if((value > 0x9H) || Flag.C){
			value -= 0x60;
			Flag.C = 1;
		}	else
			Flag.C = 0;
	}
	
	Registers.AH.hi = value);
	
	//final flag setting
	Flag.H = 0;
	Flag.Z = 0;
	
	if(value == 0)
		Flag.Z = 1;
	
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x28(){	//JR Z, r8; 12/8
	Clock.m = 2;
	Clock.t = 8;
	
	if(Flag.Z){
		Registers.PC.word += (uint8_t)(MEM->ReadByte(Registers.PC.word + 1)) + 2;
		Clock.t = 12;
	}
}

void CPU::opCode0x29(){	//ADD HL, HL; 8
	Flag.N = 0;
	Flag.H = 0;
	Flag.C = 0;
	
	if(((Registers.HL.word & 0x0FFF) * 2)> 0x0FFF)
		Flag.H = 1;
	if((Registers.HL.word * 2) > 0x0FFF)
		Flag.C = 1;
	
	Registers.HL.word *= 2;
	
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void CPU::opCode0x2A(){	//LD A, (HL+); 8
	Registers.AF.hi = MEM->ReadByte(Registers.HL.word);
	Registers.HL.word ++;
	
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++; 
}

void CPU::opCode0x2B(){	//DEC HL; 8
	Registers.HL.word --;
	
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void CPU::opCode0x2C(){	//INC L; 4
	Registers.HL.lo ++;
	
	Flag.N = 0;
	
	if(Registers.HL.lo == 0)
		Flag.Z =1;
	if(Registers.HL.lo > 0x0FFF)
		Flag.H = 1;
	
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x2D(){	//DEC L; 4
	Registers.HL.lo --;

	Flag.N = 1;
	
	if(!Registers.HL.lo)
		Flag.Z = 1;
	if(Registers.HL.lo & 0xF)
		Flag.H = 0;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x2E(){	//LD L, d8; 8
	Registers.HL.lo = MEM->Readbyte(Registers.PC.word + 1);
	
	Clock.m = 2;
	Clock.t = 8;
	Registers.PC.word += 2;	
}

void CPU::opCode0x2F(){	//CPL; 4
	Registers.AH.hi ^= 0xFF;
	
	Flag.N = 1;
	Flag.H =1;
	
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x30(){	//JR NC, r8; 12/8
		Clock.m = 2;
	Clock.t = 8;
	
	if(!Flag.C){
		Registers.PC.word += (uint8_t)(MEM->ReadByte(Registers.PC.word + 1)) + 2;
		Clock.t = 12;
	}
}

void CPU::opCode0x31(){	//LD SP, d16; 12
	Registers.SP.word = MEM->Readword(Registers.PC.word + 1);

	Clock.m = 3;
	Clock.t = 12;
	Registers.PC.word += 3;
}

void CPU::opCode0x32(){	//LD (HL-), A; 8
	MEM->WriteByte(Registers.HL.word, Registers.AF.hi);
	Registers.HL.word --;
	
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++; 
}

void CPU::opCode0x33(){	//INC SP; 8
	Registers.SP.word ++;

	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void CPU::opCode0x34(){	//INC (HL); 12
	uint8_t value = MEM->ReadByte(Registers.HL.word);
	value ++;
		
	Flag.N = 0;
	
	if(value == 0)
		Flag.Z =1;
	if(value > 0x0FFF)
		Flag.H = 1;
	
	MEM->WriteByte(Registers.HL.word, value);
	
	Clock.m = 1;
	Clock.t = 12;
	Registers.PC.word ++;
}

void CPU::opCode0x35(){	//DEC (HL); 12
MEM->ReadByte(
	uint8_t value = MEM->ReadByte(Registers.HL.word);
	
	value --;
	
	MEM->WriteByte(Registers.HL.word, value);

	Flag.N = 1;
	
	if(!value)
		Flag.Z = 1;
	if(value & 0xF)
		Flag.H = 0;

	Clock.m = 1;
	Clock.t = 12;
	Registers.PC.word ++;
}

void CPU::opCode0x36(){	//LD (HL), d8; 12
	MEM->WriteByte(Registers.HL.word, MEM->ReadByte(Registers.PC.word + 1));
	
	Clock.m = 2;
	Clock.t = 12;
	Registers.PC.word += 2;
}

void CPU::opCode0x37(){	//SCF; 4
	Flag.C = 1;
	Flag.N = 0;
	Flag.H = 0;
	
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word = 1;
}

void CPU::opCode0x38(){	//JR C, r8; 12/8
	Clock.m = 2;
	Clock.t = 8;
	
	if(Flag.C){
		Registers.PC.word += (uint8_t)(MEM->ReadByte(Registers.PC.word + 1)) + 2;
		Clock.t = 12;
	}
}

void CPU::opCode0x39(){	//ADD HL, SP; 8
	Flag.N = 0;
	Flag.H = 0;
	Flag.C = 0;
	
	if(((Registers.HL.word & 0x0FFF)+(Registers.SP.word & 0x0FFF))> 0x0FFF)
		Flag.H = 1;
	if((Registers.HL.word + Registers.SP.word ) > 0x0FFF)
		Flag.C = 1;
	
	Registers.HL.word += Registers.SP.word;
	
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void CPU::opCode0x3A(){	//LD A, (HL-); 8
	Registers.AF.hi = MEM->Readbyte(Registers.HL.word);
	Registers.HL.word--;
	
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void CPU::opCode0x3B(){	//DEC SP; 8
	Registers.SP.word --;
	
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void CPU::opCode0x3C(){	//INC A; 4
	Registers.AF.hi ++;
	
	Flag.N = 0;
	
	if(Registers.AF.hi == 0)
		Flag.Z =1;
	if(Registers.AF.hi > 0x0FFF)
		Flag.H = 1;
	
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x3D(){	//DEC A; 4
	Registers.AF.hi --;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;

	Flag.F = 0;
	Flag.H = 0;
	Flag.N = 1;

	if(!Registers.AF.hi)
		Flag.F = 1;	//set zero flag
	if(Registers.AF.hi & 0xF)
		Flag.H = 1;	//set half carry
}

void CPU::opCode0x3E(){	//LD A, d8; 8
	Registers.AF.hi = MEM->ReadByte(Registers.PC.word + 1);
	Clock.m =2;
	Clock.t = 8;
	Registers.PC.word += 2;
}

void CPU::opCode0x3F(){	//CCF; 4
	Flag.C ^= 1;
	
	Flag.N = 0;
	Flag.H =0;
	
	Clock.m = 1
	Clock.t = 4;
	Registers.PC.word += 1;
}

/************************************/
void CPU::opCode0x40();//LD B, B; 4
void CPU::opCode0x41();//LD B, C; 4
void CPU::opCode0x42();//LD B, D; 4
void CPU::opCode0x43();//LD B, E; 4
void CPU::opCode0x44();//LD B, H; 4
void CPU::opCode0x45();//LD B, L; 4
void CPU::opCode0x46();//LD B, (HL); 8
void CPU::opCode0x47();//LD B, A; 4
void CPU::opCode0x48();//LD C, B; 4
void CPU::opCode0x49();//LD C, C; 4
void CPU::opCode0x4A();//LD C, D; 4
void CPU::opCode0x4B();//LD C, E; 4
void CPU::opCode0x4C();//LD C, H; 4
void CPU::opCode0x4D();//LD C, L; 4
void CPU::opCode0x4E();//LD C, (HL); 8
void CPU::opCode0x4F();//LD C, A; 4

void CPU::opCode0x50();//LD D, B; 4
void CPU::opCode0x51();//LD D, C; 4
void CPU::opCode0x52();//LD D, D; 4
void CPU::opCode0x53();//LD D, E; 4
void CPU::opCode0x54();//LD D, H; 4
void CPU::opCode0x55();//LD D, L; 4
void CPU::opCode0x56();//LD D, (HL); 8
void CPU::opCode0x57();//LD D, A; 4
void CPU::opCode0x58();//LD E, B; 4
void CPU::opCode0x59();//LD E, C; 4
void CPU::opCode0x5A();//LD E, D; 4
void CPU::opCode0x5B();//LD E, E; 4
void CPU::opCode0x5C();//LD E, H; 4
void CPU::opCode0x5D();//LD E, L; 4
void CPU::opCode0x5E();//LD E, (HL); 8
void CPU::opCode0x5F();//LD E, A; 4

void CPU::opCode0x60();//LD H, B; 4
void CPU::opCode0x61();//LD H, C; 4
void CPU::opCode0x62();//LD H, D; 4
void CPU::opCode0x63();//LD H, E; 4
void CPU::opCode0x64();//LD H, H; 4
void CPU::opCode0x65();//LD H, L; 4
void CPU::opCode0x66();//LD H, (HL); 8
void CPU::opCode0x67();//LD H, A; 4
void CPU::opCode0x68();//LD L, B; 4
void CPU::opCode0x69();//LD L, C; 4
void CPU::opCode0x6A();//LD L, D; 4
void CPU::opCode0x6B();//LD L, E; 4
void CPU::opCode0x6C();//LD L, H; 4
void CPU::opCode0x6D();//LD L, L; 4
void CPU::opCode0x6E();//LD L, (HL); 8
void CPU::opCode0x6F();//LD L, A; 4

void CPU::opCode0x70();//LD (HL), B; 8
void CPU::opCode0x71();//LD (HL), C; 8
void CPU::opCode0x72();//LD (HL), D; 8
void CPU::opCode0x73();//LD (HL), E; 8
void CPU::opCode0x74();//LD (HL), H; 8
void CPU::opCode0x75();//LD (HL), L; 8
void CPU::opCode0x76();//HALT; 4
void CPU::opCode0x77(){	//LD (HL), A; 8
	MEM->Writeword(Registers.HL.word, Registers.AF.hi);

	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void CPU::opCode0x78(){	//LD A, B; 4
	Registers.AF.hi = Registers.BC.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x79(){	//LD A, C; 4
	Registers.AF.hi = Registers.BC.lo;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x7A(){	//LD A, D; 4
	Registers.AF.hi = Registers.DE.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x7B(){	//LD A, E; 4
	Registers.AF.hi = Registers.DE.lo;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x7C(){	//LD A, H; 4
	Registers.AF.hi = Registers.HL.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x7D(){	//LD A, L; 4
	Registers.AF.hi = Registers.HL.lo;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x7E(){	//LD A, (HL); 8
	Registers.AF.hi = Registers.HL.word;

	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void CPU::opCode0x7F(){	//LD A, A; 4
	Registers.AF.hi = Registers.AF.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x80();//ADD A, B; 4
void CPU::opCode0x81();//ADD A, C; 4
void CPU::opCode0x82();//ADD A, D; 4
void CPU::opCode0x83();//ADD A, E; 4
void CPU::opCode0x84();//ADD A, H; 4
void CPU::opCode0x85();//ADD A, L; 4
void CPU::opCode0x86();//ADD A, (HL); 8
void CPU::opCode0x87();//ADD A, A; 4
void CPU::opCode0x88();//ADC A, B; 4
void CPU::opCode0x89();//ADC A, C; 4
void CPU::opCode0x8A();//ADC A, D; 4
void CPU::opCode0x8B();//ADC A, E; 4
void CPU::opCode0x8C();//ADC A, H; 4
void CPU::opCode0x8D();//ADC A, L; 4
void CPU::opCode0x8E();//ADC A, (HL); 8
void CPU::opCode0x8F();//ADC A, A; 4

void CPU::opCode0x90();//SUB B; 4
void CPU::opCode0x91();//SUB C; 4
void CPU::opCode0x92();//SUB D; 4
void CPU::opCode0x93();//SUB E; 4
void CPU::opCode0x94();//SUB H; 4
void CPU::opCode0x95();//SUB L; 4
void CPU::opCode0x96();//SUB (HL); 8
void CPU::opCode0x97();//SUB A; 4
void CPU::opCode0x98();//SBC A, B; 4
void CPU::opCode0x99();//SBC A, C; 4
void CPU::opCode0x9A();//SBC A, D; 4
void CPU::opCode0x9B();//SBC A, E; 4
void CPU::opCode0x9C();//SBC A, H; 4
void CPU::opCode0x9D();//SBC A, L; 4
void CPU::opCode0x9E();//SBC A, (HL); 8
void CPU::opCode0x9F();//SBC A, A; 4

void CPU::opCode0xA0();//AND B; 4
void CPU::opCode0xA1();//AND C; 4
void CPU::opCode0xA2();//AND D; 4
void CPU::opCode0xA3();//AND E; 4
void CPU::opCode0xA4();//AND H; 4
void CPU::opCode0xA5();//AND L; 4
void CPU::opCode0xA6();//AND (HL); 8
void CPU::opCode0xA7();//AND A; 4
void CPU::opCode0xA8();//XOR B; 4
void CPU::opCode0xA9();//XOR C; 4
void CPU::opCode0xAA();//XOR D; 4
void CPU::opCode0xAB();//XOR E; 4
void CPU::opCode0xAC();//XOR H; 4
void CPU::opCode0xAD();//XOR L; 4
void CPU::opCode0xAE();//XOR (HL); 8
void CPU::opCode0xAF();//XOR A; 4

void CPU::opCode0xB0();//OR B; 4
void CPU::opCode0xB1();//OR C; 4
void CPU::opCode0xB2();//OR D; 4
void CPU::opCode0xB3();//OR E; 4
void CPU::opCode0xB4();//OR H; 4
void CPU::opCode0xB5();//OR L; 4
void CPU::opCode0xB6();//OR (HL); 8
void CPU::opCode0xB7();//OR A; 4
void CPU::opCode0xB8();//CP B; 4
void CPU::opCode0xB9();//CP C; 4
void CPU::opCode0xBA();//CP D; 4
void CPU::opCode0xBB();//CP E; 4
void CPU::opCode0xBC();//CP H; 4
void CPU::opCode0xBD();//CP L; 4
void CPU::opCode0xBE();//CP (HL); 8
void CPU::opCode0xBF();//CP A; 4

void CPU::opCode0xC0();//RET NZ; 20/8
void CPU::opCode0xC1();//POP BC; 12
void CPU::opCode0xC2(){	//JP NZ, a16; 16
	Clock.t = 12;
	
	if(Flag.Z == 0){
		Registers.PC.word = MEM->Readword(Registers.PC.word + 1);
		Clock.t = 16;
	}
	
	Clock.m = 3
}

void CPU::opCode0xC3(){	//JP a16; 16
	Registers.PC.word = MEM->ReadWord(Registers.PC.word+1);
	Clock.m = 3;
	Clock.t = 16;
}

void CPU::opCode0xC4();//CALL NZ, a16
void CPU::opCode0xC5();//PUSH BC
void CPU::opCode0xC6();//ADD A, d8
void CPU::opCode0xC7();//RST 00H; 16
void CPU::opCode0xC8();//RET Z; 20/8
void CPU::opCode0xC9();//RET; 16
void CPU::opCode0xCA(){	//JP Z, a16; 16/12
	Clock.t = 12;
	
	if(Flag.Z == 1){
		Registers.PC.word = MEM->Readword(Registers.PC.word + 1);
		Clock.t = 16;
	}
	
	Clock.m = 3
}

void CPU::opCode0xCB();//PREFIX CB; 4
void CPU::opCode0xCC();//CALL Z, a16; 24/12
void CPU::opCode0xCD();//CALL a16; 24
void CPU::opCode0xCE();//ADC A, d8; 8
void CPU::opCode0xCF();//RST 08H; 16

void CPU::opCode0xD0();//RET NC; 20/8
void CPU::opCode0xD1();//POP DE; 12
void CPU::opCode0xD2(){	//JP NC, a16; 16/12
	Clock.t = 12;
	
	if(Flag.C == 0){
		Registers.PC.word = MEM->Readword(Registers.PC.word + 1);
		Clock.t = 16;
	}
	
	Clock.m = 3
}

//void CPU::opCode0xD3();//BLANK
void CPU::opCode0xD4();//CALL NC, a16; 24/12
void CPU::opCode0xD5();//PUSH DE; 16
void CPU::opCode0xD6();//SUB d8; 8
void CPU::opCode0xD7();//RST 10H; 16
void CPU::opCode0xD8();//RET C; 20/8
void CPU::opCode0xD9();//RETI; 16
void CPU::opCode0xDA(){	//JP C, a16; 16/12
	Clock.t = 12;
	
	if(Flag.C == 1){
		Registers.PC.word = MEM->Readword(Registers.PC.word + 1);
		Clock.t = 16;
	}
	
	Clock.m = 3
}

//void CPU::opCode0xDB();//BLANK
void CPU::opCode0xDC();//CALL C, a16; 24/12
//void CPU::opCode0xDD();//BLANK
void CPU::opCode0xDE();//SBC A, d8; 8
void CPU::opCode0xDF();//RST 18H; 16

void CPU::opCode0xE0();//LDH (a8), A; 12
void CPU::opCode0xE1();//POP HL; 12
void CPU::opCode0xE2();//LD (C), A; 8
//void CPU::opCode0xE3();//BLANK
//void CPU::opCode0xE4();//BLANK
void CPU::opCode0xE5();//PUSH HL; 16
void CPU::opCode0xE6();//AND d8; 8
void CPU::opCode0xE7();//RST 20H; 16
void CPU::opCode0xE8(){	//ADD SP, r8; 16
	uint8_t value = MEM->ReadByte(Registers.PC.word+1);
	
	Flag.Z = 0;
	Flag.N = 0;
		
	if(((Registers.SP.word & 0x0FFF)+(value & 0x0FFF))> 0x0FFF)
		Flag.H = 1;
	if((Registers.SP.word + value ) > 0x0FFF)
		Flag.C = 1;
	
	Registers.SP.word += value;
	
	Clock.m = 2;
	Clock.t = 16;
	Registers.PC.word += 2;
}

void CPU::opCode0xE9();//JP (HL); 4
void CPU::opCode0xEA();//LD (a16), A; 16
//void CPU::opCode0xEB();//BLANK
//void CPU::opCode0xEC();//BLANK
//void CPU::opCode0xED();//BLANK
void CPU::opCode0xEE();//XOR d8; 8
void CPU::opCode0xEF();//RST 28H; 16

void CPU::opCode0xF0();//LDH A, (a8); 12
void CPU::opCode0xF1();//POP AF; 12
void CPU::opCode0xF2();//LD A, (C); 8
void CPU::opCode0xF3();//DI; 4
//void CPU::opCode0xF4();//BLANK
void CPU::opCode0xF5();//PUSH AF; 16
void CPU::opCode0xF6();//OR d8; 8
void CPU::opCode0xF7();//RST 30H; 16
void CPU::opCode0xF8();//LD HL, SP+r8; 12
void CPU::opCode0xF9();//LD SP, HL; 8
void CPU::opCode0xFA();//LD A, (a16); 16
void CPU::opCode0xFB();//EI; 4
//void CPU::opCode0xFC();//BLANK
//void CPU::opCode0xFD();//BLANK
void CPU::opCode0xFE();//CP d8; 8
void CPU::opCode0xFF();//RST 38H; 16