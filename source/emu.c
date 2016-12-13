#include "opcodes.h"
#include "flags.h"

//Template for registers
typedef union{
	struct{
		uint8_t lo;
		uint8_t hi;
	};
	uint16_t word;
}Register16_t;

//CPU registers
typedef struct{
	//Basic Registers
	Register16_t AF, BC, DE, HL;
	
	//Special Registers
	Register16_t SP, PC;
	
	//Flags
	uint8_t FL;
}regs_t;

//Opcode Tables
void (c_DMGCPU::*OPCodes[0xFF])(void);
void (c_DMGCPU::*OPCodesCB[0xFF])(void);

void c_DMGCPU::OPCODE0x3e(){
	DbgOut(DBG_CPU, VERBOSE_2, "Ld A, d8");
	Registers.AF.hi = MMU->ReadByte(Registers.PC.word + 1);
	Clock.m = 2;
	Clock.t = 8;
	Registers.PC.word += 2;
}





int main(){
	//Counter = InterruptPeriod
	//PC = InitialPC
	flags Flag;
	for(;;){
		Opcode = Memory[PC++];
		Counter -= Cycles[OpCode];
	
		switch(Opcode){
			case OpCode1: ;
			//etc
		}

		if(Counter <= 0){
			// check for interrupts
			// cyclic tasks
			//
			Counter += InterruptPeriod;
			if(ExitRequired) break;
		}
	} 
}



