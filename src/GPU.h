#IFNDEF	GPU_H
#DEFINE GPU_H

class video{
	private:
		int dispEnable;		//bit 7: LCD Display enable 0=off, 1=on
		int mapSelect;		//bit 6: Tile map select 0=9800-9BFF, 1=9C00-9FFF
		int windowEnable;	//bit 5: Window display enable 0=0ff, 1=on
		int tileSelect;		//bit 4: BG & window data select 0=8800-97FF, 1=8000-8FFF
		int bgTileSelect;	//bit 3: BG tile map display select 0=9800-9BFF, 1=9C00-9FFF
		int spriteSize;		//bit 2: Sprite Size 0=8x8, 1=8x16
		int spriteEnable;	//bit 1: Bit 5 for sprites
		int bgDisplay;		//bit 0: Bit 5 and 1 for background 0=off, 1=on
	public:
	
};