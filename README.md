# VGBC
Virtual Gameboy Color

My purpose with this project is firstly to create a working gameboy color emulator, but to also create a program that allows to look deeper into the inner workings of a game.  I want a user to be able to see and manipulate memory and register values while the game is running, and go step by step through each instruction run.  It's someting I've alwyas wanted from an emulator, but rarely find.  There is one program, no$gmb that does this, but I find the interface clunky, plus the program itself hasn't been updated in 15 years.  You can find it [here](http://problemkaputt.de/gmb.htm).  

A longer term goal with this project is allowing games to be played directly from a cartraige, instead of downloaded ROMs.  The emulator would be ran on a raspberry pi, with another program reading from the cartraige then feeding the data to the emulator.  This would be paired with hardware that allows the pi to correctly address and trade data with a cartraige. 

The first game will probably be Tetris, because of how simple the game cartraige is.  There is no memory bank switching, where instead the game code is transferred from the cartraige to in game ram.  This also means once the code is transferred, the cartraige can even be removed with no effect to the game experience.  This can onlt be done on special hardware, because the Gameboy had an internal switch that reset the handheld when a button is not depressed.  The Tetris raw code is only 32kb, so it is able to be completly stored in ram.




##Sources of information and help
[Gameboy Programming Manual](http://www.chrisantonellis.com/files/gameboy/gb-programming-manual.pdf)

[Gameboy CPU Manual](http://marc.rawer.de/Gameboy/Docs/GBCPUman.pdf)

[GB Opcodes](http://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html)

[Emubase Pan Docs](https://web.archive.org/web/20080208182406/http://nocash.emubase.de/pandocs.htm)

[GB Memory Controllers](http://www.reinerziegler.de/cgbmbc5.pdf)

[GameBoy Cartridges](http://fms.komkon.org/GameBoy/Tech/Carts.html)

[CodeSlogner Gameboy](http://www.codeslinger.co.uk/pages/projects/gameboy.html)

[Emulation in Javascript](http://imrannazar.com/GameBoy-Emulation-in-JavaScript:-Graphics)

[Bit manipulation on stack overflow](https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit-in-c-c)

[Overview of MBC types](http://gbdev.gg8.se/wiki/articles/Memory_Bank_Controllers)















