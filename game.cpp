//============================================================================
// Name          : Eman Furrukh.cpp
// Author        : FAST DS Department
// Version       : 2022
// Copyright   : (c) Reserved
// Description : Basic 2D Atari Game...
//============================================================================

#ifndef RushHour_CPP_
#define RushHour_CPP_
#include "util.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;

int menu = 0;
int score = 0;
int array[20][20];
int highscore = 0;
long long int t = 9999999999;
string name1, name2;
int level = 0;
int counter = 0;
bool Right=false;
bool Left=false;
bool Up=false;
bool Down=false;
float x2 = 300; 
float y2 = 46; 
int xI = 400, yI = 400;

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

//this is the class made to create the map of the game as well as the obstacles in it. 
/*class Obstacles {
	int x;
	int y;
	int length;
	int width;
	float color; 
public:
	Obstacles() {
		x = 0;
		y = 0;
		length = 0;
		width = 0;
		color = 0.0;
	}
	Obstacles(int X, int Y, int l, int w, float c) {
		x = X;
		y = Y;
		length = l;
		width = w;
		color = c;
	}*/
	
//function allowing the players car to move.
bool flag = true;
void moveCar() {
	
	if (xI > 10 && flag) {
		xI -= 10;
		cout << "going left";
		if(xI < 100)
			
			flag = false;

	}
	else if (xI < 1010 && !flag) {
		cout << "go right";
		xI += 10;
		if (xI > 900)
			flag = true;
	}
}
//function allowing the bots car to move
void moveBots() {
       if (x2 < 900 && !flag) {
		cout << "go left";
		x2 += 10;
		if (x2 > 200)
			flag = true;
	}
	else if (y2 > 10 && flag) {
		y2 -= 10;
		cout << "go right";
		if(y2 < 800)
			flag = false;
        }
}

//used to display the car i.e type of vehicle. 
void drawCar() {
     	//player car
	float width = 10; 
	float height = 7.5;
	float* color = colors[ORANGE]; 
	float radius = 5.0;
	DrawRoundRect(xI,yI,width,height,color,radius); // bottom left tyre
	DrawRoundRect(xI+width*3,yI,width,height,color,radius); // bottom right tyre
	DrawRoundRect(xI+width*3,yI+height*4,width,height,color,radius); // top right tyre
	DrawRoundRect(xI,yI+height*4,width,height,color,radius); // top left tyre
	DrawRoundRect(xI, yI+height*2, width, height, color, radius/2); // body left rect
	DrawRoundRect(xI+width, yI+height, width*2, height*3, color, radius/2); // body center rect
	DrawRoundRect(xI+width*3, yI+height*2, width, height, color, radius/2); // body right rect*/
	moveCar();
	glutPostRedisplay();
}

void drawBots() {
	//computer controlled car
	float width2 = 10; 
	float height2 = 7.5;
	float* color2 = colors[PURPLE]; 
	float radius2 = 5.0;
	DrawRoundRect(x2,y2,width2,height2,color2,radius2); // bottom left tyre
	DrawRoundRect(x2+width2*3,y2,width2,height2,color2,radius2); // bottom right tyre
	DrawRoundRect(x2+width2*3,y2+height2*4,width2,height2,color2,radius2); // top right tyre
	DrawRoundRect(x2,y2+height2*4,width2,height2,color2,radius2); // top left tyre
	DrawRoundRect(x2, y2+height2*2, width2, height2, color2, radius2/2); // body left rect
	DrawRoundRect(x2+width2, y2+height2, width2*2, height2*3, color2, radius2/2); // body center rect
	DrawRoundRect(x2+width2*3, y2+height2*2, width2, height2, color2, radius2/2); // body right rect
	moveBots();
	glutPostRedisplay();
}

void DrawObstacles() {
	int gap_turn1 = 80;
	int xAxis = 120;
	int yAxis = 120;
	int w1 = 610/2 - gap_turn1/2; // half width
	int h1 = 5;
	float *c1 = colors[BLUE];
	DrawRectangle(xAxis, yAxis, w1, h1, c1); // bottom left
	DrawRectangle(xAxis + w1 + gap_turn1, yAxis, w1, h1, c1); // bottom right
	DrawRectangle(xAxis+w1*2+gap_turn1, yAxis+h1, h1*2, w1, c1); // right down
	DrawRectangle(xAxis+w1*2+gap_turn1, yAxis+h1+w1+gap_turn1, h1*2, w1, c1); // right up
	DrawRectangle(xAxis + w1 + gap_turn1, yAxis+610, w1, h1, c1); // top left
	DrawRectangle(xAxis, yAxis+610, w1, h1, c1); // top right
	DrawRectangle(xAxis-h1*2, yAxis+h1+w1+gap_turn1, h1*2, w1, c1); // left up
	DrawRectangle(xAxis-h1*2, yAxis+h1, h1*2, w1, c1);// left down
}

