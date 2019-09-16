#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <list>
#include <iostream>
using namespace std;

#include "Globals.h"

class UI
{
public:
	UI();
	void Init(ALLEGRO_FONT *font18 = NULL);
	void Update(bool keys[], float keytimer[], int GameState);
	void Render();
	
	bool running;

private:
	void InputUpdate(bool keys[], float keytimer[]);
	void PositionUpdate(bool keys[], float keytimer[]);

	void SettingsMenu(int cursorY);
	void OptionsMenu(int cursorY);

	ALLEGRO_FONT *font18;

	enum UISTATE { OFF, ON, ACTIVATING, DEACTIVATING };//status of uielements
	int UIState[4] = {OFF, OFF, OFF, OFF};//state of UI elements 

	int cursorX;
	int cursorY;

	int settingsYcursormax;
	int optionsYcursormax;

	int settingsX;
	int optionsX;

	float settingsboundX;
	float optionsboundX;
};