#include "emulator.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>

using namespace std;

Emulator emu;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


/* demo image code
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!", sf::Style::None);
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	window.setVerticalSyncEnabled(true);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
*/

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR lpCmdLine, int nCMDShow) {
	//Register the window classname
	const TCHAR CLASS_NAME[] = TEXT("Visual Gameboy Color");

	WNDCLASS wc = {};

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	//create the window
	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		TEXT("Visual Gameboy Color"),    // Window text
		WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,            // Window style

								  // Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, 816, 615,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
		);
	
	//create sfml window that goes inside hwnd from above
	DWORD Style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS;
	HWND mainView = CreateWindowEx(0, "STATIC", NULL, Style, 0, 0, 800, 600, hwnd, NULL, hInstance, NULL);
	
	//define the sfml view
	sf::Vector2u windowSize;
	sf::FloatRect pixelSize;

	sf::RenderWindow SFMLView(mainView);
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	SFMLView.setVerticalSyncEnabled(true);

	const unsigned int W = 160;
	const unsigned int H = 144;

	sf::Uint8* pixels = new sf::Uint8[W*H * 4];

	sf::Texture texture;
	texture.create(W, H);

	sf::Sprite sprite; // needed to draw the texture on screen




	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, nCMDShow);

	// Run the message loop.

	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//clear view
			SFMLView.clear();
			////////////////
			
			emu.update(pixels);

			/* test code for making blue side borders and green top and bottom borders
			for(int i = 0; i < W*H*4; i += 4) {
				pixels[i] = 255;
				pixels[i+1] = 1;
				pixels[i + 2] = 0;
				pixels[i + 3] = 255;
				if (i % (W * 4) == 159*4) {
					pixels[i] = 0;
					pixels[i + 1] = 0;
					pixels[i + 2] = 255;
					pixels[i + 3] = 255;
				}
				if (i % (W * 4) == 0) {
					pixels[i] = 0;
					pixels[i + 1] = 0;
					pixels[i + 2] = 255;
					pixels[i + 3] = 255;
				}
			}*/

			cout << "Setup pixel coloring" << endl;
			texture.update(pixels);
			sprite.setTexture(texture);
			
			//get size of window and sprite in pixels
			windowSize = SFMLView.getSize();
			pixelSize = sprite.getLocalBounds();

			//get scale with which to change the sprite
			windowSize.x = windowSize.x / pixelSize.width;
			windowSize.y = windowSize.y / pixelSize.height;

			sprite.setScale(sf::Vector2f(windowSize));

			SFMLView.draw(sprite);
	
			//write to screen
			SFMLView.display();
		}
	}
	
	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	uint8_t controller;

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		//all painting occurs here

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
		return 0;
	}
	controller = emu.mem->ReadByte(0xFF00);

	case WM_KEYDOWN: {
		controller = emu.mem->ReadByte(0xFF00);
		switch (wParam) {
		case 'W': {	//up
			if((controller >> 4) & 1)
				controller |= 1 << 2;
		}
		case 'A': {	//left
			if ((controller >> 4) & 1)
			controller |= 1 << 1;
		}
		case 'S': {	//down
			if ((controller >> 4) & 1)
			controller |= 1 << 3;
		}
		case 'D': {	//right
			if ((controller >> 4) & 1)
			controller |= 1 << 0;
		}
		case 'M': {	//B
			if ((controller >> 5) & 1)
				controller |= 1 << 1;
		}
		case 'K' : {	//A
			if ((controller >> 5) & 1)
				controller |= 1 << 0;
		}
		case 'V': {	//Select
			if ((controller >> 5) & 1)
				controller |= 1 << 2;
		}
		case 'B': {	//Start
			if ((controller >> 5) & 1)
				controller |= 1 << 3;
		}
		}
		emu.mem->WriteByte(0xFF00, controller);
		return 0;
	}

	case WM_KEYUP: {
		controller = emu.mem->ReadByte(0xFF00);
		switch (wParam) {
		case 'W': {	//up
			if ((controller >> 4) & 1)
				controller |= 0 << 2;
		}
		case 'A': {	//left
			if ((controller >> 4) & 1)
				controller |= 0 << 1;
		}
		case 'S': {	//down
			if ((controller >> 4) & 1)
				controller |= 0 << 3;
		}
		case 'D': {	//right
			if ((controller >> 4) & 1)
				controller |= 0 << 0;
		}
		case 'M': {	//B
			if ((controller >> 5) & 1)
				controller |= 0 << 1;
		}
		case 'K': {	//A
			if ((controller >> 5) & 1)
				controller |= 0 << 0;
		}
		case 'V': {	//Select
			if ((controller >> 5) & 1)
				controller |= 0 << 2;
		}
		case 'B': {	//Start
			if ((controller >> 5) & 1)
				controller |= 0 << 3;
		}
		}
		emu.mem->WriteByte(0xFF00, controller);
		return 0;
	}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


