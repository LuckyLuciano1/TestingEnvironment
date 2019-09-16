#pragma once
const int SCREENW = 800;
const int SCREENH = 800;
enum ID { NONE, BOX, GROUND };
enum COLLISIONID { LINE, SQUARE, CIRCLE, POINT };//circle and point currently unimplemented

enum KEYS { W, A, S, D, ESCAPE, LSHIFT, SPACEBAR, LMOUSE, RMOUSE, UP, DOWN, LEFT, RIGHT, ENTER };
const int KEYNUMBER = 14;

enum GAMESTATE { TITLE, LEVEL };
enum UIELEMENT { DEATHSCREEN, SETTINGS, OPTIONS, STARTSCREEN };//elements of the UI displayed on top of the gamestate