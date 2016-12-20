#ifndef EMULATOR_H
#define EMULATOR_H

#include "MEM.h"
#include "GPU.h"
#include "DMGCPU.h"

using namespace std;

class Emulator{
	private:
		void update();
		
		const int MAXCYCLES = 69905;
		int timerCounter;
		int cyclesThisUpdate;
		int cycles;
		int dividerRegister;
		int dividerCounter;
		int interruptMaster;
		
		MEM* mem;
		GPU* gpu;
		CPU* cpu;
		
	public:
		Emulator();
		~Emulator();
		
		void platform();
		
		void updateTimers(int);
		void DoDividerRegister();
		void setClockFreq();
		void requestInterrupt(int);
		void doInterupts();
		void serviceInterrupt(int);
};
#endif