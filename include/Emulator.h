#IFNDEF EMULATOR_H
#DEFINE EMULATOR_H

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
		
	public:
		Emulator();
		~Emulator();
		
		void update();
		void updateTimers(int);
		void DoDividerRegister();
		void setClockFreq();
		void requestInterrupt(int);
		void doInterrupts();
		void serviceInterrupt(int);
}