void DrawMap() {
	if(counter == 1) {
		glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
		glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	     	drawCar();
	     	drawBots();
		//conversion of score intp string to displayed on screen
		string scr=to_string(score);
		DrawString( 510, 803, scr, colors[RED]);
		DrawObstacles();
	}
	if(counter == 2) {
		glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
		glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	     	
	     	//player 1 car
		drawCar();
		//player 2 car
		float width2 = 10; 
		float height2 = 7.5;
		float* color2 = colors[YELLOW]; 
		float radius2 = 5.0;
		DrawRoundRect(x2,y2,width2,height2,color2,radius2); // bottom left tyre
		DrawRoundRect(x2+width2*3,y2,width2,height2,color2,radius2); // bottom right tyre
		DrawRoundRect(x2+width2*3,y2+height2*4,width2,height2,color2,radius2); // top right tyre
		DrawRoundRect(x2,y2+height2*4,width2,height2,color2,radius2); // top left tyre
		DrawRoundRect(x2, y2+height2*2, width2, height2, color2, radius2/2); // body left rect
		DrawRoundRect(x2+width2, y2+height2, width2*2, height2*3, color2, radius2/2); // body center rect
		DrawRoundRect(x2+width2*3, y2+height2*2, width2, height2, color2, radius2/2); // body right rect
		//conversion of score intp string to displayed on screen
		string scr=to_string(score);
		DrawString( 310, 800, scr, colors[ORANGE]);
		DrawString( 710, 800, scr, colors[YELLOW]);
		DrawObstacles();
	}
}
//};
//Obstacles o1(150, 250, 100, 160, 6.0);
//Obstacles o2 (150, 230, 100, 160, 7.0);
//Obstacles o3(150, 120, 100, 160, 5.0);

/*
class Canons {
	int small;
	int medium;
	int large;
};  */



//used to display the helicopter i.e type of vehicle. 
void drawHelicopter() {
	DrawRoundRect(xI, yI, 10, 20, colors[DARK_GREEN], 6.0);
	DrawRectangle(xI+10,yI, 5, 5, colors[DARK_GREEN]);
	DrawSquare(xI+15,yI,5,colors[DARK_GREEN]);
	DrawSquare(xI+6,yI,2,colors[BLACK]);
	DrawSquare(xI+10,yI,2,colors[BLACK]);
	glutPostRedisplay();
}

//used to display the firetruck i.e type of vehicle. 
void drawFiretruck() {
	DrawRectangle(xI,yI, 10, 10, colors[RED]);
	DrawRectangle(xI,yI-3, 10, 2, colors[WHITE]);
	DrawCircle(xI+2,yI,2,colors[BLACK]);
	DrawCircle(xI+5,yI,2,colors[BLACK]);
	glutPostRedisplay();
}


/*
 * Main Canvas drawing function.
 * */

