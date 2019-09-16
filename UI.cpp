#include "UI.h"

UI::UI()
{
	cursorX = 0;
	cursorY = 0;

	settingsX = 0;
	optionsX = 0;

	settingsYcursormax = 0;
	optionsYcursormax = 2;

	settingsboundX = 180;
	optionsboundX = 200;

	running = true;
}

void UI::Init(ALLEGRO_FONT *font18)
{
	if (font18 != NULL) {
		UI::font18 = font18;
	}
	//images here
}

void UI::Update(bool keys[], float keytimer[], int GameState)
{
	InputUpdate(keys, keytimer);
	PositionUpdate(keys, keytimer);
}

void UI::Render()
{
	//OPTIONS MENU///////////////////////////////////////////////////////////////
	al_draw_filled_rectangle(0, 0, optionsX, SCREENH, al_map_rgb(255, 255, 255));
	
	if (UIState[OPTIONS] != OFF && (UIState[SETTINGS] == OFF || UIState[SETTINGS] == DEACTIVATING))//drawing cursor on options menu
	{
		al_draw_filled_rectangle(0, 200+(cursorY*50), optionsX, 250 + (cursorY*50), al_map_rgb(215, 215, 215));
	}
	//draw text options:
	al_draw_text(font18, al_map_rgb(0, 0, 0), optionsX - 10, 200, ALLEGRO_ALIGN_RIGHT, "QUIT");
	al_draw_text(font18, al_map_rgb(0, 0, 0), optionsX - 10, 250, ALLEGRO_ALIGN_RIGHT, "RESTART");
	al_draw_text(font18, al_map_rgb(0, 0, 0), optionsX - 10, 300, ALLEGRO_ALIGN_RIGHT, "SETTINGS");


	//SETTINGS MENU//////////////////////////////////////////////////////////////
	al_draw_filled_rectangle(0, 0, settingsX, SCREENH, al_map_rgb(235, 235, 235));
	
	if (UIState[SETTINGS] == ON || UIState[SETTINGS] == ACTIVATING)//drawing cursor on settings menu
	{
		al_draw_filled_rectangle(0, 200 + (cursorY * 50), settingsX, 250 + (cursorY * 50), al_map_rgb(195, 195, 195));
	}
	//draw text settings:
	al_draw_text(font18, al_map_rgb(0, 0, 0), settingsX - 10, 200, ALLEGRO_ALIGN_RIGHT, "VOLUME");
}


void UI::InputUpdate(bool keys[], float keytimer[])
{
	if (keys[LEFT] && keytimer[LEFT] == 0.0f)//if the left key is pressed
		cursorX--;
	if (keys[RIGHT] && keytimer[RIGHT] == 0.0f)//if the right key is pressed
		cursorX++;
	if (keys[UP] && keytimer[UP] == 0.0f)//if the up key is pressed
		cursorX = 0, cursorY--;
	if (keys[DOWN] && keytimer[DOWN] == 0.0f)//if the down key is pressed
		cursorX = 0, cursorY++;

	if (keys[ESCAPE] && keytimer[ESCAPE] == 0.0f && (UIState[OPTIONS] == OFF || UIState[OPTIONS] == DEACTIVATING) && UIState[SETTINGS] == OFF)//go to options menu
		UIState[OPTIONS] = ACTIVATING,
		cursorX = 0,
		cursorY = 0;

	else if (keys[ESCAPE] && keytimer[ESCAPE] == 0.0f && UIState[OPTIONS] == ON && (UIState[SETTINGS] == ON || UIState[SETTINGS] == ACTIVATING))//go back to options menu (if on settings menu)
		UIState[SETTINGS] = DEACTIVATING;

	else if (keys[ESCAPE] && keytimer[ESCAPE] == 0.0f && (UIState[OPTIONS] == ON || UIState[OPTIONS] == ACTIVATING) && UIState[SETTINGS] == OFF)//exiting options menu
		UIState[OPTIONS] = DEACTIVATING;


	if (UIState[OPTIONS] == ON && UIState[SETTINGS] == OFF)//if in options menu
	{
		if (cursorY > optionsYcursormax)//looping cursor
			cursorY = 0;
		else if (cursorY < 0)
			cursorY = optionsYcursormax;

		if (keys[ENTER] && keytimer[ENTER] == 0.0f) {//if the enter key is pressed
			OptionsMenu(cursorY);
		}

	}
	else if (UIState[SETTINGS] == ON)//if in settings menu
	{
		if (cursorY > settingsYcursormax)//looping cursor
			cursorY = 0;
		else if (cursorY < 0)
			cursorY = settingsYcursormax;

		if (keys[ENTER] && keytimer[ENTER] == 0.0f) {//if the enter key is pressed
			SettingsMenu(cursorY);
		}
	}
}

void UI::PositionUpdate(bool keys[], float keytimer[])
{
	if (UIState[SETTINGS] == ACTIVATING)
	{
		if (settingsX >= settingsboundX)
			UIState[SETTINGS] = ON;
		else
			settingsX += 10;
	}
	else if (UIState[SETTINGS] == DEACTIVATING)
	{
		if (settingsX + settingsboundX <= 0)
			UIState[SETTINGS] = OFF,
			cursorX = 0,
			cursorY = 0;
		else
			settingsX -= 10;
	}

	if (UIState[OPTIONS] == ACTIVATING)
	{
		if (optionsX >= optionsboundX)
			UIState[OPTIONS] = ON;
		else
			optionsX += 10;
	}
	else if (UIState[OPTIONS] == DEACTIVATING)
	{
		if (optionsX + optionsboundX <= 0)
			UIState[OPTIONS] = OFF,
			cursorX = 0,
			cursorY = 0;
		else
			optionsX -= 10;
	}
}

void UI::OptionsMenu(int cursorY)
{
	switch (cursorY)
	{
	case 0://QUIT
		running = false;
		break;
	case 1://RESTART
		break;
	case 2://SETTINGS
		UIState[SETTINGS] = ACTIVATING;
		cursorX = 0;
		cursorY = 0;
		break;
	}
}

void UI::SettingsMenu(int cursorY)
{
	switch (cursorY)
	{
	case 0://VOLUME
		break;
	}
}