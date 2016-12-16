#include opcodes.h

Counter = InterruptPeriod
PC = InitialPC

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

void (c_DMGCPU::*OPCodes[0xFF])

/* Opcode Function Structure
void opCode0x##(){; Function; Cycles
	Do the opcode function

	Set flags 

	Set instruction size
	Set instruction cycles
	Increment instruction pointer
} */

void opCode0x00(){//NOP; 4
	Clock.m = 1;	//instruction size ??
	Clock.t = 4;	//Number of cycles
	Registers.PC.word ++;  //size of instruction, 1 byte
}

void opCode0x01(){ //LD BC, d16; 12
	Registers.BC.word = MEM->Readword(Registers.PC.word + 1);

	Clock.m = 3;
	Clock.t = 12;
	Registers.PC.word += 3;
}

void opCode0x02(){ //LD (BC), A; 8
	MEM->Writeword(Registers.BC.word, Registers.AF.hi);

	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;	
}

void opCode0x03(){ //INC BC; 8
	Registers.BC.word ++;

	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;	
}

void opCode0x04(){ //INC B; 4
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

void opCode0x05(){ //DEC B; 4
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

void opCode0x06(){ //LD B, d8; 8
	Registers.BC.hi = MEM->ReadByte(Registers.PC.word + 1);
	
	Clock.m =2;
	Clock.t = 8;
	Registers.PC.word += 2;
}

void opCode0x07(){ //RLCA; 4
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

void opCode0x08(){ //LD (a16), SP; 20
	MEM->Writeword(Registers.SP.word, MEM->ReadWord(Registers.PC.word + 1));
	
	Clock.m = 3;
	Clock.t = 20;
	Registers.PC.word += 3;
}

void opCode0x09(){	//ADD HL, BC; 8
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

void opCode0x0A(){ //LD A, (BC); 8
	Registers.AF.hi = MEM->ReadByte(Registers.BC.word);

	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void opCode0x0B(){ //DEC BC; 8
	Registers.BC.word --;
	
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void opCode0x0C(){ //INC C; 4
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

void opCode0x0D(){ //DEC C; 4
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

void opCode0x0E(){ //LD C, d8; 8
	Registers.BC.lo = MEM->ReadByte(Registers.PC.word + 1);
	
	Clock.m = 2;
	Clock.t = 8;
	Registers.PC.word += 2;
}

void opCode0x0F(){ //RRCA; 4
	uint8_t carryi = (Registers.AF.hi >> 0) & 1;	//get 7th bit of A register

	resetFlags();	//reset all flags

	Registers.AF.hi = (Registers.AF.hi >>> 1);	//shift bits right 1 spot
	Registers.AF.hi |= carryi;
	Flag.C = carryi;
	
	Clock.m = 1;
	Clock.c = 4;
	Registers.PC.word ++;
}

void opCode0x10(){	//STOP 0; 4
	while(Registers.AF.hi == 0 || MEM->ReadByte(0xFF00) == 0);
	
	Clock.m = 1;
	Clock.t = 4;
	
	if(MEM->ReadByte(Registers.PC.word + 1) == 0x00)
		Registers.PC.word += 2;
	else
		Registers.PC.word ++;
}

void opCode0x11(){	//LD DE, D16; 12
	Registers.DE.word = MEM->Readword(Registers.PC.word + 1);

	Clock.m = 3;
	Clock.t = 12;
	Registers.PC.word += 3;
}

void opCode0x12(){	//LD (DE), A; 8
	MEM->Writeword(Registers.DE.word, Registers.AF.hi);

	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void opCode0x13(){	//INC DE; 8
	Registers.DE.word ++;

	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void opCode0x14(){	//INC D; 4
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

void opCode0x15(){	//DEC D; 4
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

void opCode0x16(){	//LD D, D8; 8
	Registers.DE.hi = MEM->ReadByte(registers.PC.word + 1);
	
	Clock.m = 2;
	Clock.t = 8;
	Registers.PC.word += 2;
}

void opCode0x17();//RLA; 4
void opCode0x18(){	//JR r8; 12
	Registers.PC.word += (uint8_t)(MEM->ReadByte(Registers.PC.word + 1)) + 2;
	Clock.m = 2;
	Clock.t = 12;
}

void opCode0x19(){	//ADD HL, DE; 8
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

void opCode0x1A(){	//LD A, (DE); 8
	Registers.AF.hi = MEM->ReadByte(Registers.DE.word);

	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void opCode0x1B(){//DEC DE; 8
	Registers.DE.word --;
	
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void opCode0x1C(){	//INC E; 4
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

void opCode0x1D(){	//DEC E; 4
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

void opCode0x1E(){	//LD E, d8; 8
	Registers.DE.lo = MEM->ReadByte(Registers.PC.word + 1);
	
	Clock.m = 2;
	Clock.t = 8;
	Registers.PC.word += 2;
}

void opCode0x1F();//RRA; 4

void opCode0x20(){	//JR NZ, r8; 12/8
	Clock.m = 2;
	Clock.t = 8;
	if(!Flag.Z){
		Registers.PC.word += (uint8_t)(MEM->ReadByte(Registers.PC.word + 1)) + 2;
		Clock.t = 12;
	}
}

void opCode0x21(){	//LD HL, d16; 12
	Registers.HL.word = MEM->Readword(Registers.PC.word + 1);

	Clock.m = 3;
	Clock.t = 12;
	Registers.PC.word += 3;
}

void opCode0x22(){	//LD(HL+), A; 8
	MEM->WriteByte(Registers.HL.word, Registers.AF.hi);
	Registers.GL.word ++;
	
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void opCode0x23(){	//INC HL; 8
	Registers.HL.word ++;

	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void opCode0x24(){	//INC H; 4
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

void opCode0x25(){	//DEC H; 4
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

void opCode0x26(){	//LD H, d8; 8
	Registers.HL.hi = MEM->ReadByte(Registers.PC.word + 1);
	
	Clock.m = 2;
	Clock.t = 8;
	Registers.PC.word += 2;
}

void opCode0x27(){	//DAA; 4
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

void opCode0x28(){	//JR Z, r8; 12/8
	Clock.m = 2;
	Clock.t = 8;
	
	if(Flag.Z){
		Registers.PC.word += (uint8_t)(MEM->ReadByte(Registers.PC.word + 1)) + 2;
		Clock.t = 12;
	}
}

void opCode0x29(){	//ADD HL, HL; 8
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

void opCode0x2A(){	//LD A, (HL+); 8
	Registers.AF.hi = MEM->ReadByte(Registers.HL.word);
	Registers.HL.word ++;
	
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++; 
}

void opCode0x2B(){	//DEC HL; 8
	Registers.HL.word --;
	
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void opCode0x2C(){	//INC L; 4
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

void opCode0x2D(){	//DEC L; 4
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

void opCode0x2E(){	//LD L, d8; 8
	Registers.HL.lo = MEM->Readbyte(Registers.PC.word + 1);
	
	Clock.m = 2;
	Clock.t = 8;
	Registers.PC.word += 2;	
}

void opCode0x2F(){	//CPL; 4
	Registers.AH.hi ^= 0xFF;
	
	Flag.N = 1;
	Flag.H =1;
	
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void opCode0x30(){	//JR NC, r8; 12/8
		Clock.m = 2;
	Clock.t = 8;
	
	if(!Flag.C){
		Registers.PC.word += (uint8_t)(MEM->ReadByte(Registers.PC.word + 1)) + 2;
		Clock.t = 12;
	}
}

void opCode0x31(){	//LD SP, d16; 12
	Registers.SP.word = MEM->Readword(Registers.PC.word + 1);

	Clock.m = 3;
	Clock.t = 12;
	Registers.PC.word += 3;
}

void opCode0x32(){	//LD (HL-), A; 8
	MEM->WriteByte(Registers.HL.word, Registers.AF.hi);
	Registers.HL.word --;
	
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++; 
}

void opCode0x33(){	//INC SP; 8
	Registers.SP.word ++;

	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void opCode0x34(){	//INC (HL); 12
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

void opCode0x35(){	//DEC (HL); 12
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

void opCode0x36(){	//LD (HL), d8; 12
	MEM->WriteByte(Registers.HL.word, MEM->ReadByte(Registers.PC.word + 1));
	
	Clock.m = 2;
	Clock.t = 12;
	Registers.PC.word += 2;
}

void opCode0x37(){	//SCF; 4
	Flag.C = 1;
	Flag.N = 0;
	Flag.H = 0;
	
	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word = 1;
}

void opCode0x38(){	//JR C, r8; 12/8
	Clock.m = 2;
	Clock.t = 8;
	
	if(Flag.C){
		Registers.PC.word += (uint8_t)(MEM->ReadByte(Registers.PC.word + 1)) + 2;
		Clock.t = 12;
	}
}

void opCode0x39(){	//ADD HL, SP; 8
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

void opCode0x3A(){	//LD A, (HL-); 8
	Registers.AF.hi = MEM->Readbyte(Registers.HL.word);
	Registers.HL.word--;
	
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void opCode0x3B(){	//DEC SP; 8
	Registers.SP.word --;
	
	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void opCode0x3C(){	//INC A; 4
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

void opCode0x3D(){	//DEC A; 4
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

void opCode0x3E(){	//LD A, d8; 8
	Registers.AF.hi = MEM->ReadByte(Registers.PC.word + 1);
	Clock.m =2;
	Clock.t = 8;
	Registers.PC.word += 2;
}

void opCode0x3F(){	//CCF; 4
	Flag.C ^= 1;
	
	Flag.N = 0;
	Flag.H =0;
	
	Clock.m = 1
	Clock.t = 4;
	Registers.PC.word += 1;
}

/************************************/
void opCode0x40();//LD B, B; 4
void opCode0x41();//LD B, C; 4
void opCode0x42();//LD B, D; 4
void opCode0x43();//LD B, E; 4
void opCode0x44();//LD B, H; 4
void opCode0x45();//LD B, L; 4
void opCode0x46();//LD B, (HL); 8
void opCode0x47();//LD B, A; 4
void opCode0x48();//LD C, B; 4
void opCode0x49();//LD C, C; 4
void opCode0x4A();//LD C, D; 4
void opCode0x4B();//LD C, E; 4
void opCode0x4C();//LD C, H; 4
void opCode0x4D();//LD C, L; 4
void opCode0x4E();//LD C, (HL); 8
void opCode0x4F();//LD C, A; 4

void opCode0x50();//LD D, B; 4
void opCode0x51();//LD D, C; 4
void opCode0x52();//LD D, D; 4
void opCode0x53();//LD D, E; 4
void opCode0x54();//LD D, H; 4
void opCode0x55();//LD D, L; 4
void opCode0x56();//LD D, (HL); 8
void opCode0x57();//LD D, A; 4
void opCode0x58();//LD E, B; 4
void opCode0x59();//LD E, C; 4
void opCode0x5A();//LD E, D; 4
void opCode0x5B();//LD E, E; 4
void opCode0x5C();//LD E, H; 4
void opCode0x5D();//LD E, L; 4
void opCode0x5E();//LD E, (HL); 8
void opCode0x5F();//LD E, A; 4

void opCode0x60();//LD H, B; 4
void opCode0x61();//LD H, C; 4
void opCode0x62();//LD H, D; 4
void opCode0x63();//LD H, E; 4
void opCode0x64();//LD H, H; 4
void opCode0x65();//LD H, L; 4
void opCode0x66();//LD H, (HL); 8
void opCode0x67();//LD H, A; 4
void opCode0x68();//LD L, B; 4
void opCode0x69();//LD L, C; 4
void opCode0x6A();//LD L, D; 4
void opCode0x6B();//LD L, E; 4
void opCode0x6C();//LD L, H; 4
void opCode0x6D();//LD L, L; 4
void opCode0x6E();//LD L, (HL); 8
void opCode0x6F();//LD L, A; 4

void opCode0x70();//LD (HL), B; 8
void opCode0x71();//LD (HL), C; 8
void opCode0x72();//LD (HL), D; 8
void opCode0x73();//LD (HL), E; 8
void opCode0x74();//LD (HL), H; 8
void opCode0x75();//LD (HL), L; 8
void opCode0x76();//HALT; 4
void opCode0x77(){	//LD (HL), A; 8
	MEM->Writeword(Registers.HL.word, Registers.AF.hi);

	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void opCode0x78(){	//LD A, B; 4
	Registers.AF.hi = Registers.BC.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void opCode0x79(){	//LD A, C; 4
	Registers.AF.hi = Registers.BC.lo;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void opCode0x7A(){	//LD A, D; 4
	Registers.AF.hi = Registers.DE.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void opCode0x7B(){	//LD A, E; 4
	Registers.AF.hi = Registers.DE.lo;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void opCode0x7C(){	//LD A, H; 4
	Registers.AF.hi = Registers.HL.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void opCode0x7D(){	//LD A, L; 4
	Registers.AF.hi = Registers.HL.lo;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void opCode0x7E(){	//LD A, (HL); 8
	Registers.AF.hi = Registers.HL.word;

	Clock.m = 1;
	Clock.t = 8;
	Registers.PC.word ++;
}

void opCode0x7F(){	//LD A, A; 4
	Registers.AF.hi = Registers.AF.hi;

	Clock.m = 1;
	Clock.t = 4;
	Registers.PC.word ++;
}

void opCode0x80();//ADD A, B; 4
void opCode0x81();//ADD A, C; 4
void opCode0x82();//ADD A, D; 4
void opCode0x83();//ADD A, E; 4
void opCode0x84();//ADD A, H; 4
void opCode0x85();//ADD A, L; 4
void opCode0x86();//ADD A, (HL); 8
void opCode0x87();//ADD A, A; 4
void opCode0x88();//ADC A, B; 4
void opCode0x89();//ADC A, C; 4
void opCode0x8A();//ADC A, D; 4
void opCode0x8B();//ADC A, E; 4
void opCode0x8C();//ADC A, H; 4
void opCode0x8D();//ADC A, L; 4
void opCode0x8E();//ADC A, (HL); 8
void opCode0x8F();//ADC A, A; 4

void opCode0x90();//SUB B; 4
void opCode0x91();//SUB C; 4
void opCode0x92();//SUB D; 4
void opCode0x93();//SUB E; 4
void opCode0x94();//SUB H; 4
void opCode0x95();//SUB L; 4
void opCode0x96();//SUB (HL); 8
void opCode0x97();//SUB A; 4
void opCode0x98();//SBC A, B; 4
void opCode0x99();//SBC A, C; 4
void opCode0x9A();//SBC A, D; 4
void opCode0x9B();//SBC A, E; 4
void opCode0x9C();//SBC A, H; 4
void opCode0x9D();//SBC A, L; 4
void opCode0x9E();//SBC A, (HL); 8
void opCode0x9F();//SBC A, A; 4

void opCode0xA0();//AND B; 4
void opCode0xA1();//AND C; 4
void opCode0xA2();//AND D; 4
void opCode0xA3();//AND E; 4
void opCode0xA4();//AND H; 4
void opCode0xA5();//AND L; 4
void opCode0xA6();//AND (HL); 8
void opCode0xA7();//AND A; 4
void opCode0xA8();//XOR B; 4
void opCode0xA9();//XOR C; 4
void opCode0xAA();//XOR D; 4
void opCode0xAB();//XOR E; 4
void opCode0xAC();//XOR H; 4
void opCode0xAD();//XOR L; 4
void opCode0xAE();//XOR (HL); 8
void opCode0xAF();//XOR A; 4

void opCode0xB0();//OR B; 4
void opCode0xB1();//OR C; 4
void opCode0xB2();//OR D; 4
void opCode0xB3();//OR E; 4
void opCode0xB4();//OR H; 4
void opCode0xB5();//OR L; 4
void opCode0xB6();//OR (HL); 8
void opCode0xB7();//OR A; 4
void opCode0xB8();//CP B; 4
void opCode0xB9();//CP C; 4
void opCode0xBA();//CP D; 4
void opCode0xBB();//CP E; 4
void opCode0xBC();//CP H; 4
void opCode0xBD();//CP L; 4
void opCode0xBE();//CP (HL); 8
void opCode0xBF();//CP A; 4

void opCode0xC0();//RET NZ; 20/8
void opCode0xC1();//POP BC; 12
void opCode0xC2(){	//JP NZ, a16; 16
	Clock.t = 12;
	
	if(Flag.Z == 0){
		Registers.PC.word = MEM->Readword(Registers.PC.word + 1);
		Clock.t = 16;
	}
	
	Clock.m = 3
}

void opCode0xC3(){	//JP a16; 16
	Registers.PC.word = MEM->ReadWord(Registers.PC.word+1);
	Clock.m = 3;
	Clock.t = 16;
}

void opCode0xC4();//CALL NZ, a16
void opCode0xC5();//PUSH BC
void opCode0xC6();//ADD A, d8
void opCode0xC7();//RST 00H; 16
void opCode0xC8();//RET Z; 20/8
void opCode0xC9();//RET; 16
void opCode0xCA(){	//JP Z, a16; 16/12
	Clock.t = 12;
	
	if(Flag.Z == 1){
		Registers.PC.word = MEM->Readword(Registers.PC.word + 1);
		Clock.t = 16;
	}
	
	Clock.m = 3
}

void opCode0xCB();//PREFIX CB; 4
void opCode0xCC();//CALL Z, a16; 24/12
void opCode0xCD();//CALL a16; 24
void opCode0xCE();//ADC A, d8; 8
void opCode0xCF();//RST 08H; 16

void opCode0xD0();//RET NC; 20/8
void opCode0xD1();//POP DE; 12
void opCode0xD2(){	//JP NC, a16; 16/12
	Clock.t = 12;
	
	if(Flag.C == 0){
		Registers.PC.word = MEM->Readword(Registers.PC.word + 1);
		Clock.t = 16;
	}
	
	Clock.m = 3
}

//void opCode0xD3();//BLANK
void opCode0xD4();//CALL NC, a16; 24/12
void opCode0xD5();//PUSH DE; 16
void opCode0xD6();//SUB d8; 8
void opCode0xD7();//RST 10H; 16
void opCode0xD8();//RET C; 20/8
void opCode0xD9();//RETI; 16
void opCode0xDA(){	//JP C, a16; 16/12
	Clock.t = 12;
	
	if(Flag.C == 1){
		Registers.PC.word = MEM->Readword(Registers.PC.word + 1);
		Clock.t = 16;
	}
	
	Clock.m = 3
}

//void opCode0xDB();//BLANK
void opCode0xDC();//CALL C, a16; 24/12
//void opCode0xDD();//BLANK
void opCode0xDE();//SBC A, d8; 8
void opCode0xDF();//RST 18H; 16

void opCode0xE0();//LDH (a8), A; 12
void opCode0xE1();//POP HL; 12
void opCode0xE2();//LD (C), A; 8
//void opCode0xE3();//BLANK
//void opCode0xE4();//BLANK
void opCode0xE5();//PUSH HL; 16
void opCode0xE6();//AND d8; 8
void opCode0xE7();//RST 20H; 16
void opCode0xE8(){	//ADD SP, r8; 16
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

void opCode0xE9();//JP (HL); 4
void opCode0xEA();//LD (a16), A; 16
//void opCode0xEB();//BLANK
//void opCode0xEC();//BLANK
//void opCode0xED();//BLANK
void opCode0xEE();//XOR d8; 8
void opCode0xEF();//RST 28H; 16

void opCode0xF0();//LDH A, (a8); 12
void opCode0xF1();//POP AF; 12
void opCode0xF2();//LD A, (C); 8
void opCode0xF3();//DI; 4
//void opCode0xF4();//BLANK
void opCode0xF5();//PUSH AF; 16
void opCode0xF6();//OR d8; 8
void opCode0xF7();//RST 30H; 16
void opCode0xF8();//LD HL, SP+r8; 12
void opCode0xF9();//LD SP, HL; 8
void opCode0xFA();//LD A, (a16); 16
void opCode0xFB();//EI; 4
//void opCode0xFC();//BLANK
//void opCode0xFD();//BLANK
void opCode0xFE();//CP d8; 8
void opCode0xFF();//RST 38H; 16


//Regular OpCodes
void (c_DMGCPU::*OPCodes[0xFF])(void);
void (c_DMGCPU::*OPCodesCB[0xFF])(void);

//Function to setup opcodes
void opCodeInit();
