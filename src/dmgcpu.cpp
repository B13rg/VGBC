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
    opCodes[0x52] = &CPU::opCode0x52;
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

    //
	//Start of CB table
	//

	opCodesCB[0x00] = &CPU::opCodeCB0x00;
    opCodesCB[0x01] = &CPU::opCodeCB0x01;
    opCodesCB[0x02] = &CPU::opCodeCB0x02;
    opCodesCB[0x03] = &CPU::opCodeCB0x03;
    opCodesCB[0x04] = &CPU::opCodeCB0x04;
    opCodesCB[0x05] = &CPU::opCodeCB0x05;
    opCodesCB[0x06] = &CPU::opCodeCB0x06;
    opCodesCB[0x07] = &CPU::opCodeCB0x07;
    opCodesCB[0x08] = &CPU::opCodeCB0x08;
    opCodesCB[0x09] = &CPU::opCodeCB0x09;
    opCodesCB[0x0A] = &CPU::opCodeCB0x0A;
    opCodesCB[0x0B] = &CPU::opCodeCB0x0B;
    opCodesCB[0x0C] = &CPU::opCodeCB0x0C;
    opCodesCB[0x0D] = &CPU::opCodeCB0x0D;
    opCodesCB[0x0E] = &CPU::opCodeCB0x0E;
    opCodesCB[0x0F] = &CPU::opCodeCB0x0F;
    opCodesCB[0x10] = &CPU::opCodeCB0x10;
    opCodesCB[0x11] = &CPU::opCodeCB0x11;
    opCodesCB[0x12] = &CPU::opCodeCB0x12;
    opCodesCB[0x13] = &CPU::opCodeCB0x13;
    opCodesCB[0x14] = &CPU::opCodeCB0x14;
    opCodesCB[0x15] = &CPU::opCodeCB0x15;
    opCodesCB[0x16] = &CPU::opCodeCB0x16;
    opCodesCB[0x17] = &CPU::opCodeCB0x17;
    opCodesCB[0x18] = &CPU::opCodeCB0x18;
    opCodesCB[0x19] = &CPU::opCodeCB0x19;
    opCodesCB[0x1A] = &CPU::opCodeCB0x1A;
    opCodesCB[0x1B] = &CPU::opCodeCB0x1B;
    opCodesCB[0x1C] = &CPU::opCodeCB0x1C;
    opCodesCB[0x1D] = &CPU::opCodeCB0x1D;
    opCodesCB[0x1E] = &CPU::opCodeCB0x1E;
    opCodesCB[0x1F] = &CPU::opCodeCB0x1F;
    opCodesCB[0x20] = &CPU::opCodeCB0x20;
    opCodesCB[0x21] = &CPU::opCodeCB0x21;
    opCodesCB[0x22] = &CPU::opCodeCB0x22;
    opCodesCB[0x23] = &CPU::opCodeCB0x23;
    opCodesCB[0x24] = &CPU::opCodeCB0x24;
    opCodesCB[0x25] = &CPU::opCodeCB0x25;
    opCodesCB[0x26] = &CPU::opCodeCB0x26;
    opCodesCB[0x27] = &CPU::opCodeCB0x27;
    opCodesCB[0x28] = &CPU::opCodeCB0x28;
    opCodesCB[0x29] = &CPU::opCodeCB0x29;
    opCodesCB[0x2A] = &CPU::opCodeCB0x2A;
    opCodesCB[0x2B] = &CPU::opCodeCB0x2B;
    opCodesCB[0x2C] = &CPU::opCodeCB0x2C;
    opCodesCB[0x2D] = &CPU::opCodeCB0x2D;
    opCodesCB[0x2E] = &CPU::opCodeCB0x2E;
    opCodesCB[0x2F] = &CPU::opCodeCB0x2F;
    opCodesCB[0x30] = &CPU::opCodeCB0x30;
    opCodesCB[0x31] = &CPU::opCodeCB0x31;
    opCodesCB[0x32] = &CPU::opCodeCB0x32;
    opCodesCB[0x33] = &CPU::opCodeCB0x33;
    opCodesCB[0x34] = &CPU::opCodeCB0x34;
    opCodesCB[0x35] = &CPU::opCodeCB0x35;
    opCodesCB[0x36] = &CPU::opCodeCB0x36;
    opCodesCB[0x37] = &CPU::opCodeCB0x37;
    opCodesCB[0x38] = &CPU::opCodeCB0x38;
    opCodesCB[0x39] = &CPU::opCodeCB0x39;
    opCodesCB[0x3A] = &CPU::opCodeCB0x3A;
    opCodesCB[0x3B] = &CPU::opCodeCB0x3B;
    opCodesCB[0x3C] = &CPU::opCodeCB0x3C;
    opCodesCB[0x3D] = &CPU::opCodeCB0x3D;
    opCodesCB[0x3E] = &CPU::opCodeCB0x3E;
    opCodesCB[0x3F] = &CPU::opCodeCB0x3F;
    opCodesCB[0x40] = &CPU::opCodeCB0x40;
    opCodesCB[0x41] = &CPU::opCodeCB0x41;
    opCodesCB[0x42] = &CPU::opCodeCB0x42;
    opCodesCB[0x43] = &CPU::opCodeCB0x43;
    opCodesCB[0x44] = &CPU::opCodeCB0x44;
    opCodesCB[0x45] = &CPU::opCodeCB0x45;
    opCodesCB[0x46] = &CPU::opCodeCB0x46;
    opCodesCB[0x47] = &CPU::opCodeCB0x47;
    opCodesCB[0x48] = &CPU::opCodeCB0x48;
    opCodesCB[0x49] = &CPU::opCodeCB0x49;
    opCodesCB[0x4A] = &CPU::opCodeCB0x4A;
    opCodesCB[0x4B] = &CPU::opCodeCB0x4B;
    opCodesCB[0x4C] = &CPU::opCodeCB0x4C;
    opCodesCB[0x4D] = &CPU::opCodeCB0x4D;
    opCodesCB[0x4E] = &CPU::opCodeCB0x4E;
    opCodesCB[0x4F] = &CPU::opCodeCB0x4F;
    opCodesCB[0x50] = &CPU::opCodeCB0x50;
    opCodesCB[0x51] = &CPU::opCodeCB0x51;
    opCodesCB[0x52] = &CPU::opCodeCB0x52;
    opCodesCB[0x53] = &CPU::opCodeCB0x53;
    opCodesCB[0x54] = &CPU::opCodeCB0x54;
    opCodesCB[0x55] = &CPU::opCodeCB0x55;
    opCodesCB[0x56] = &CPU::opCodeCB0x56;
    opCodesCB[0x57] = &CPU::opCodeCB0x57;
    opCodesCB[0x58] = &CPU::opCodeCB0x58;
    opCodesCB[0x59] = &CPU::opCodeCB0x59;
    opCodesCB[0x5A] = &CPU::opCodeCB0x5A;
    opCodesCB[0x5B] = &CPU::opCodeCB0x5B;
    opCodesCB[0x5C] = &CPU::opCodeCB0x5C;
    opCodesCB[0x5D] = &CPU::opCodeCB0x5D;
    opCodesCB[0x5E] = &CPU::opCodeCB0x5E;
    opCodesCB[0x5F] = &CPU::opCodeCB0x5F;
    opCodesCB[0x60] = &CPU::opCodeCB0x60;
    opCodesCB[0x61] = &CPU::opCodeCB0x61;
    opCodesCB[0x62] = &CPU::opCodeCB0x62;
    opCodesCB[0x63] = &CPU::opCodeCB0x63;
    opCodesCB[0x64] = &CPU::opCodeCB0x64;
    opCodesCB[0x65] = &CPU::opCodeCB0x65;
    opCodesCB[0x66] = &CPU::opCodeCB0x66;
    opCodesCB[0x67] = &CPU::opCodeCB0x67;
    opCodesCB[0x68] = &CPU::opCodeCB0x68;
    opCodesCB[0x69] = &CPU::opCodeCB0x69;
    opCodesCB[0x6A] = &CPU::opCodeCB0x6A;
    opCodesCB[0x6B] = &CPU::opCodeCB0x6B;
    opCodesCB[0x6C] = &CPU::opCodeCB0x6C;
    opCodesCB[0x6D] = &CPU::opCodeCB0x6D;
    opCodesCB[0x6E] = &CPU::opCodeCB0x6E;
    opCodesCB[0x6F] = &CPU::opCodeCB0x6F;
    opCodesCB[0x70] = &CPU::opCodeCB0x70;
    opCodesCB[0x71] = &CPU::opCodeCB0x71;
    opCodesCB[0x72] = &CPU::opCodeCB0x72;
    opCodesCB[0x73] = &CPU::opCodeCB0x73;
    opCodesCB[0x74] = &CPU::opCodeCB0x74;
    opCodesCB[0x75] = &CPU::opCodeCB0x75;
    opCodesCB[0x76] = &CPU::opCodeCB0x76;
    opCodesCB[0x77] = &CPU::opCodeCB0x77;
    opCodesCB[0x78] = &CPU::opCodeCB0x78;
    opCodesCB[0x79] = &CPU::opCodeCB0x79;
    opCodesCB[0x7A] = &CPU::opCodeCB0x7A;
    opCodesCB[0x7B] = &CPU::opCodeCB0x7B;
    opCodesCB[0x7C] = &CPU::opCodeCB0x7C;
    opCodesCB[0x7D] = &CPU::opCodeCB0x7D;
    opCodesCB[0x7E] = &CPU::opCodeCB0x7E;
    opCodesCB[0x7F] = &CPU::opCodeCB0x7F;
    opCodesCB[0x80] = &CPU::opCodeCB0x80;
    opCodesCB[0x81] = &CPU::opCodeCB0x81;
    opCodesCB[0x82] = &CPU::opCodeCB0x82;
    opCodesCB[0x83] = &CPU::opCodeCB0x83;
    opCodesCB[0x84] = &CPU::opCodeCB0x84;
    opCodesCB[0x85] = &CPU::opCodeCB0x85;
    opCodesCB[0x86] = &CPU::opCodeCB0x86;
    opCodesCB[0x87] = &CPU::opCodeCB0x87;
    opCodesCB[0x88] = &CPU::opCodeCB0x88;
    opCodesCB[0x89] = &CPU::opCodeCB0x89;
    opCodesCB[0x8A] = &CPU::opCodeCB0x8A;
    opCodesCB[0x8B] = &CPU::opCodeCB0x8B;
    opCodesCB[0x8C] = &CPU::opCodeCB0x8C;
    opCodesCB[0x8D] = &CPU::opCodeCB0x8D;
    opCodesCB[0x8E] = &CPU::opCodeCB0x8E;
    opCodesCB[0x8F] = &CPU::opCodeCB0x8F;
    opCodesCB[0x90] = &CPU::opCodeCB0x90;
    opCodesCB[0x91] = &CPU::opCodeCB0x91;
    opCodesCB[0x92] = &CPU::opCodeCB0x92;
    opCodesCB[0x93] = &CPU::opCodeCB0x93;
    opCodesCB[0x94] = &CPU::opCodeCB0x94;
    opCodesCB[0x95] = &CPU::opCodeCB0x95;
    opCodesCB[0x96] = &CPU::opCodeCB0x96;
    opCodesCB[0x97] = &CPU::opCodeCB0x97;
    opCodesCB[0x98] = &CPU::opCodeCB0x98;
    opCodesCB[0x99] = &CPU::opCodeCB0x99;
    opCodesCB[0x9A] = &CPU::opCodeCB0x9A;
    opCodesCB[0x9B] = &CPU::opCodeCB0x9B;
    opCodesCB[0x9C] = &CPU::opCodeCB0x9C;
    opCodesCB[0x9D] = &CPU::opCodeCB0x9D;
    opCodesCB[0x9E] = &CPU::opCodeCB0x9E;
    opCodesCB[0x9F] = &CPU::opCodeCB0x9F;
    opCodesCB[0xA0] = &CPU::opCodeCB0xA0;
    opCodesCB[0xA1] = &CPU::opCodeCB0xA1;
    opCodesCB[0xA2] = &CPU::opCodeCB0xA2;
    opCodesCB[0xA3] = &CPU::opCodeCB0xA3;
    opCodesCB[0xA4] = &CPU::opCodeCB0xA4;
    opCodesCB[0xA5] = &CPU::opCodeCB0xA5;
    opCodesCB[0xA6] = &CPU::opCodeCB0xA6;
    opCodesCB[0xA7] = &CPU::opCodeCB0xA7;
    opCodesCB[0xA8] = &CPU::opCodeCB0xA8;
    opCodesCB[0xA9] = &CPU::opCodeCB0xA9;
    opCodesCB[0xAA] = &CPU::opCodeCB0xAA;
    opCodesCB[0xAB] = &CPU::opCodeCB0xAB;
    opCodesCB[0xAC] = &CPU::opCodeCB0xAC;
    opCodesCB[0xAD] = &CPU::opCodeCB0xAD;
    opCodesCB[0xAE] = &CPU::opCodeCB0xAE;
    opCodesCB[0xAF] = &CPU::opCodeCB0xAF;
    opCodesCB[0xB0] = &CPU::opCodeCB0xB0;
    opCodesCB[0xB1] = &CPU::opCodeCB0xB1;
    opCodesCB[0xB2] = &CPU::opCodeCB0xB2;
    opCodesCB[0xB3] = &CPU::opCodeCB0xB3;
    opCodesCB[0xB4] = &CPU::opCodeCB0xB4;
    opCodesCB[0xB5] = &CPU::opCodeCB0xB5;
    opCodesCB[0xB6] = &CPU::opCodeCB0xB6;
    opCodesCB[0xB7] = &CPU::opCodeCB0xB7;
    opCodesCB[0xB8] = &CPU::opCodeCB0xB8;
    opCodesCB[0xB9] = &CPU::opCodeCB0xB9;
    opCodesCB[0xBA] = &CPU::opCodeCB0xBA;
    opCodesCB[0xBB] = &CPU::opCodeCB0xBB;
    opCodesCB[0xBC] = &CPU::opCodeCB0xBC;
    opCodesCB[0xBD] = &CPU::opCodeCB0xBD;
    opCodesCB[0xBE] = &CPU::opCodeCB0xBE;
    opCodesCB[0xBF] = &CPU::opCodeCB0xBF;
    opCodesCB[0xC0] = &CPU::opCodeCB0xC0;
    opCodesCB[0xC1] = &CPU::opCodeCB0xC1;
    opCodesCB[0xC2] = &CPU::opCodeCB0xC2;
    opCodesCB[0xC3] = &CPU::opCodeCB0xC3;
    opCodesCB[0xC4] = &CPU::opCodeCB0xC4;
    opCodesCB[0xC5] = &CPU::opCodeCB0xC5;
    opCodesCB[0xC6] = &CPU::opCodeCB0xC6;
    opCodesCB[0xC7] = &CPU::opCodeCB0xC7;
    opCodesCB[0xC8] = &CPU::opCodeCB0xC8;
    opCodesCB[0xC9] = &CPU::opCodeCB0xC9;
    opCodesCB[0xCA] = &CPU::opCodeCB0xCA;
	opCodesCB[0xCB] = &CPU::opCodeCB0xCB
    opCodesCB[0xCC] = &CPU::opCodeCB0xCC;
    opCodesCB[0xCD] = &CPU::opCodeCB0xCD;
    opCodesCB[0xCE] = &CPU::opCodeCB0xCE;
    opCodesCB[0xCF] = &CPU::opCodeCB0xCF;
    opCodesCB[0xD0] = &CPU::opCodeCB0xD0;
    opCodesCB[0xD1] = &CPU::opCodeCB0xD1;
    opCodesCB[0xD2] = &CPU::opCodeCB0xD2;
    opCodesCB[0xD3] = &CPU::opcodeCB0xD3;
    opCodesCB[0xD4] = &CPU::opCodeCB0xD4;
    opCodesCB[0xD5] = &CPU::opCodeCB0xD5;
    opCodesCB[0xD6] = &CPU::opCodeCB0xD6;
    opCodesCB[0xD7] = &CPU::opCodeCB0xD7;
    opCodesCB[0xD8] = &CPU::opCodeCB0xD8;
    opCodesCB[0xD9] = &CPU::opCodeCB0xD9;
    opCodesCB[0xDA] = &CPU::opCodeCB0xDA;
    opCodesCB[0xDB] = &CPU::opcodeCB0xDB;
    opCodesCB[0xDC] = &CPU::opCodeCB0xDC;
    opCodesCB[0xDD] = &CPU::opcodeCB0xDD;
    opCodesCB[0xDE] = &CPU::opCodeCB0xDE;
    opCodesCB[0xDF] = &CPU::opCodeCB0xDF;
    opCodesCB[0xE0] = &CPU::opCodeCB0xE0;
    opCodesCB[0xE1] = &CPU::opCodeCB0xE1;
    opCodesCB[0xE2] = &CPU::opCodeCB0xE2;
    opCodesCB[0xE3] = &CPU::opcodeCB0xE3;
    opCodesCB[0xE4] = &CPU::opcodeCB0xE4;
    opCodesCB[0xE5] = &CPU::opCodeCB0xE5;
    opCodesCB[0xE6] = &CPU::opCodeCB0xE6;
    opCodesCB[0xE7] = &CPU::opCodeCB0xE7;
    opCodesCB[0xE8] = &CPU::opCodeCB0xE8;
    opCodesCB[0xE9] = &CPU::opCodeCB0xE9;
    opCodesCB[0xEA] = &CPU::opCodeCB0xEA;
    opCodesCB[0xEB] = &CPU::opcodeCB0xEB;
    opCodesCB[0xEC] = &CPU::opcodeCB0xEC;
    opCodesCB[0xED] = &CPU::opcodeCB0xED;
    opCodesCB[0xEE] = &CPU::opCodeCB0xEE;
    opCodesCB[0xEF] = &CPU::opCodeCB0xEF;
    opCodesCB[0xF0] = &CPU::opCodeCB0xF0;
    opCodesCB[0xF1] = &CPU::opCodeCB0xF1;
    opCodesCB[0xF2] = &CPU::opCodeCB0xF2;
    opCodesCB[0xF3] = &CPU::opCodeCB0xF3;
    opCodesCB[0xF4] = &CPU::opcodeCB0xF4;
    opCodesCB[0xF5] = &CPU::opCodeCB0xF5;
    opCodesCB[0xF6] = &CPU::opCodeCB0xF6;
    opCodesCB[0xF7] = &CPU::opCodeCB0xF7;
    opCodesCB[0xF8] = &CPU::opCodeCB0xF8;
    opCodesCB[0xF9] = &CPU::opCodeCB0xF9;
    opCodesCB[0xFA] = &CPU::opCodeCB0xFA;
    opCodesCB[0xFB] = &CPU::opCodeCB0xFB;
    opCodesCB[0xFC] = &CPU::opcodeCB0xFC;
    opCodesCB[0xFD] = &CPU::opcodeCB0xFD;
    opCodesCB[0xFE] = &CPU::opCodeCB0xFE;
    opCodesCB[0xFF] = &CPU::opCodeCB0xFF;
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
	MEM->WriteWord(Registers.BC.word, Registers.AF.hi);

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
	MEM->WriteWord(Registers.SP.word, MEM->ReadWord(Registers.PC.word + 1));

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
	Registers.DE.word = MEM->ReadWord(Registers.PC.word + 1);

	Clock.m = 3;
	Clock.t = 12;
	Registers.PC.word += 3;
}

