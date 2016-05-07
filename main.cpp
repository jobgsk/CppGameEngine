

#include <functional>
#include <exception>
#include <iostream>
#include "GameManager.h"


GameManager *app;

void __keyboard(unsigned char key, int x, int y)
{
	tanks::ButtonControlls button = tanks::ButtonControlls::NONE;

	if (key == 'w')
		button = tanks::ButtonControlls::MOVE_UP;
	else if (key == 's')
		button = tanks::ButtonControlls::MOVE_DOWN;

	else if (key == 'q')
		button = tanks::ButtonControlls::MOVE_LEFT;
	else if (key == 'e')
		button = tanks::ButtonControlls::MOVE_RIGHT;
	
	else if (key == 'a')
		button = tanks::ButtonControlls::TURN_LEFT;
	else if (key == 'd')
		button = tanks::ButtonControlls::TURN_RIGHT;
	
	else if (key == 'm')
		button = tanks::ButtonControlls::SHOW_MAP;
	else if (key == 'n')
		button = tanks::ButtonControlls::SHOW_GAME;

	else if (key == 'f')
		button = tanks::ButtonControlls::SHOOT;
	else if (key == 'j')
		button = tanks::ButtonControlls::JUMP;

	else if ((int)key == 27)
		button = tanks::ButtonControlls::ESCAPE;
	else if ((int)key == 13)
		button = tanks::ButtonControlls::ENTER;

	app->keyboard(button);
}

void __keyboard_up(unsigned char key, int x, int y)
{
	app->keyboard(tanks::ButtonControlls::NONE);
}

bool pressed = false;
void __mouse_button(int button, int state, int x, int y)
{
	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			pressed = false;
			app->mouse_release(button, state, x, y);
		}
		else {// state = GLUT_DOWN
			pressed = true;
			app->mouse_press(button, state, x, y);
		}
	}
}

void __mouse_move(int x, int y) {

	app->mouse_move(x, y);
}

void __update()
{
	app->update();
}


void __display()
{
	auto fp = std::bind(&GameManager::display, app);
	Graphics::Display(fp);
}

void __reshape(int w, int h)
{
	Graphics::Reshape(w, h);
};


void __callbacks()
{

	glutKeyboardFunc(__keyboard);
	glutKeyboardUpFunc(__keyboard_up);

	glutDisplayFunc(__display);
	glutReshapeFunc(__reshape);
	glutIdleFunc(__update);

	// here are the two new functions
	glutMouseFunc(__mouse_button);
	glutMotionFunc(__mouse_move);

}

int main(int argc, char** argv)
{
	try
	{
		Graphics *gl = new Graphics(argc, argv, "Test");
		app = new GameManager();
		app->init();
		__callbacks();
		app->run();

	}
	catch (std::exception& e)
	{
		std::cout << " error " << &e << std::endl;
		std::cin.ignore();
	}

	return EXIT_SUCCESS;
}
