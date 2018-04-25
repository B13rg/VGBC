#ifndef GPU_H
#define GPU_H

//#include "MEM.h"
//#include "Emulator.h"
#include <cstdint>
#include "cpu.h"
//#include <SFML/Graphics.hpp>

using namespace std;

#define STATE_OAM_READ 2
#define STATE_VRAM_READ 3
#define STATE_HBLANK 0
#define STATE_VBLANK 1

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

		bool lockVram;
		bool vblankStart;

		uint8_t * slate;


		uint8_t stateclock;
		uint8_t line;

		uint8_t tiles[384][8][8];
		uint8_t vram[0x2000];
		uint8_t scx, scy;	//scroll registers
		uint8_t wndx, wndy;	//window registers
		uint8_t bgbuffer[256][256];
		uint8_t paletteref[4][4];
		uint8_t palette[4];

		void writeScanLine(uint8_t *pixels);
		void RenderTile();
		void getColor(int, uint16_t, uint8_t *);
		void RenderSprite();


		
		MEM *mem;
	public:
		GPU(MEM*);
		~GPU();

		void WriteByteVram(uint16_t addr, uint8_t data);
		void WriteReg(uint16_t addr, uint8_t data);
		uint8_t ReadReg(uint16_t addr);
		void UpdateTile(uint16_t addr, uint8_t data);

		void Tick(uint32_t clock, uint8_t *);


		void get_Texture(uint8_t *pixels);
		uint8_t state;
};
#endif