void CPU::opCode0x12(){	//LD (DE), A; 8
	MEM->WriteWord(Registers.DE.word, Registers.AF.hi);

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
	Registers.HL.word = MEM->ReadWord(Registers.PC.word + 1);

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
		if((value > 0x9F) || Flag.C){
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
	Registers.HL.lo = MEM->ReadByte(Registers.PC.word + 1);

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
	Registers.SP.word = MEM->ReadWord(Registers.PC.word + 1);

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
	Registers.AF.hi = MEM->ReadByte(Registers.HL.word);
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
void CPU::opCode0x40(){	//LD B, B; 4
	Registers.BC.hi = Registers.BC.hi;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x41(){	//LD B, C; 4
	Registers.BC.hi = Registers.BC.lo;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x42(){	//LD B, D; 4
	Registers.BC.hi = Registers.DE.hi;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x43(){	//LD B, E; 4
	Registers.BC.hi = Registers.DE.lo;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x44(){	//LD B, H; 4
	Registers.BC.hi = Registers.HL.hi;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x45(){	//LD B, L; 4
	Registers.BC.hi = Registers.HL.lo;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x46(){	//LD B, (HL); 8
	Registers.BC.hi = MEM->ReadByte(Registers.HL.word);
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word += 1;
}

void CPU::opCode0x47(){	//LD B, A; 4
	Registers.BC.hi = Registers.AF.hi;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x48(){	//LD C, B; 4
	Registers.BC.lo = Registers.BC.hi;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x49(){	//LD C, C; 4
	Registers.BC.lo = Registers.BC.lo;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x4A(){	//LD C, D; 4
	Registers.BC.lo = Registers.DE.hi;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x4B(){	//LD C, E; 4
	Registers.BC.lo = Registers.DE.lo;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x4C(){	//LD C, H; 4
	Registers.BC.lo = Registers.HL.hi;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x4D(){	//LD C, L; 4
	Registers.BC.lo = Registers.HL.lo;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x4E(){	//LD C, (HL); 8
	Registers.BC.lo = MEM->ReadByte(Registers.HL.word);
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word += 1;
}

void CPU::opCode0x4F()	//LD C, A; 4
	Registers.BC.lo = Registers.AF.hi;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x50(){	//LD D, B; 4
	Registers.DE.hi = Registers.BC.hi;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x51(){	//LD D, C; 4
	Registers.DE.hi = Registers.BC.lo;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x52(){	//LD D, D; 4
	Registers.DE.hi = Registers.DE.hi;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x53(){	//LD D, E; 4
	Registers.DE.hi = Registers.DE.lo;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x54(){	//LD D, H; 4
	Registers.DE.hi = Registers.HL.hi;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x55(){	//LD D, L; 4
	Registers.DE.hi = Registers.HL.lo;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x56(){	//LD D, (HL); 8
	Registers.DE.hi = MEM->ReadByte(Registers.HL.word);
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word += 1;
}

void CPU::opCode0x57(){	//LD D, A; 4
	Registers.DE.hi = Registers.AF.hi;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x58(){	//LD E, B; 4
	Registers.DE.lo = Registers.BC.hi;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x59(){	//LD E, C; 4
	Registers.DE.lo = Registers.BC.lo;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x5A(){	//LD E, D; 4
	Registers.DE.lo = Registers.DE.hi;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x5B(){	//LD E, E; 4
	Registers.DE.lo = Registers.DE.lo;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x5C(){	//LD E, H; 4
	Registers.DE.lo = Registers.HL.hi;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x5D(){	//LD E, L; 4
	Registers.DE.lo = Registers.HL.lo;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x5E(){	//LD E, (HL); 8
	Registers.DE.lo = MEM->ReadByte(Registers.HL.word);
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word += 1;
}

void CPU::opCode0x5F(){	//LD E, A; 4
	Registers.DE.lo = Registers.AF.hi;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x60(){	//LD H, B; 4
	Registers.HL.hi = Registers.BC.hi;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x61(){	//LD H, C; 4
	Registers.HL.hi = Registers.BC.lo
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x62(){	//LD H, D; 4
	Registers.HL.hi = Registers.DE.hi;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}
void CPU::opCode0x63(){	//LD H, E; 4
	Registers.HL.hi = Registers.DE.lo;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x64(){	//LD H, H; 4
	Registers.HL.hi = Registers.HL.hi;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x65(){	//LD H, L; 4
	Registers.HL.hi = Registers.HL.lo;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x66(){	//LD H, (HL); 8
	Registers.HL.hi = MEM->ReadByte(Registers.HL.word);
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word += 1;
}

void CPU::opCode0x67(){	//LD H, A; 4
	Registers.HL.hi = Registers.AF.hi;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x68(){	//LD L, B; 4
	Registers.HL.lo = Registers.BC.hi;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x69(){	//LD L, C; 4
	Registers.HL.lo = Registers.BC.lo;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x6A(){	//LD L, D; 4
	Registers.HL.lo = Registers.DE.hi;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x6B(){	//LD L, E; 4
	Registers.HL.lo = Registers.DE.lo;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x6C(){	//LD L, H; 4
	Registers.HL.lo = Registers.HL.hi;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x6D(){	//LD L, L; 4
	Registers.HL.lo = Registers.HL.lo
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x6E(){	//LD L, (HL); 8
	Registers.HL.lo = MEM->ReadByte(Registers.HL.word);
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word += 1;
}

void CPU::opCode0x6F(){	//LD L, A; 4
	Registers.HL.lo = Registers.AF.hi;
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x70(){	//LD (HL), B; 8
	MEM->WriteByte(Registers.HL.word, Registers.BC.hi);
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word += 1;
}

void CPU::opCode0x71(){	//LD (HL), C; 8
	MEM->WriteByte(Registers.HL.word, Registers.BC.lo);
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word += 1;
}

void CPU::opCode0x72(){	//LD (HL), D; 8
	MEM->WriteByte(Registers.HL.word, Registers.DE.hi);
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word += 1;
}

void CPU::opCode0x73(){	//LD (HL), E; 8
	MEM->WriteByte(Registers.HL.word, Registers.DE.lo);
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word += 1;
}

void CPU::opCode0x74(){	//LD (HL), H; 8
	MEM->WriteByte(Registers.HL.word, Registers.HL.hi);
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word += 1;
}

void CPU::opCode0x75(){	//LD (HL), L; 8
	MEM->WriteByte(Registers.HL.word, Registers.HL.lo);
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word += 1;
}

void CPU::opCode0x76(){	//HALT; 4
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0x77(){	//LD (HL), A; 8
	MEM->WriteByte(Registers.HL.word, Registers.AF.hi);

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
	Registers.AF.hi = mem->ReadByte(Registers.HL.word);

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

void CPU::opCode0x80(){	//ADD A, B; 4
	Flag.N = 0;
	Flag.H = 0;
	Flag.C = 0;

	if(((Registers.AF.hi & 0x0FFF)+(Registers.BC.hi & 0x0FFF))> 0x0FFF)
		Flag.H = 1;
	if((Registers.AF.hi + Registers.BC.hi ) > 0x0FFF)
		Flag.C = 1;

	Registers.AF.hi += Registers.BC.hi;

	Flag.Z = !Registers.AF.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x81(){	//ADD A, C; 4
	Flag.N = 0;
	Flag.H = 0;
	Flag.C = 0;

	if(((Registers.AF.hi & 0x0FFF)+(Registers.BC.lo & 0x0FFF))> 0x0FFF)
		Flag.H = 1;
	if((Registers.AF.hi + Registers.BC.lo ) > 0x0FFF)
		Flag.C = 1;

	Registers.AF.hi += Registers.BC.lo;

	Flag.Z = !Registers.AF.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x82(){	//ADD A, D; 4
	Flag.N = 0;
	Flag.H = 0;
	Flag.C = 0;

	if(((Registers.AF.hi & 0x0FFF)+(Registers.DE.hi & 0x0FFF))> 0x0FFF)
		Flag.H = 1;
	if((Registers.AF.hi + Registers.DE.hi ) > 0x0FFF)
		Flag.C = 1;

	Registers.AF.hi += Registers.DE.hi;

	Flag.Z != Registers.AF.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x83(){	//ADD A, E; 4
	Flag.N = 0;
	Flag.H = 0;
	Flag.C = 0;

	if(((Registers.AF.hi & 0x0FFF)+(Registers.DE.lo & 0x0FFF))> 0x0FFF)
		Flag.H = 1;
	if((Registers.AF.hi + Registers.DE.lo ) > 0x0FFF)
		Flag.C = 1;

	Registers.AF.hi += Registers.DE.lo;

	Flag.Z = !Registers.AF.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x84(){	//ADD A, H; 4
	Flag.N = 0;
	Flag.H = 0;
	Flag.C = 0;

	if(((Registers.AF.hi & 0x0FFF)+(Registers.HL.hi & 0x0FFF))> 0x0FFF)
		Flag.H = 1;
	if((Registers.AF.hi + Registers.HL.hi ) > 0x0FFF)
		Flag.C = 1;

	Registers.AF.hi += Registers.HL.hi;

	Flag.Z = !Registers.AF.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x85(){	//ADD A, L; 4
	Flag.N = 0;
	Flag.H = 0;
	Flag.C = 0;

	if(((Registers.AF.hi & 0x0FFF)+(Registers.HL.lo & 0x0FFF))> 0x0FFF)
		Flag.H = 1;
	if((Registers.AF.hi + Registers.HL.lo ) > 0x0FFF)
		Flag.C = 1;

	Registers.AF.hi += Registers.HL.lo;

	Flag.Z = !Registers.AF.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x86(){	//ADD A, (HL); 8
	Flag.N = 0;
	Flag.H = 0;
	Flag.C = 0;

	uint8_t val = mem->ReadByte(Registers.HL.word);

	if(((Registers.AF.hi & 0x0FFF)+(val & 0x0FFF))> 0x0FFF)
		Flag.H = 1;
	if((Registers.AF.hi + val ) > 0x0FFF)
		Flag.C = 1;

	Registers.AF.hi += val;

	Flag.Z = !Registers.AF.hi;

	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void CPU::opCode0x87(){	//ADD A, A; 4
	Flag.N = 0;
	Flag.H = 0;
	Flag.C = 0;

	if(((Registers.AF.hi & 0x0FFF) * 2)> 0x0FFF)
		Flag.H = 1;
	if((Registers.AF.hi * 2) > 0x0FFF)
		Flag.C = 1;

	Registers.AF.hi *= 2;

	Flag.Z = !Registers.AF.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x88(){	//ADC A, B; 4
	Flag.N = 0;
	Flag.H = 0;
	Flag.C = 0;

	if(((Registers.AF.hi & 0x0FFF)+(Registers.BC.hi & 0x0FFF))> 0x0FFF)
		Flag.H = 1;
	if((Registers.AF.hi + Registers.BC.hi ) > 0x0FFF)
		Flag.C = 1;

	Registers.AF.hi += Registers.BC.hi;

	Registers.AF.hi += Flag.C;

	Flag.Z = !Registers.AF.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x89(){	//ADC A, C; 4
	Flag.N = 0;
	Flag.H = 0;
	Flag.C = 0;

	if(((Registers.AF.hi & 0x0FFF)+(Registers.BC.lo & 0x0FFF))> 0x0FFF)
		Flag.H = 1;
	if((Registers.AF.hi + Registers.BC.lo ) > 0x0FFF)
		Flag.C = 1;

	Registers.AF.hi += Registers.BC.lo;

	Registers.AF.hi += Flag.C;

	Flag.Z = !Registers.AF.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x8A(){	//ADC A, D; 4
	Flag.N = 0;
	Flag.H = 0;
	Flag.C = 0;

	if(((Registers.AF.hi & 0x0FFF)+(Registers.DE.hi & 0x0FFF))> 0x0FFF)
		Flag.H = 1;
	if((Registers.AF.hi + Registers.DE.hi ) > 0x0FFF)
		Flag.C = 1;

	Registers.AF.hi += Registers.DE.hi;

	Registers.AF.hi += Flag.C;

	Flag.Z != Registers.AF.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x8B(){	//ADC A, E; 4
	Flag.N = 0;
	Flag.H = 0;
	Flag.C = 0;

	if(((Registers.AF.hi & 0x0FFF)+(Registers.DE.lo & 0x0FFF))> 0x0FFF)
		Flag.H = 1;
	if((Registers.AF.hi + Registers.DE.lo ) > 0x0FFF)
		Flag.C = 1;

	Registers.AF.hi += Registers.DE.lo;

	Registers.AF.hi += Flag.C;

	Flag.Z = !Registers.AF.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x8C(){	//ADC A, H; 4
	Flag.N = 0;
	Flag.H = 0;
	Flag.C = 0;

	if(((Registers.AF.hi & 0x0FFF)+(Registers.HL.hi & 0x0FFF))> 0x0FFF)
		Flag.H = 1;
	if((Registers.AF.hi + Registers.HL.hi ) > 0x0FFF)
		Flag.C = 1;

	Registers.AF.hi += Registers.HL.hi;

	Registers.AF.hi += Flag.C;

	Flag.Z = !Registers.AF.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x8D(){	//ADC A, L; 4
	Flag.N = 0;
	Flag.H = 0;
	Flag.C = 0;

	if(((Registers.AF.hi & 0x0FFF)+(Registers.HL.lo & 0x0FFF))> 0x0FFF)
		Flag.H = 1;
	if((Registers.AF.hi + Registers.HL.lo ) > 0x0FFF)
		Flag.C = 1;

	Registers.AF.hi += Registers.HL.lo;

	Registers.AF.hi += Flag.C;

	Flag.Z = !Registers.AF.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x8E(){	//ADC A, (HL); 8
	Flag.N = 0;
	Flag.H = 0;
	Flag.C = 0;

	uint8_t val = mem->ReadByte(Registers.HL.word);

	if(((Registers.AF.hi & 0x0FFF)+(val & 0x0FFF))> 0x0FFF)
		Flag.H = 1;
	if((Registers.AF.hi + val ) > 0x0FFF)
		Flag.C = 1;

	Registers.AF.hi += val;

	Registers.AF.hi += Flag.C;

	Flag.Z = !Registers.AF.hi;

	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void CPU::opCode0x8F(){	//ADC A, A; 4
	Flag.N = 0;
	Flag.H = 0;
	Flag.C = 0;

	if(((Registers.AF.hi & 0x0FFF) * 2)> 0x0FFF)
		Flag.H = 1;
	if((Registers.AF.hi * 2) > 0x0FFF)
		Flag.C = 1;

	Registers.AF.hi *= 2;

	Registers.AF.hi += Flag.C;

	Flag.Z = !Registers.AF.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x90(){	//SUB B; 4
	Flag.N = 1;
	Flag.H = 0;
	Flag.C = 0;

	if(((Registers.AF.hi & 0x0FFF)-(Registers.BC.hi & 0x0FFF))> 0x0FFF)
		Flag.H = 1;
	if((Registers.AF.hi - Registers.BC.hi ) > 0x0FFF)
		Flag.C = 1;

	Registers.AF.hi -= Registers.BC.hi;

	Flag.Z = !Registers.AF.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x91(){	//SUB C; 4
	Flag.N = 1;
	Flag.H = 0;
	Flag.C = 0;

	if(((Registers.AF.hi & 0x0FFF)-(Registers.BC.lo & 0x0FFF))> 0x0FFF)
		Flag.H = 1;
	if((Registers.AF.hi - Registers.BC.lo ) > 0x0FFF)
		Flag.C = 1;

	Registers.AF.hi -= Registers.BC.lo;

	Flag.Z = !Registers.AF.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x92(){	//SUB D; 4
	Flag.N = 1;
	Flag.H = 0;
	Flag.C = 0;

	if(((Registers.AF.hi & 0x0FFF)-(Registers.DE.hi & 0x0FFF))> 0x0FFF)
		Flag.H = 1;
	if((Registers.AF.hi - Registers.DE.hi ) > 0x0FFF)
		Flag.C = 1;

	Registers.AF.hi -= Registers.DE.hi;

	Flag.Z = !Registers.AF.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x93(){	//SUB E; 4
	Flag.N = 1;
	Flag.H = 0;
	Flag.C = 0;

	if(((Registers.AF.hi & 0x0FFF)-(Registers.DE.lo & 0x0FFF))> 0x0FFF)
		Flag.H = 1;
	if((Registers.AF.hi - Registers.DE.lo ) > 0x0FFF)
		Flag.C = 1;

	Registers.AF.hi -= Registers.DE.lo;

	Flag.Z = !Registers.AF.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x94(){	//SUB H; 4
	Flag.N = 1;
	Flag.H = 0;
	Flag.C = 0;

	if(((Registers.AF.hi & 0x0FFF)-(Registers.HL.hi & 0x0FFF))> 0x0FFF)
		Flag.H = 1;
	if((Registers.AF.hi - Registers.HL.hi ) > 0x0FFF)
		Flag.C = 1;

	Registers.AF.hi -= Registers.HL.hi;

	Flag.Z = !Registers.AF.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x95(){	//SUB L; 4
	Flag.N = 1;
	Flag.H = 0;
	Flag.C = 0;

	if(((Registers.AF.hi & 0x0FFF)-(Registers.HL.lo & 0x0FFF))> 0x0FFF)
		Flag.H = 1;
	if((Registers.AF.hi - Registers.HL.lo ) > 0x0FFF)
		Flag.C = 1;

	Registers.AF.hi -= Registers.HL.lo;

	Flag.Z = !Registers.AF.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x96(){	//SUB (HL); 8
	Flag.N = 1;
	Flag.H = 0;
	Flag.C = 0;

	uint8_t val = mem->ReadByte(Registers.HL.word);


	if(((Registers.AF.hi & 0x0FFF)-(val & 0x0FFF))> 0x0FFF)
		Flag.H = 1;
	if((Registers.AF.hi - val ) > 0x0FFF)
		Flag.C = 1;

	Registers.AF.hi -= val;

	Flag.Z = !Registers.AF.hi;

	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void CPU::opCode0x97(){	//SUB A; 4
	Flag.N = 1;
	Flag.H = 0;
	Flag.C = 0;

	Registers.AF.hi = 0;

	Flag.Z = 0;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x98(){	//SBC A, B; 4
	Flag.N = 1;
	Flag.H = 0;

	Registers.AF.hi = Registers.AF.hi - Registers.BC.hi + Flag.C;

	Flag.C = 0;

	if((Registers.AF.hi & 0x0FFF)> 0x0FFF)
		Flag.H = 1;
	if(Registers.AF.hi > 0x0FFF)
		Flag.C = 1;

	Flag.Z != Registers.AF.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x99(){	//SBC A, C; 4
	Flag.N = 1;
	Flag.H = 0;

	Registers.AF.hi = Registers.AF.hi - Registers.BC.lo + Flag.C;

	Flag.C = 0;

	if((Registers.AF.hi & 0x0FFF)> 0x0FFF)
		Flag.H = 1;
	if(Registers.AF.hi > 0x0FFF)
		Flag.C = 1;

	Flag.Z != Registers.AF.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x9A(){	//SBC A, D; 4
	Flag.N = 1;
	Flag.H = 0;

	Registers.AF.hi = Registers.AF.hi - Registers.DE.hi + Flag.C;

	Flag.C = 0;

	if((Registers.AF.hi & 0x0FFF)> 0x0FFF)
		Flag.H = 1;
	if(Registers.AF.hi > 0x0FFF)
		Flag.C = 1;

	Flag.Z != Registers.AF.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void CPU::opCode0x9B(){	//SBC A, E; 4
	Flag.N = 1;
	Flag.H = 0;

	Registers.AF.hi = Registers.AF.hi - Registers.DE.lo + Flag.C;

	Flag.C = 0;

	if((Registers.AF.hi & 0x0FFF)> 0x0FFF)
		Flag.H = 1;
	if(Registers.AF.hi > 0x0FFF)
		Flag.C = 1;

	Flag.Z != Registers.AF.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}
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

void CPU::opCode0xB8(){	//CP B; 4
	int temp;
	temp = Registers.AF.hi - Registers.BC.hi;
	Flag.N = 1;
	if(!temp)
		Flag.Z = 1;
	if(temp < 0)
		Flag.C = 1;
	Flag.H = (temp && 0xf) && 0x10;	//half carry check

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0xB9(){	//CP C; 4
	int temp;
	temp = Registers.AF.hi - Registers.BC.lo;
	Flag.N = 1;
	if(!temp)
		Flag.Z = 1;
	if(temp < 0)
		Flag.C = 1;
	Flag.H = (temp && 0xf) && 0x10;	//half carry check

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0xBA(){	//CP D; 4
	int temp;
	temp = Registers.AF.hi - Registers.DE.hi;
	Flag.N = 1;
	if(!temp)
		Flag.Z = 1;
	if(temp < 0)
		Flag.C = 1;
	Flag.H = (temp && 0xf) && 0x10;	//half carry check

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0xBB(){	//CP E; 4
	int temp;
	temp = Registers.AF.hi - Registers.DE.lo;
	Flag.N = 1;
	if(!temp)
		Flag.Z = 1;
	if(temp < 0)
		Flag.C = 1;
	Flag.H = (temp && 0xf) && 0x10;	//half carry check

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0xBC(){	//CP H; 4
	int temp;
	temp = Registers.AF.hi - Registers.HL.hi;
	Flag.N = 1;
	if(!temp)
		Flag.Z = 1;
	if(temp < 0)
		Flag.C = 1;
	Flag.H = (temp && 0xf) && 0x10;	//half carry check

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0xBD(){	//CP L; 4
	int temp;
	temp = Registers.AF.hi - Registers.HL.lo;
	Flag.N = 1;
	if(!temp)
		Flag.Z = 1;
	if(temp < 0)
		Flag.C = 1;
	Flag.H = (temp && 0xf) && 0x10;	//half carry check

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0xBE(){	//CP (HL); 8
	int temp;
	temp = Registers.AF.hi - MEM->ReadByte(Registers.HL.word);
	Flag.N = 1;
	if(!temp)
		Flag.Z = 1;
	if(temp < 0)
		Flag.C = 1;
	Flag.H = (temp && 0xf) && 0x10;	//half carry check

	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word += 1;
}

void CPU::opCode0xBF(){	//CP A; 4
	int temp;
	temp = Registers.AF.hi - Registers.AF.hi;
	Flag.N = 1;
	if(!temp)
		Flag.Z = 1;
	if(temp < 0)
		Flag.C = 1;
	Flag.H = (temp && 0xf) && 0x10;	//half carry check

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word += 1;
}

void CPU::opCode0xC0();//RET NZ; 20/8
void CPU::opCode0xC1();//POP BC; 12

void CPU::opCode0xC2(){	//JP NZ, a16; 16
	Clock.t = 12;

	if(Flag.Z == 0){
		Registers.PC.word = MEM->ReadWord(Registers.PC.word + 1);
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
		Registers.PC.word = MEM->ReadWord(Registers.PC.word + 1);
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
		Registers.PC.word = MEM->ReadWord(Registers.PC.word + 1);
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
		Registers.PC.word = MEM->ReadWord(Registers.PC.word + 1);
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

void CPU::opCode0xE9(){	//JP (HL); 4
	Registers.PC.word = mem->ReadWord(Registers.HL.word);

	Clock.m = 1;
	Clock.t = 4;
}

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

void CPU::opCode0xFE(){	//CP d8; 8
	Flag.N = 1;
	Flag.Z = 0;
	Flag.H = 0;
	Flag.C = 0;

	uint8_t ayy, val;

	ayy = Registers.AF.hi;
	val = mem->ReadByte(Registers.PC.word + 1);

	if(((ayy & 0x0FFF)-(val & 0x0FFF))> 0x0FFF)
		Flag.H = 1;

	if(ayy > val)
		Flag.C =1;

	if(ayy == val)
		Flag.Z = 1;

	Clock.m = 2;
	Clock.t = 8;
	Registers.PC.word += 2;
}

void CPU::opCode0xFF();//RST 38H; 16
