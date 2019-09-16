#include "Engine.h"

Engine::Engine(float FPS)//constructor
{
	render = true;
	running = true;
	frames = 0;
	engineTime = 0;
	engineFPS = 0;

	GameState = TITLE;

	Engine::FPS = FPS;


	//ALLEGRO setup:

	srand(time(NULL));//seeding random command with computer clock

	al_init();//starting allegro
	al_init_primitives_addon();//basic drawing commands - lines, boxes
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	al_install_keyboard();
	al_install_mouse();

	//defining timer, display, and queue
	display = al_create_display(SCREENW, SCREENH);
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	font18 = al_load_ttf_font("arial.ttf", 18, 0);
	UI.Init(font18);
	//level.Init()

	//logging timer and display as items that can be in event queue
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_flip_display();
	al_start_timer(timer);
}
void Engine::GameLoop() {

	while (running) {//runs until 'break' command is used
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		GameEventManager(ev);//enclosed is keyboard events, update section, and closing of display window via red 'X'
		
		//render section
		if (render && al_is_event_queue_empty(event_queue))//if event_timer has run, as well as no events within keyboard input or anything else, render
			GameRender();
	}

	Close();//closes out all necessary timers, displays, etc.
}

void Engine::GameEventManager(ALLEGRO_EVENT ev)
{
	switch (ev.type)
	{
	//keyboard input
	case ALLEGRO_EVENT_KEY_DOWN://key being pressed down
		EventKeyDown(ev);
		break;
	case ALLEGRO_EVENT_KEY_UP://key being released
		EventKeyUp(ev);
		break;

	//mouse input
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		al_get_mouse_state(&state);
		if (state.buttons & 1)
			keys[LMOUSE] = true,
			lmouseup = 0.0f;
		if (state.buttons & 2)
			keys[RMOUSE] = true,
			rmouseup = 0.0f;
		break;
	case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		al_get_mouse_state(&state);
		if (!state.buttons & 1)
			keys[LMOUSE] = false,
			keytimer[LMOUSE] = 0.0f;
		if (!state.buttons & 2)
			keys[RMOUSE] = false,
			keytimer[RMOUSE] = 0.0f;
		break;
	case ALLEGRO_EVENT_MOUSE_AXES://mouse being moved
		mouseX = ev.mouse.x;
		mouseY = ev.mouse.y;
		break;
	
	//window closing- makes red 'X' functional
	case ALLEGRO_EVENT_DISPLAY_CLOSE:
		running = false;
		break;

	//update section
	case ALLEGRO_EVENT_TIMER://timer increments (?)
		GameUpdate();
		break;
	}
}

void Engine::GameUpdate()//updates object position, culls deleted objects, addresses user input 
{
	render = true;

	//updating FPS
	frames++;
	if (al_current_time() - engineTime >= 1)
	{
		engineTime = al_current_time();
		engineFPS = frames;
		frames = 0;
	}

	//managing keyboard/mouse input:

	UI.Update(keys, keytimer, GameState);//keyboard input (+ other updating) related to the UI menus
	
	if (!UI.running)//quitting game if signalled by UI input
		running = false;

	if (keys[LMOUSE])
	{}
	else
		lmouseup += 1.0f / FPS;//timing how long the mouse buttons have been released for

	if (keys[RMOUSE])
	{}
	else
		rmouseup += 1.0f / FPS;

	//tracking how long a key is being held for
	for (int x = 0; x < KEYNUMBER; x++)
	{
		if (keys[x])
			keytimer[x] += (1.0f / FPS);
	}

	if(GameState == LEVEL)
		level.LevelUpdate();
}

void Engine::GameRender()
{
	render = false;

	//rendering objects

	if(GameState == LEVEL)
		level.LevelRender();
	
	UI.Render();

	al_flip_display();//drawing to screen
	al_clear_to_color(al_map_rgb(0, 0, 0));//clearing screen	
}

void Engine::EventKeyDown(ALLEGRO_EVENT ev)
{
	switch (ev.keyboard.keycode)
	{
	case ALLEGRO_KEY_ESCAPE:
		keys[ESCAPE] = true;
		break;
	case ALLEGRO_KEY_W:
		keys[W] = true;
		break;
	case ALLEGRO_KEY_A:
		keys[A] = true;
		break;
	case ALLEGRO_KEY_S:
		keys[S] = true;
		break;
	case ALLEGRO_KEY_D:
		keys[D] = true;
		break;
	case ALLEGRO_KEY_SPACE:
		keys[SPACEBAR] = true;
		break;
	case ALLEGRO_KEY_LSHIFT:
		keys[LSHIFT] = true;
		break;
	case ALLEGRO_KEY_UP:
		keys[UP] = true;
		break;
	case ALLEGRO_KEY_DOWN:
		keys[DOWN] = true;
		break;
	case ALLEGRO_KEY_LEFT:
		keys[LEFT] = true;
		break;
	case ALLEGRO_KEY_RIGHT:
		keys[RIGHT] = true;
		break;
	case ALLEGRO_KEY_ENTER:
		keys[ENTER] = true;
		break;
	}
}
void Engine::EventKeyUp(ALLEGRO_EVENT ev)
{
	switch (ev.keyboard.keycode)
	{
	case ALLEGRO_KEY_ESCAPE:
		keys[ESCAPE] = false;
		keytimer[ESCAPE] = 0.0f;
		break;
	case ALLEGRO_KEY_W:
		keys[W] = false;
		keytimer[W] = 0.0f;
		break;
	case ALLEGRO_KEY_A:
		keys[A] = false;
		keytimer[A] = 0.0f;
		break;
	case ALLEGRO_KEY_S:
		keys[S] = false;
		keytimer[S] = 0.0f;
		break;
	case ALLEGRO_KEY_D:
		keys[D] = false;
		keytimer[D] = 0.0f;
		break;
	case ALLEGRO_KEY_SPACE:
		keys[SPACEBAR] = false;
		keytimer[SPACEBAR] = 0.0f;
		break;
	case ALLEGRO_KEY_LSHIFT:
		keys[LSHIFT] = false;
		keytimer[LSHIFT] = 0.0f;
		break;
	case ALLEGRO_KEY_UP:
		keys[UP] = false;
		keytimer[UP] = 0.0f;
		break;
	case ALLEGRO_KEY_DOWN:
		keys[DOWN] = false;
		keytimer[DOWN] = 0.0f;
		break;
	case ALLEGRO_KEY_LEFT:
		keys[LEFT] = false;
		keytimer[LEFT] = 0.0f;
		break;
	case ALLEGRO_KEY_RIGHT:
		keys[RIGHT] = false;
		keytimer[RIGHT] = 0.0f;
		break;
	case ALLEGRO_KEY_ENTER:
		keys[ENTER] = false;
		keytimer[ENTER] = 0.0f;
		break;
	}
}

void Engine::Close()
{
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	al_uninstall_keyboard();
	al_uninstall_mouse();
}