#ifndef EMULATOR_H
#define EMULATOR_H

#include "MEM.h"
#include "GPU.h"
#include "DMGCPU.h"

using namespace std;

class Emulator{
	private:
		

		const int MAXCYCLES = 69905;
		int timerCounter;
		int cyclesThisUpdate;
		//uint32_t cycles;
		//int dividerRegister;
		int dividerCounter;
		int interruptMaster;
	public:
		Emulator();
		~Emulator();

		MEM* mem;
		GPU* gpu;
		CPU* Cpu;
		void platform();

		void update(sf::Uint8 *);

		void updateTimers(int);
		void DoDividerRegister(int);
		void setClockFreq();
		void requestInterrupt(int);
		void doInterupts();
		void serviceInterrupt(int);
		bool InteruptsEnabled;
};
#endif