void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	
	
	//this will display the first screen i.e the menu 
	if(menu == 0)
	{
		DrawSquare(  0, 0 ,1000,colors[SKY_BLUE]);
		DrawString( 350, 500, " WELCOME TO ATARI GAME!", colors[BLUE]);
		DrawString( 50+200, 450, "1) Solo", colors[BLUE]);
		DrawString( 50+200, 400, "2) Multiplayer", colors[BLUE]);
		DrawString( 50+200, 350, "3) Settings", colors[BLUE]);
		DrawString( 50+200, 300, "4) Highscores", colors[BLUE]);
		DrawString( 50+200, 250, "5) Credits", colors[BLUE]);
		DrawString( 50+200, 200, "6) QUIT", colors[BLUE]);
	}
	//if user presses 1, it will go inside Solo and ask for the name.
	if(menu == 1)
	{
	       DrawSquare(  0, 0 ,1000,colors[SKY_BLUE]);
	       DrawString(50+200, 550, "Enter your name: ", colors[BLUE]);
	       DrawString(50+200, 450, "START", colors[BLUE]);
	       
	}	//if user presses 2, it will go inside Multiplayer and ask for 2 player names 
	if(menu == 2)
	{
	       DrawSquare(0, 0 ,1000,colors[SKY_BLUE]);
	       DrawString(50+200, 550, "Player 1 Name: ", colors[BLUE]);
	       DrawString(50+200, 500, "Player 2 Name: ", colors[BLUE]);
	       DrawString(50+200, 450, "START", colors[BLUE]);
	}
	//if user presses 3, it will go inside Settings and ask for vehicle type and controls.
	if(menu == 3)
	{
		//picking vehicle type
		DrawSquare(  0, 0 ,1000,colors[SKY_BLUE]);
		DrawString(450,800,"Choose Vehicle Type:",colors[BLACK]);
		DrawSquare(  250, 550 , 150,colors[RED]);
		DrawString(255, 590, "1. Helicopter", colors[BLACK]);
		DrawSquare(  400, 550 , 150,colors[RED]);
		DrawString(430, 590, "2. Firetruck", colors[BLACK]);
		DrawSquare(  550, 550 , 150,colors[RED]);
		DrawString(600, 590, "3. Car", colors[BLACK]);
		
		//choosing controls
		DrawString(450,500,"Controls: ", colors[BLACK]);
		DrawString(400,450,"UP ", colors[BLACK]);
		DrawString(400,400,"DOWN ", colors[BLACK]);
		DrawString(400,350,"LEFT ", colors[BLACK]);
		DrawString(400,300,"RIGHT ", colors[BLACK]);
	}
	//if user presses 4, it will display the highscores
	if(menu == 4) 
	{
		ifstream high;
		high.open("high_score.txt");
		high>>highscore;
		high.close();
		if(highscore<score)
		{
			highscore=score;
		}
		ofstream highk;
		highk.open("high_score.txt");
		highk<<highscore;
		highk.close();
	} 
	//if user presses 5, it will display the credits. 
	if(menu == 5)
	{
		DrawSquare(  0, 0 ,1000,colors[SKY_BLUE]);
	 	DrawString( 50+200, 550, "CREDITS:", colors[BLUE]);
		DrawString( 50+200, 450, "Created by Eman Furrukh", colors[BLUE]);
		DrawString( 50+200, 400, "Published on date 9th June 2022", colors[BLUE]);
		DrawString( 50+200, 350, "FAST UNIVERSITY, ISLAMABAD", colors[BLUE]);
		DrawString( 50+200, 250, "CopyRights (c)", colors[BLUE]);
		DrawString( 50+200, 200, "2022", colors[BLUE]);
	}
	if(counter == 1)
		DrawMap();

	
	//drawCar();
	//drawHelicopter();
	//drawFiretruck();
	glutSwapBuffers(); // do not modify this line..
}



/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */
 

void NonPrintableKeys(int key, int x, int y) {
if (key
			== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...
		xI -= 10;

	} else if (key
			== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
		xI += 10;
	} else if (key
			== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
		yI += 10;
	}

	else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
		yI -= 10;
	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	//Obstacles a1;
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}
	//displays solo mode
	if (key == '1') {
		menu = 1;
		/*cout<<"Enter your name in lowercase: ";
		cin>>name1;
		if(key == 'S')
			a1.DrawMap();*/
	}
	//to go back to menu
	if(key == 'P' || key == 'p')
		menu = 0;
	//displays multiplayer mode	
	if(key == '2') {
	        menu = 2;
	        if(key == 'S' || key == 's')
	        	counter = 2;
	}
	//displays settings 
	if(key == '3') {
		menu = 3;
		if(key == '1')
			drawHelicopter();
		if(key == '2')
			drawFiretruck();
		if(key == '3')
			drawCar();
	}
	//displays highscores
	if(key == '4') {
		menu = 4;
	}
	//displays credits
	if(key == '5') 
		menu = 5;
	if(key == 'S' || key == 's')
		counter = 1;
	//exiting the game
	if(key == '6') 
		exit(1); 
	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here
	moveCar();
	if(t<=0)
		menu = 0;
	t--;
       moveBots();
	if(t<=0)
		menu = 0;
	t--; 

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(100, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	cout << x << " " << y << endl;
	glutPostRedisplay();
}

void MouseMoved(int x, int y) {
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
	{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;
		cout<<"Left Button Pressed"<<endl;	
	}
 	else if (button == GLUT_RIGHT_BUTTON) {// dealing with right button
			cout<<"Right Button Pressed"<<endl;
			//if we are in SOLO window, if you click START, the game will start
			if( menu == 1) {
				if(x>250 && x<350 && y>350 && y<400) {
					DrawMap();
					t = 1800; 
				}
			}
			//if we are in MULTIPLAYER window, if you click START, the game will start
			else if(menu == 2) {
				if(x>250 && x<350 && y>350 && y<450)
					DrawMap();
					t = 1800;
			}
	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	int width = 1020, height = 840; // i have set yI window size to be 800 x 600
	
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Atari Game by Eman Furrukh"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* RushHour_CPP_ */
