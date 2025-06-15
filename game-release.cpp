//============================================================================
// Name        : Tetris.cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Tetris...
//============================================================================
#ifndef TETRIS_CPP_
#define TETRIS_CPP_
#include "util.h"
#include <iostream>
#include<vector>
#include<algorithm>
//#include<cstdlib>
#include<ctime>
#include<string>
//#include<sys/wait.h>
//#include<stdlib.h>
//#include<stdio.h>
#include<unistd.h>
#include<fstream>
#include<sstream>
#include<cmath>      // for basic math functions such as cos, sin, sqrt
using namespace std;

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();
}

void gameOverScreen(int width, int height, const float color[3]){
    glColor3fv(color);
    glBegin(GL_QUADS);
    glVertex2i(0,0);
    glVertex2i(width,0);
    glVertex2i(width,height);
    glVertex2i(0,height);
    glEnd();
}


/*
 * Main Canvas drawing function.
 * */
double startx=320,starty=400;
int dir;
int snakeSize=2;
int snakeHead[650][2];
int squares[5][2];
int hurdle[5][2];
int x=300;
int y=300;
int b=15;
int c=5;
int z=0;
int j=0;
int k=0;
int score=0;
int gameOver=0;
int m=650;
int n=650;
string scores;
int highest1=0;
string highest;


