#ifndef GPU_H
#define GPU_H

//#include "MEM.h"
//#include "Emulator.h"
#include "DMGCPU.h"

using namespace std;

class GPU{
	private:
		bool dispEnable;		//bit 7: LCD Display enable 0=off, 1=on
		bool mapSelect;		//bit 6: Tile map select 0=9800-9BFF, 1=9C00-9FFF
		bool windowEnable;	//bit 5: Window display enable 0=0ff, 1=on
		bool tileSelect;		//bit 4: BG & window data select 0=8800-97FF, 1=8000-8FFF
		bool bgTileSelect;	//bit 3: BG tile map display select 0=9800-9BFF, 1=9C00-9FFF
		bool spriteSize;		//bit 2: Sprite Size 0=8x8, 1=8x16
		bool spriteEnable;	//bit 1: Bit 5 for sprites
		bool bgDisplay;		//bit 0: Bit 5 and 1 for background 0=off, 1=on

		MEM *mem;
	public:
		GPU(MEM*);
		~GPU();
};
#endif