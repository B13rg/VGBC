#ifndef MEM_H
#define MEM_H

using namespace std;

class c_MEM{

	private:
		const uint8_t BIOS[0x100];	//basic bios;
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
		c_MEM();
		~c_MEM();
		
		uint8_t ReadByte(uint16_t addr);		//Read byte from addr
		uint16_t ReadWord(uint16_t addr);	//Read word from addr
		
		void WriteByte(uint16_t addr, uint8_t data);	//write byte of data to memory space addr
		void WriteWord(uint16_t addr, uint16_t data);	//Write word of data to memory space addr
		
		void loadRom(const char *fname);	//Load game rom into memory
		
		void pushtoStack(uint16_t);
		uint16_t popoffStack();
		
};

#endif