void Display(){
	if(gameOver==0){
		if(k==0){
			for(int a=0 ; a<1 ; a++){
				while(1){
					j=0;
					hurdle[a][0]=rand()%640;
					if(hurdle[a][0]>=550) {
						hurdle[a][0]=150;
					}
					if(hurdle[a][0]<=100) {
						hurdle[a][0]=500;
					}


					hurdle[a][1]= rand()%590;
					if(hurdle[a][1]>=550) {
						hurdle[a][1]=150;
					}
					if(hurdle[a][1]<=100) {
						hurdle[a][1]=500;
					}
					
					hurdle[a+1][0]=hurdle[a][0];
					hurdle[a+1][1]=hurdle[a][1]-100;
					hurdle[a+2][0]=hurdle[a+1][0];
					hurdle[a+2][1]=hurdle[a+1][1];
					hurdle[a+3][0]=hurdle[a+2][0]+100;
					hurdle[a+3][1]=hurdle[a+2][1];
					
					for(int i=0 ; i<snakeSize ; i++){
						if((snakeHead[i][0]/10>=hurdle[2][0]/10) && (snakeHead[i][0]/10<=hurdle[3][0]/10) && (snakeHead[i][1]/10==hurdle[2][1]/10)){
							j++;
						}
						if((snakeHead[i][1]/10>=hurdle[0][1]/10) && (snakeHead[i][1]/10<=hurdle[1][1]/10) && (snakeHead[i][0]/10==hurdle[0][0]/10)){
							j++;
						}
					}
					
					if(j==0){
						break;
					}
				}
			}
			k++;
		}	

		if(k==1){
			for(int a=0 ; a<5 ; a++){
				if(a==0){
					squares[a][0]= rand()%640;
					squares[a][1]= rand()%590;
				}
				else{
					while(1){
						j=0;
						squares[a][0]= rand()%640;
						for(int i=0 ; i<a ; i++) {
							if(squares[a][0]/10==squares[i][0]/10){
								j++;
							}
						}
						if(j==0){
							break;
						}
					}
					while(1){
						j=0;
						squares[a][1]= rand()%590;
						for(int i=0 ; i<a ; i++) {
							if(squares[a][1]/10==squares[i][1]/10){
								j++;
							}
							else if((squares[i][0]-squares[a][0])/10==((squares[i][1]-squares[a][1])/10)) {
								j++;
							}
							else if((squares[a][0]-squares[i][0])/10==((squares[a][1]-squares[i][1])/10)) {
								j++;
							}
							else if((squares[a][0]+squares[a][1])/10==((squares[i][0]+squares[i][1])/10)) {
								j++;
							}
						}
						if((squares[a][0]/10>=hurdle[2][0]/10) && (squares[a][0]/10<=hurdle[3][0]/10) && (squares[a][1]/10==hurdle[2][1]/10)){
							j++;
						}
						if((squares[a][1]/10>=hurdle[0][1]/10) && (squares[a][1]/10<=hurdle[1][1]/10) && (squares[a][0]/10==hurdle[0][0]/10)){
							j++;
						}
						if(j==0){
							break;
						}
					}
				}	
			}
			k++;
		}
		
	    // set the background color using function glClearColotgr.
	    // to change the background play with the red, green and blue values below.
	    // Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	    glClearColor(0/*Red Component*/, 0.0/*Green Component*/,
		    0.0/*Blue Component*/, 0 /*Alpha component*/);// Red==Green==Blue==1 --> White Colour
	    glClear(GL_COLOR_BUFFER_BIT);   //Update the colors
	    
	    for(int a=0 ; a<4 ; a+=2){
	    	 DrawLine( hurdle[a][0] , hurdle[a][1] , hurdle[a+1][0]  , hurdle[a+1][1] , 10 , colors[YELLOW_GREEN] );
	    }
	    
	    for(int a=0 ; a<5 ; a++){
	    	DrawSquare( squares[a][0] , squares[a][1] ,10,colors[CYAN]);
	    }
	    
	    for(int i=0 ; i<snakeSize ; i++){
	    	DrawSquare( snakeHead[i][0] , snakeHead[i][1] ,10,colors[CYAN]); 
	    }
	    
	    if((z%450>=0) && (z%450<=112)){
	    	DrawCircle( squares[6][0] , squares[6][1] ,10,colors[RED]); 
	    }
	    //DrawSquare( (((300+i)%645)+640)%645 , (((300+j)%595)+590)%595 ,10,colors[10]);  //This will draw a square shape of size 100x100  at x=300 and y=300
	    //DrawSquare( (((290+i)%645)+640)%645 , (((300+j)%595)+590)%595 ,10,colors[10]);  //This will draw a square shape of size 100x100  at x=300 and y=300
	    
	    
	    DrawString( 50, 620, "Snake", colors[MISTY_ROSE]); // this will print given string at x=50 , y=620
	    DrawString( 270, 620,"SCORE: ", colors[MISTY_ROSE]); // this will print given string at x=450 , y=620
	    scores = to_string(score) ;
	    DrawString( 310, 620, scores , colors[MISTY_ROSE]);
	    DrawCircle( snakeHead[0][0]+b , snakeHead[0][1]+c ,5,colors[RED]);
	    
	    ifstream in;
	    in.open("highestScore.txt");
	    in >> highest1;
	    in.close();
	    highest = to_string(highest1);

	    if (score > highest1) {
	   	ofstream out;
	    	out.open("highestScore.txt");
	    	out << score;
	    	out.close();
	    }
    	    
    	    DrawString( 450, 620,"Highest  SCORE: ", colors[MISTY_ROSE]); // this will print given string at x=450 , y=620
	    DrawString( 520, 620, highest , colors[MISTY_ROSE]);
    	    
    	    												
																			//                    v1( x,y )   v2( x,y )  , v3( x,y ) 
	    //DrawTriangle( 300, 50 , 500, 50 , 400 , 250, colors[MISTY_ROSE] );  // Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
	    
	    //DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	    DrawLine( 0 , 0 ,  650 , 0 , 50 , colors[MISTY_ROSE] );
	    DrawLine( 650 , 0 ,  650 , 600 , 50 , colors[MISTY_ROSE] );
	    DrawLine( 0 , 600 ,  650 , 600 , 50 , colors[MISTY_ROSE] );
	    DrawLine( 0 , 0 ,  0 , 600 , 50 , colors[MISTY_ROSE] );
	    
	    glutSwapBuffers(); // do not modify this line..
	}
	if(gameOver>=1){
		gameOverScreen(m , n , colors[BLACK]);
		DrawString(265 , 390 , "Game Over" , colors[MISTY_ROSE]);
		
		DrawString( 260, 340,"Your Score is ", colors[DARK_CYAN]); // this will print given string at x=450 , y=620
	    	scores = to_string(score) ;
	   	DrawString( 310, 340, scores , colors[DARK_CYAN]);
	   	DrawString(250 , 290 , "(Press ESC key to exit)" , colors[MISTY_ROSE]);
		
		glutSwapBuffers();
	}
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
    if (key == GLUT_KEY_LEFT   /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
											// what to do when left key is pressed...
		if(dir!=1){
			dir=3;
		}
		
    } else if (key == GLUT_KEY_RIGHT  /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
    		
		if(dir!=3){
			dir=1;
		}
		
    } else if (key == GLUT_KEY_UP) /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/ {
    		
        	if(dir!=2){	
        		dir=4;
        	}
        	
    }
    else if (key == GLUT_KEY_DOWN)   /*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/ {
    		if(dir!=4){
			dir=2;
		}
		
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
    if (key == KEY_ESC/* Escape key ASCII*/) {
        exit(1); // exit the program when escape key is pressed.
    }
    if (key == 'R' || key=='r'/* Escape key ASCII*/) {
        //exit(1); // exit the program when escape key is pressed.
    	//aswangle+=90;
    }
    
    else if (int(key) == 13)
    {  
	}
    
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
	if(dir==1){
		x+=10;
		b=15;
		c=5;
	}
	else if(dir==2){
		y-=10;
		b=5;
		c=-5;
	}
	else if(dir==3){
		x-=10;
		b=-5;
		c=5;
	}
	else if(dir==4){
		y+=10;
		b=5;
		c=15;
	}
	z++;
	
	if(z%225==0){
		for(int a=0 ; a<1 ; a++){
			while(1){
				j=0;
				hurdle[a][0]=rand()%640;
				if(hurdle[a][0]>=550) {
					hurdle[a][0]=150;
				}
				if(hurdle[a][0]<=100) {
					hurdle[a][0]=500;
				}


				hurdle[a][1]= rand()%590;
				if(hurdle[a][1]>=550) {
					hurdle[a][1]=150;
				}
				if(hurdle[a][1]<=100) {
					hurdle[a][1]=500;
				}
				
				hurdle[a+1][0]=hurdle[a][0];
				hurdle[a+1][1]=hurdle[a][1]-100;
				hurdle[a+2][0]=hurdle[a+1][0];
				hurdle[a+2][1]=hurdle[a+1][1];
				hurdle[a+3][0]=hurdle[a+2][0]+100;
				hurdle[a+3][1]=hurdle[a+2][1];
				
				for(int i=0 ; i<snakeSize ; i++){
					if((snakeHead[i][0]/10>=hurdle[2][0]/10) && (snakeHead[i][0]/10<=hurdle[3][0]/10) && (snakeHead[i][1]/10==hurdle[2][1]/10)){
						j++;
					}
					if((snakeHead[i][1]/10>=hurdle[0][1]/10) && (snakeHead[i][1]/10<=hurdle[1][1]/10) && (snakeHead[i][0]/10==hurdle[0][0]/10)){
						j++;
					}
				}
				
				if(j==0){
					break;
				}
			}
		}	
	}
	
	if(z%112==0){
		for(int a=0 ; a<5 ; a++){
			if(a==0){
				squares[a][0]= rand()%640;
				squares[a][1]= rand()%590;
			}
			else{
				while(1){
					j=0;
					squares[a][0]= rand()%640;
					for(int i=0 ; i<a ; i++) {
						if(squares[a][0]/10==squares[i][0]/10){
							j++;
						}
					}
					if(j==0){
						break;
					}
				}
				while(1){
					j=0;
					squares[a][1]= rand()%590;
					for(int i=0 ; i<a ; i++) {
						if(squares[a][1]/10==squares[i][1]/10){
							j++;
						}
						else if((squares[i][0]-squares[a][0])/10==((squares[i][1]-squares[a][1])/10)) {
							j++;
						}
						else if((squares[a][0]-squares[i][0])/10==((squares[a][1]-squares[i][1])/10)) {
							j++;
						}
						else if((squares[a][0]+squares[a][1])/10==((squares[i][0]+squares[i][1])/10)) {
							j++;
						}
					}
					if((squares[a][0]/10>=hurdle[2][0]/10) && (squares[a][0]/10<=hurdle[3][0]/10) && (squares[a][1]/10==hurdle[2][1]/10)){
						j++;
					}
					if((squares[a][1]/10>=hurdle[0][1]/10) && (squares[a][1]/10<=hurdle[1][1]/10) && (squares[a][0]/10==hurdle[0][0]/10)){
						j++;
					}
					if(j==0){
						break;
					}
				}
			}	
		}
	}
	
	if(z%450==0){
		for(int a=6 ; a<7 ; a++){
			if(a==0){
				squares[a][0]= rand()%640;
				squares[a][1]= rand()%590;
			}
			else{
				while(1){
					j=0;
					squares[a][0]= rand()%640;
					for(int i=0 ; i<a ; i++) {
						if(squares[a][0]/10==squares[i][0]/10){
							j++;
						}
					}
					if(j==0){
						break;
					}
				}
				while(1){
					j=0;
					squares[a][1]= rand()%590;
					for(int i=0 ; i<a ; i++) {
						if(squares[a][1]/10==squares[i][1]/10){
							j++;
						}
						else if((squares[i][0]-squares[a][0])/10==((squares[i][1]-squares[a][1])/10)) {
							j++;
						}
						else if((squares[a][0]-squares[i][0])/10==((squares[a][1]-squares[i][1])/10)) {
							j++;
						}
						else if((squares[a][0]+squares[a][1])/10==((squares[i][0]+squares[i][1])/10)) {
							j++;
						}
					}
					if((squares[a][0]/10>=hurdle[2][0]/10) && (squares[a][0]/10<=hurdle[3][0]/10) && (squares[a][1]/10==hurdle[2][1]/10)){
						j++;
					}
					if((squares[a][1]/10>=hurdle[0][1]/10) && (squares[a][1]/10<=hurdle[1][1]/10) && (squares[a][0]/10==hurdle[0][0]/10)){
						j++;
					}
					if(j==0){
						break;
					}
				}
			}	
		}
	}
	
	if(dir!=1 && dir!=2 && dir!=3 && dir!=4 ){
		snakeHead[1][0]=snakeHead[0][0]-10;
		snakeHead[1][1]=snakeHead[0][1];
		snakeHead[2][0]=snakeHead[0][0]-20;
		snakeHead[2][1]=snakeHead[0][1];
	}
	else{
		for(int i=snakeSize-1 ; i>0 ; i--){
			snakeHead[i][0]=snakeHead[i-1][0];
			snakeHead[i][1]=snakeHead[i-1][1];
		}
	}
	snakeHead[0][0]=((x%645)+640)%645;
	snakeHead[0][1]=((y%595)+590)%595;
	
	if(((snakeHead[0][0]/10>=hurdle[2][0]/10) || (snakeHead[0][0]/10>=(hurdle[2][0]/10-1)) || (snakeHead[0][0]/10>=(hurdle[2][0]/10+1))) && ((snakeHead[0][0]/10<=hurdle[3][0]/10) || (snakeHead[0][0]/10<=(hurdle[3][0]/10-1)) || (snakeHead[0][0]/10<=(hurdle[3][0]/10+1))) && ((snakeHead[0][1]/10==hurdle[2][1]/10) || (snakeHead[0][1]/10==(hurdle[2][1]/10-1)) || (snakeHead[0][1]/10==(hurdle[2][1]/10+1)))){
		gameOver=1;
	}
	if(((snakeHead[0][1]/10<=hurdle[0][1]/10) || (snakeHead[0][1]/10<=(hurdle[0][1]/10-1)) || (snakeHead[0][1]/10<=(hurdle[0][1]/10+1)))  && ((snakeHead[0][1]/10>=hurdle[1][1]/10) || (snakeHead[0][1]/10>=(hurdle[1][1]/10-1)) || (snakeHead[0][1]/10>=(hurdle[1][1]/10+1))) && ((snakeHead[0][0]/10==hurdle[0][0]/10) || (snakeHead[0][0]/10==(hurdle[0][0]/10-1)) || (snakeHead[0][0]/10==(hurdle[0][0]/10+1)))){
		gameOver=1;
	}
	
	for(int i=1 ; i<snakeSize ; i++){
		if((snakeHead[0][0]==snakeHead[i][0]) && (snakeHead[0][1]==snakeHead[i][1])){
			gameOver=1;
		}
	}
		
	for(int i=0 ; i<5 ; i++) {
		if((snakeHead[0][0]/10==squares[i][0]/10) && (snakeHead[0][1]/10==squares[i][1]/10)){
			snakeSize++;
			score+=5;		
			while(1){
				j=0;
				squares[i][0]= rand()%640;
				for(int a=0 ; a<5 ; a++) {
					if(a==i){
						continue;
					}
					if(squares[i][0]/10==squares[a][0]/10){
						j++;
					}
				}
				if(j==0){
					break;
				}
			}
			while(1){
				j=0;
				squares[i][1]= rand()%590;
				for(int a=0 ; a<5 ; a++) {
					if(a==i){
						continue;
					}
					if(squares[i][1]/10==squares[a][1]/10){
						j++;
					}
					else if((squares[i][0]-squares[a][0])/10==((squares[i][1]-squares[a][1])/10)) {
						j++;
					}
					else if((squares[a][0]-squares[i][0])/10==((squares[a][1]-squares[i][1])/10)) {
						j++;
					}
					else if((squares[i][0]+squares[i][1])/10==((squares[a][0]+squares[a][1])/10)) {
						j++;
					}
				}
				if((squares[i][0]/10>=hurdle[2][0]/10) && (squares[i][0]/10<=hurdle[3][0]/10) && (squares[i][1]/10==hurdle[2][1]/10)){
					j++;
				}
				if((squares[i][1]/10>=hurdle[0][1]/10) && (squares[i][1]/10<=hurdle[1][1]/10) && (squares[i][0]/10==hurdle[0][0]/10)){
					j++;
				}
				
				if(j==0){
					break;
				}
			}
		}
	}
	
	for(int i=6 ; i<7 ; i++) {
		if(((snakeHead[0][0]/10==squares[i][0]/10) || (snakeHead[0][0]/10==squares[i][0]/10-1) || (snakeHead[0][0]/10==squares[i][0]/10+1)) && ((snakeHead[0][1]/10==squares[i][1]/10) || (snakeHead[0][1]/10==squares[i][1]/10-1) || (snakeHead[0][1]/10==squares[i][1]/10+1))){
			snakeSize+=2;
			score+=10;		
			while(1){
				j=0;
				squares[i][0]= rand()+740;
				for(int a=0 ; a<5 ; a++) {
					if(a==i){
						continue;
					}
					if(squares[i][0]/10==squares[a][0]/10){
						j++;
					}
				}
				if(j==0){
					break;
				}
			}
			while(1){
				j=0;
				squares[i][1]= rand()%590;
				for(int a=0 ; a<5 ; a++) {
					if(a==i){
						continue;
					}
					if(squares[i][1]/10==squares[a][1]/10){
						j++;
					}
					else if((squares[i][0]-squares[a][0])/10==((squares[i][1]-squares[a][1])/10)) {
						j++;
					}
					else if((squares[a][0]-squares[i][0])/10==((squares[a][1]-squares[i][1])/10)) {
						j++;
					}
					else if((squares[i][0]+squares[i][1])/10==((squares[a][0]+squares[a][1])/10)) {
						j++;
					}
				}
				if((squares[i][0]/10>=hurdle[2][0]/10) && (squares[i][0]/10<=hurdle[3][0]/10) && (squares[i][1]/10==hurdle[2][1]/10)){
					j++;
				}
				if((squares[i][1]/10>=hurdle[0][1]/10) && (squares[i][1]/10<=hurdle[1][1]/10) && (squares[i][0]/10==hurdle[0][0]/10)){
					j++;
				}
				
				if(j==0){
					break;
				}
			}
		}
	}
	
// implement your functionality here
	glutPostRedisplay();
// once again we tell the library to call our Timer function after next 1000/FPS
    glutTimerFunc(750.0 / FPS, Timer, 0);
}

/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {
    int width = 650, height = 650; // i have set my window size to be 800 x 600
    InitRandomizer(); // seed the random number generator...
    glutInit(&argc, argv); // initialize the graphics library...

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
    glutInitWindowPosition(50, 50); // set the initial position of our window
    glutInitWindowSize(width, height); // set the size of our window
    glutCreateWindow("PF's Snake Game"); // set the title of our game window
    SetCanvasSize(width, height); // set the number of pixels...

// Register your functions to the library,
// you are telling the library names of function to call for different tasks.
//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
    glutDisplayFunc(Display); // tell library which function to call for drawing Canvas.
    glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
    glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
    glutTimerFunc(5.0 / FPS, Timer, 0);

// now handle the control to library and it will call our registered functions when
// it deems necessary...
    glutMainLoop();
    return 1;
}
#endif /* Snake Game */

