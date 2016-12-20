#ifndef MEM_H
#define MEM_H

using namespace std;

class MEM{

	private:
		const uint8_t BIOS[0x100] = {
0x31, 0xFE, 0xFF, 0xAF, 0x21, 0xFF, 0x9F, 0x32, 0xCB, 0x7C, 0x20, 0xFB, 0x21, 0x26, 0xFF, 0x0E, 0x11, 0x3E, 0x80, 0x32, 0xE2, 0x0C, 0x3E, 0xF3, 0xE2, 0x32, 0x3E, 0x77, 0x77, 0x3E, 0xFC, 0xE0, 0x47, 0x11, 0x04, 0x01, 0x21, 0x10, 0x80, 0x1A, 0xCD, 0x95, 0x00, 0xCD, 0x96, 0x00, 0x13, 0x7B, 0xFE, 0x34, 0x20, 0xF3, 0x11, 0xD8, 0x00, 0x06, 0x08, 0x1A, 0x13, 0x22, 0x23, 0x05, 0x20, 0xF9, 0x3E, 0x19, 0xEA, 0x10, 0x99, 0x21, 0x2F, 0x99, 0x0E, 0x0C, 0x3D, 0x28, 0x08, 0x32, 0x0D, 0x20, 0xF9, 0x2E, 0x0F, 0x18, 0xF3, 0x67, 0x3E, 0x64, 0x57, 0xE0, 0x42, 0x3E, 0x91, 0xE0, 0x40, 0x04, 0x1E, 0x02, 0x0E, 0x0C, 0xF0, 0x44, 0xFE, 0x90, 0x20, 0xFA, 0x0D, 0x20, 0xF7, 0x1D, 0x20, 0xF2, 0x0E, 0x13, 0x24, 0x7C, 0x1E, 0x83, 0xFE, 0x62, 0x28, 0x06, 0x1E, 0xC1, 0xFE, 0x64, 0x20, 0x06, 0x7B, 0xE2, 0x0C, 0x3E, 0x87, 0xE2, 0xF0, 0x42, 0x90, 0xE0, 0x42, 0x15, 0x20, 0xD2, 0x05, 0x20, 0x4F, 0x16, 0x20, 0x18, 0xCB, 0x4F, 0x06, 0x04, 0xC5, 0xCB, 0x11, 0x17, 0xC1, 0xCB, 0x11, 0x17, 0x05, 0x20, 0xF5, 0x22, 0x23, 0x22, 0x23, 0xC9, 0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E, 0x3C, 0x42, 0xB9, 0xA5, 0xB9, 0xA5, 0x42, 0x3C, 0x21, 0x04, 0x01, 0x11, 0xA8, 0x00, 0x1A, 0x13, 0xBE, 0x20, 0xFE, 0x23, 0x7D, 0xFE, 0x34, 0x20, 0xF5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20, 0xFB, 0x86, 0x20, 0xFE, 0x3E, 0x01, 0xE0, 0x50};	//basic bios;
		uint8_t rom[0xFF][0x4000];	//16k Memory banks
		uint8_t vram[0x2000];	//8k of video ram 0x8000 - 0x9FFF
		uint8_t eram[0x2000];	//8k of external ram 0xA000 - 0xBFFF
		uint8_t wram[0x1000];	//4k of working ram 0xC000 - 0xCFFF, copied to 0xE000 - 0xFDFF
		uint8_t bram[0xF][0x1000];	//4k of banked ram 0xD000 - 0xDFFF
				
		uint8_t oam[0x9F];		//Hold display data for 40 objects 0xFE00 - 0xFE9F
        uint8_t zram[0x80];		//port/mode, control, sound registers 0xFF00 - 0xFF7F
		uint8_t hram[0x7E];		//Working and stack ram 0xFF80 - 0xFFFE
		
		uint8_t intFlag;		//Interupt flag register 0xFF0F
		uint8_t intEnable;		//Interupt flags enable/disable
		
		uint8_t romBankType;
        uint8_t activeRomBank = 0;
		
		uint8_t ramBankSize;
		uint8_t ramEnable;
		uint8_t activeRAmBank = 0;
				
		uint8_t biosLoaded;
		
		uint16_t stackPointer;
		
		void handleBanking(uint16_t, uint8_t);
		
		void RAMBankEnable(uint16_t, uint8_t);
		void ChangeLoRomBank(uint8_t);
		void ChangeHiRomBank(uint8_t);
		void RamBankChange(uint8_t);
		void ChangeROMRAMMode(uint8_t);
		
	public:
		MEM();
		~MEM();
		
		uint8_t ReadByte(uint16_t addr);		//Read byte from addr
		uint16_t ReadWord(uint16_t addr);	//Read word from addr
		
		void WriteByte(uint16_t addr, uint8_t data);	//write byte of data to memory space addr
		void WriteWord(uint16_t addr, uint16_t data);	//Write word of data to memory space addr
		
		void loadRom(const char *fname);	//Load game rom into memory
		
		void pushtoStack(uint16_t);
		uint16_t popoffStack();
		
};

#endif