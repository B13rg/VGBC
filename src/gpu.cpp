#include <stdio.h>
#include <cstdint>
#include <cstring>
#include "../include/gpu.h"

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

void GPU::Tick(uint32_t clock, uint8_t * pixels)
{
	stateclock += clock;
	slate = pixels;
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

void GPU::get_Texture(uint8_t * pixels)
{
	//calculate each pixel on 160x144 screen
	for (int i = 0; i < 144; i++) {
		for (int k = 0; k < 160; i++) {
			pixels[i*k * 4] = 0x77;
			pixels[i*k * 4 + 1] = 0x77;
			pixels[i*k * 4 + 2] = 0x77;
			pixels[i*k * 4 + 3] = 255;
		}
	}



	//return pixels;
}

void GPU::writeScanLine(uint8_t * pixels)
{	
	uint8_t lcdControl = mem->ReadByte(0xFF40);

	dispEnable = (lcdControl >> 7) & 1;
	mapSelect = (lcdControl >> 6) & 1;
	windowEnable = (lcdControl >> 5) & 1;
	tileSelect = (lcdControl >> 4) & 1;
	bgTileSelect = (lcdControl >> 3) & 1;
	spriteSize = (lcdControl >> 2) & 1;
	spriteEnable = (lcdControl >> 1) & 1;
	bgDisplay = (lcdControl >> 0) & 1;


	if ((lcdControl >> 0) & 1)
		RenderTile();
	if ((lcdControl >> 1) & 1)
		RenderSprite();
}

void GPU::RenderTile()
{
	uint16_t tileData = 0;
	uint16_t backgroundMemory = 0;
	bool unsig = true;
	uint8_t scry = mem->ReadByte(0xFF42);
	uint8_t scrx = mem->ReadByte(0xFF43);
	uint8_t winy = mem->ReadByte(0xFF4A);
	uint8_t winx = mem->ReadByte(0xFF4B) - 7;

	bool usingWindow = false;

	//Check if window is enabled
	if (windowEnable) {
		//check current scanline position
		if (winy <= mem->ReadByte(0xFF44))
			usingWindow = true;
	}

	//check which tileset in use
	if (tileSelect) {
		tileData = 0x8000;
	}
	else {
		tileData = 0x8800;
		unsig = false;
	}
	//choose background or window memory
	if (!usingWindow) {
		if (bgTileSelect)
			backgroundMemory = 0x9C00;
		else
			backgroundMemory = 0x9800;
	}
	else {
		if (mapSelect) 
			backgroundMemory = 0x9C00;
		else
			backgroundMemory = 0x9800;
	}

	//used to calculate which of the 32 vertical tiles current
	//scanline is drawing
	uint8_t yPos = 0;

	if (!usingWindow)
		yPos = scry + mem->ReadByte(0xFF44);
	else
		yPos = mem->ReadByte(0xFF44) - winy;

	//get correct pixels of tile for scanline
	uint16_t tileRow = (((uint16_t)(yPos / 8)) * 32);

	//begin drawing pixels on line
	for (int i = 0; i < 160; i++) {
		uint8_t xPos = i + scrx;
		if (usingWindow)
			if (i >= winx)
				xPos = i - winx;

		uint8_t tilCol = (xPos / 8);
		int16_t tileNum;
		uint16_t tileAddr = backgroundMemory + tileRow + tilCol;

		if (unsig)
			tileNum = (uint8_t)mem->ReadByte(tileAddr);
		else
			tileNum = (int8_t)mem->ReadByte(tileAddr);

		uint16_t tileLocation = tileData;

		if (unsig)
			tileLocation += (tileNum * 16);
		else
			tileLocation += ((tileNum + 128) * 16);

		uint8_t line = yPos % 8;
		line *= 2;	//each line takes 2 bytes of memory
		uint8_t data1 = mem->ReadByte(tileLocation + line);
		uint8_t data2 = mem->ReadByte(tileLocation + line + 1);

		int colorbit = xPos % 8;
		colorbit -= 7;
		colorbit *= -1;

		int colorNum = (data2 >> colorbit) & 1;
		colorNum <<= 1;
		colorNum |= (data1 >> colorbit) & 1;

		//get color pallette from 0xFF47
		uint8_t color[4];
		getColor(colorNum, 0xFF47, color);
		
		int ending = mem->ReadByte(0xFF44);

		//safety check
		if (!(ending < 0 || ending>143 || i < 0 || i > 159))
			return;
		
		slate[i*ending * 4] = color[0];
		slate[i*ending * 4 + 1] = color[1];
		slate[i*ending * 4 + 2] = color[2];
		slate[i*ending * 4 + 3] = color[3];
	}
}

void GPU::getColor(int colorNum, uint16_t addr, uint8_t * slate) {
	uint8_t pallette = mem->ReadByte(addr);
	int hi = 0;
	int lo = 0;

	switch (colorNum) {
	case 0: hi = 1; lo = 0; break;
	case 1: hi = 3; lo = 2; break;
	case 2: hi = 5; lo = 4; break;
	case 3: hi = 7; lo = 6; break;
	}

	int color = 0;
	color = ((pallette >> hi) & 1) << 1;
	color |= ((pallette >> lo) & 1);

	switch (color) {
	case 0:
		slate[0] = 255;
		slate[1] = 255;
		slate[3] = 255;
		slate[4] = 255;
		break;
	case 1:
		slate[0] = 0xCC;
		slate[1] = 0xCC;
		slate[3] = 0xCC;
		slate[4] = 255;
		break;
	case 2:
		slate[0] = 0x77;
		slate[1] = 0x77;
		slate[3] = 0x77;
		slate[4] = 255;
		break;
	case 3:
		slate[0] = 0;
		slate[1] = 0;
		slate[3] = 0;
		slate[4] = 255;
		break;
	}
}


void GPU::RenderSprite()
{
	bool use8x16 = false;
	if (spriteSize)
		use8x16 = true;

	for (int sprite = 0; sprite < 40; sprite++) {
		uint8_t index = sprite * 4;
		uint8_t yPos = mem->ReadByte(0xFE00 + index) - 16;
		uint8_t xPos = mem->ReadByte(0xFE00 + index + 1) - 8;
		uint8_t tileLoc = mem->ReadByte(0xFE00 + index + 2);
		uint8_t attributes = mem->ReadByte(0xFE00 + index + 3);

		bool yFlip = (attributes >> 6) & 1;
		bool xFlip = (attributes >> 5) & 1;

		int scanline = mem->ReadByte(0xFF44);

		int ySize = 8;

		if (use8x16)
			ySize = 16;

		//check if sprite intersects with scanline
		if ((scanline >= yPos) && (scanline < (yPos + ySize))) {
			int line = scanline - yPos;

			//read sprite backward into y axis
			if (yFlip) {
				line -= ySize;
				line *= -1;
			}

			line *= 2;	//same as for tiles

			uint16_t dataAddr = (0x8000 + (tileLoc * 16)) + line;
			uint8_t data1 = mem->ReadByte(dataAddr);
			uint8_t data2 = mem->ReadByte(dataAddr + 1);

			//read from right to left
			for (int tilePix = 7; tilePix >= 0; tilePix--) {
				int colorBit = tilePix;
				if (xFlip) {
					colorBit -= 7;
					colorBit *= -1;
				}

				//rest is same as for tiles
				int colorNum = (data2 >> colorBit) & 1;
				colorNum <<= 1;
				colorNum |= (data1 >> colorBit) & 1;

				//get color pallette from color address
				uint16_t colorAddr = ((attributes >> 4) & 1) ? 0xFF49 : 0xFF48;

				uint8_t color[4];
				getColor(colorNum, colorAddr, color);

				int xPix = 0 - tilePix;
				xPix += 7;

				int ending = xPos + xPix;

				//safety check
				if (!(scanline < 0 || ending>143 || ending < 0 || ending > 159))
					return;

				slate[ending* scanline * 4] = color[0];
				slate[ending * scanline * 4 + 1] = color[1];
				slate[ending * scanline * 4 + 2] = color[2];
				slate[ending * scanline * 4 + 3] = color[3];
			}
		}
	}
}


/*
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
}*/

