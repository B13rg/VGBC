#include <stdio.h>
#include <cstdint>
#include "GPU.h"

using namespace std;

GPU::GPU(MEM* MEM) {
	mem = MEM;
	stateclock = 0;
	state = 0;
	line = 0;
	memset(&tiles, 0, 384 * 8 * 8);

	vblankStart = false;

	paletteref[0][0] = 156;
	paletteref[0][1] = 189;
	paletteref[0][2] = 15;
	paletteref[0][3] = 255;

	paletteref[1][0] = 140;
	paletteref[1][1] = 173;
	paletteref[1][2] = 15;
	paletteref[1][3] = 255;

	paletteref[2][0] = 48;
	paletteref[2][1] = 98;
	paletteref[2][2] = 48;
	paletteref[2][3] = 255;

	paletteref[3][0] = 15;
	paletteref[3][1] = 56;
	paletteref[3][2] = 15;
	paletteref[3][3] = 255;
}

GPU::~GPU() {}

//tilemap layout
//8000-87FF | tiles 0-127 tileset 1
//8800-8FFF | tiles 128-255, -1 to -128
//9000-97FF | tiles 0-127 tileset 0
//9800-9BFF | tilemap 0
//9C00-9FFF | tilemap 1


void GPU::WriteByteVram(uint16_t addr, uint8_t data)
{
	if (!lockVram) {
		mem->WriteByte(addr, data);
		//vram[addr - 0x8000] = data;

		UpdateTile(addr, data);
	}
}

void GPU::WriteReg(uint16_t addr, uint8_t data)
{
}

uint8_t GPU::ReadReg(uint16_t addr)
{
	switch (addr) {
	case 0xFF40:	//LCD control
		return 0;
	case 0xFF42:	//SCY
		return scy;
	case 0xFF43:	//SCX
		return scx;

	case 0xFF44:
		return line;
	case 0xFF4A:
		return wndy;
	case 0xFF4B:
		return wndx;
	default:
		return 0;
	}
}

void GPU::UpdateTile(uint16_t addr, uint8_t data)
{
	uint16_t addrtrans = addr & 0x1FFE;
	uint16_t tileindex = (addrtrans >> 4);
	uint8_t y = (addrtrans >> 1) & 7;

	uint8_t sx, x;

	for (x = 0; x < 8; x++) {
		sx = 1 << (7 - x);
		tiles[tileindex][y][x] = ((mem->ReadByte(addr) & sx) ? 1 : 0)+((mem->ReadByte(addr + 1) & sx) ? 2 : 0);
	}
}

void GPU::Tick(uint32_t clock, sf::Uint8 * pixels)
{
	stateclock += clock;

	switch (state) {
	case STATE_OAM_READ:
		if (stateclock >= 20) {
			stateclock = 0;
			state = STATE_VRAM_READ;
		}
		break;
	case STATE_VRAM_READ:
		if (stateclock >= 43) {
			stateclock = 0;
			state = STATE_HBLANK;
		}
		break;
	case STATE_HBLANK:
		if (stateclock >= 51) {
			stateclock = 0;
			line++;
			if (line == 143) {
				state = STATE_VBLANK;
				writeScanLine(pixels);
			}
			else
				state = STATE_OAM_READ;
		}
		break;
	case STATE_VBLANK:
		if (stateclock >= 114) {
			stateclock = 0;
			line++;

			if (line > 153) {
				state = STATE_OAM_READ;
				line = 0;
			}
		}
		break;
	default:
		state = STATE_OAM_READ;
		break;
	}
}

void GPU::get_Texture(sf::Uint8 * pixels)
{
	//calculate each pixel on 160x144 screen



	//return pixels;
}

void GPU::writeScanLine(sf::Uint8 * pixels)
{
	uint16_t tilemapbase = 0x1800;
	uint16_t offsetbase = tilemapbase + ((((line + scy) & 255) >> 3) << 5);
	uint8_t x, y, tindex;

	y = (line + scy) & 7;
	for (x = 0; x < 160; x++) {
		tindex = vram[offsetbase + (x / 8)];



		pixels[x*line] = paletteref[palette[tiles[tindex][y][x % 8]]][0];
		pixels[x*line + 1] = paletteref[palette[tiles[tindex][y][x % 8]]][1];
		pixels[x*line + 2] = paletteref[palette[tiles[tindex][y][x % 8]]][2];
		pixels[x*line + 3] = paletteref[palette[tiles[tindex][y][x % 8]]][3];
	}
}

