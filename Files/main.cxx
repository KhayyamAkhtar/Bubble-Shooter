#include "graphics.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>                     // Provides exit
#include <ctype.h>                      // Provides toupper
#include<time.h>
#include <math.h>
using namespace std;

//REAL GAMING FILE

#define PI 3.14159235


int xLimit = 800;		//X-axis Boundary limit for game display
int yLimit = 600;		//Y-axis Boundary limit for game display
int lineXend = 386;		//X co-ordinate for aiming line ending
int lineYend = 386;		//Y co-ordinate for aiming line ending
int xOrigin = 386, yOrigin = 540; //Starting points for the line
void *blueBall;		//Pointer for blue ball
void *redBall;		//Pointer for red ball
void *yellowBall;		//Pointer for yellow ball
void *fireWork;		//Pointer for firework
int RSEED;		//Used as seed for srand mainly for starting grid
int thrownBallCopy; //remembers the ball color that will be thrown
int rightBoundTouched , leftBoundTouched , upBoundTouched;	//manages whether the ball has been touched at the boundaries
int *bubbleGrid;	//Balls on screen
int gridCounter;
int endLine = 0;
int score;

int *bubbleBurst;	//Balls to remove
int burstCounter;
int noOfBurstBalls;
int burstIndex;
int ballColorThrown;


float xCO = 360 , yCO = 540; //Manages motion of the ball
int ballStop = 0; //Manages whether or not the ball has stopped

//The GAME!!!
float theta = PI/2;
float x_shooter = cos(theta);
float y_shooter = -sin(theta);
//The GAME!!!





char Main_Menu(void);
void Developers(void);
void AimLine(char);
int RandomThrowBall(void);
void BubbleThrow(void);
void BubbleBoundaryCheck(void);
void StartingGrid(void);
int NewBallCheck(int , int , int , int);
int BallTouchedGrid(void);
void BubbleBursting(void);
void EndLineMovement(void);
int BubbleBurstCheck(void);
int EditedThrowBall(void);
int FallenGrid(void);
int FreeBubbleBurstCheck(void);




int FreeBubbleBurstCheck(void) {		//Checks hanging bubbles START
	int highY = 0;
	int preHighY = 0;
	int preY;
	int preX;
	int preColor;
	int toBurst = 0;
	bubbleBurst = (int *)malloc(3 * sizeof(int));

	for (int arrayIndex = 0 ; arrayIndex <= gridCounter ; arrayIndex = arrayIndex + 3) {
		preY = bubbleGrid[arrayIndex + 1];
		if (preY > highY) {
			highY = preY;
			preX = bubbleGrid[arrayIndex];
			preColor = bubbleGrid[arrayIndex + 2];
		}
	}
	for (int arrayIndex = 0 ; arrayIndex <= gridCounter ; arrayIndex = arrayIndex + 3) {
		preY = bubbleGrid[arrayIndex + 1];
		if (preY < highY) {
			if (preY > preHighY) {
				preHighY = preY;
			}
		}
	}
	if (highY - preHighY > 50) {
		bubbleBurst[0] = preX;
		bubbleBurst[1] = highY;
		bubbleBurst[2] = preColor;
		burstCounter = 3;
		toBurst = 1;
	} else {
		free(bubbleBurst);
	}

	return toBurst;
}		//Checks hanging bubbles END





int FallenGrid(void) {		//Checks if the user game has lost START
	int highY = 0;
	for (int arrayIndex = 1 ; arrayIndex <= gridCounter ; arrayIndex = arrayIndex + 3) {
		if (bubbleGrid[arrayIndex] > highY) {
			highY = bubbleGrid[arrayIndex];
		}
	}
	if (highY >= 480) {
		return 1;
	} else {
		return 0;
	}
}	//Checks if the user game has lost END





int EditedThrowBall(void) {		//generates colors for balls that makes the game easier START
	int ballColors[3] = {10 , 10 , 10};
	int num = 10;
	int color;
	int counter = 1;
	ballColors[0] = bubbleGrid[2];
	for (int arrayIndex = 5 ; arrayIndex <= gridCounter ; arrayIndex = arrayIndex + 3) {
		color = bubbleGrid[arrayIndex];
		if (color == ballColors[0]) {
			break;
		} else {
			if (color == ballColors[1]) {
				break;
			} else {
				if (color == ballColors[2]) {
					break;
				} else {
					if (counter < 3) {
						ballColors[counter] = color;
						counter = counter + 1;
					}
				}
			}
		}
	}
	//color = 10;
	num = 10;
	while (num == 10) {
		srand(time(NULL));
		num = rand() % 3;
		color = ballColors[num];
		if (color == 10) {
			num = 10;
		}
	}
	if (color == 0) {
		putimage(360 , 540 , blueBall , XOR_PUT);
	}
	if (color == 1) {
		putimage(360 , 540 , yellowBall , XOR_PUT);
	}
	if (color == 2) {
		putimage(360 , 540 , redBall , XOR_PUT);
	}
	thrownBallCopy = color;
	return color;
}	//generates colors for balls that makes the game easier END




void EndLineMovement(void) {		//Moves the bubble grid START
	int preX;
	int preY;
	int preColor;
	setcolor(BLACK);
	line(0, endLine, xLimit , endLine);
	for (int arrayIndex = 0 ; arrayIndex <= gridCounter ; arrayIndex = arrayIndex + 3) {
		preX = bubbleGrid[arrayIndex];
		preY = bubbleGrid[arrayIndex + 1];
		preColor = bubbleGrid[arrayIndex + 2];
		if (preColor == 0) {
			putimage(preX , preY , blueBall , XOR_PUT);
		}
		if (preColor == 1) {
			putimage(preX , preY , yellowBall , XOR_PUT);
		}
		if (preColor == 2) {
			putimage(preX , preY , redBall , XOR_PUT);
		}
		bubbleGrid[arrayIndex + 1] = bubbleGrid[arrayIndex + 1] + 41;
	}
	for (int arrayIndex = 0 ; arrayIndex <= gridCounter ; arrayIndex = arrayIndex + 3) {
		preX = bubbleGrid[arrayIndex];
		preY = bubbleGrid[arrayIndex + 1];
		preColor = bubbleGrid[arrayIndex + 2];
		if (preColor == 0) {
			putimage(preX , preY , blueBall , XOR_PUT);
		}
		if (preColor == 1) {
			putimage(preX , preY , yellowBall , XOR_PUT);
		}
		if (preColor == 2) {
			putimage(preX , preY , redBall , XOR_PUT);
		}
	}
	setcolor(YELLOW);
	endLine = endLine + 40;
	line(0, endLine, xLimit , endLine);
	setcolor(WHITE);
}		//Moves the bubble grid END





int BubbleBurstCheck(void) {	//Checks Balls to burst START
	int preX;
	int preY;
	int preColor;
	noOfBurstBalls = 1;
	burstCounter = 3;
	bubbleBurst = (int *)malloc(6 * sizeof(int));
	bubbleBurst[0] = xCO;
	bubbleBurst[1] = yCO;
	bubbleBurst[2] = ballColorThrown;
	int toBurst = 0;
	int midX , midY;
	for (int arrayIndex = 0 ; arrayIndex <= gridCounter ; arrayIndex = arrayIndex + 3) {
		preX = bubbleGrid[arrayIndex];
		preY = bubbleGrid[arrayIndex + 1];
		midX = ((2 * preX) + 50) / 2;//***
		midY = ((2 * preY) + 50) / 2;//***
		preColor = bubbleGrid[arrayIndex + 2];
		if ((midX >= xCO -58)&&(midX <= xCO + 116)) {	//Values determines area -60 and + 120
			if ((midY >= yCO - 58)&&(midY <= yCO + 116)) {	//Values determines area
				if (preColor == ballColorThrown) {
					bubbleBurst[burstCounter] = preX;
					bubbleBurst[burstCounter + 1] = preY;
					bubbleBurst[burstCounter + 2] = preColor;
					burstCounter = burstCounter + 3;
					noOfBurstBalls = noOfBurstBalls + 1;
					bubbleBurst = (int *)realloc(bubbleBurst , (burstCounter + 3) * sizeof(int));
				}
			}
		}
	}
	/*
	for (int arrayIndex = 0 ; arrayIndex <= gridCounter ; arrayIndex = arrayIndex + 3) {
		preX = bubbleGrid[arrayIndex];
		preY = bubbleGrid[arrayIndex + 1];
		midX = ((2 * preX) + 50) / 2;//
		midY = ((2 * preY) + 50) / 2;//
		preColor = bubbleGrid[arrayIndex + 2];
		if ((midX >= xCO -20)&&(midX <= xCO + 40)) {	//Values determines area -60 and + 120
			if ((midY >= yCO - 50)&&(midY <= yCO + 100)) {	//Values determines area
				if (preColor == ballColorThrown) {
					bubbleBurst[burstCounter] = preX;
					bubbleBurst[burstCounter + 1] = preY;
					bubbleBurst[burstCounter + 2] = preColor;
					burstCounter = burstCounter + 3;
					noOfBurstBalls = noOfBurstBalls + 1;
					bubbleBurst = (int *)realloc(bubbleBurst , (burstCounter + 3) * sizeof(int));
				}
			}
		}
	}
	*/

	if (noOfBurstBalls >= 3) {
		toBurst = 1;
		score = score + (noOfBurstBalls * 15);
	} else {
		free(bubbleBurst);
	}

	return toBurst;
}	//Checks Balls to burst END





void BubbleBursting(void) {		//Bursts balls from grid START
	int burstX;
	int burstY;
	int burstColor;
	int gridX;
	int gridY;
	int gridColor;
	int arrayIndex2;
	int *tempBubbleGrid;
	int tempCounter = 0;
	for (int arrayIndex = 0 ; arrayIndex < burstCounter ; arrayIndex = arrayIndex + 3) {
		burstX = bubbleBurst[arrayIndex];
		burstY = bubbleBurst[arrayIndex + 1];
		burstColor = bubbleBurst[arrayIndex + 2];
		if (burstColor == 0) {
			putimage(burstX , burstY , blueBall , XOR_PUT);
		}
		if (burstColor == 1) {
			putimage(burstX , burstY , yellowBall , XOR_PUT);
		}
		if (burstColor == 2) {
			putimage(burstX , burstY , redBall , XOR_PUT);
		}
		putimage(burstX , burstY , fireWork , XOR_PUT);
		delay(50);
		putimage(burstX , burstY , fireWork , XOR_PUT);
		arrayIndex2 = 0;
		while (arrayIndex2 <= gridCounter) {
			gridX = bubbleGrid[arrayIndex2];
			gridY = bubbleGrid[arrayIndex2 + 1];
			gridColor = bubbleGrid[arrayIndex2 + 2];
			if (gridX == burstX) {
				if (gridY == burstY) {
					if (gridColor == burstColor) {
						for (int arrayIndex3 = arrayIndex2 ; arrayIndex3 < gridCounter ; arrayIndex3 = arrayIndex3 + 3) {
							bubbleGrid[arrayIndex3] = bubbleGrid[arrayIndex3 + 3];
							bubbleGrid[arrayIndex3 + 1] = bubbleGrid[arrayIndex3 + 4];
							bubbleGrid[arrayIndex3 + 2] = bubbleGrid[arrayIndex3 + 5];
						}
						gridCounter = gridCounter - 3;
						//bubbleGrid = (int *)realloc(bubbleGrid , gridCounter * sizeof(int)); Method 1
						arrayIndex2 = arrayIndex2 - 3;

						/*
						bubbleGrid[arrayIndex2] = 1000;
						bubbleGrid[arrayIndex2 + 1] = 1000;	//if using two arrays
						bubbleGrid[arrayIndex2 + 2] = 1000;
						*/
					}
				}
			}
			arrayIndex2 = arrayIndex2 + 3;
		}
	}
	/* Method 2
	tempBubbleGrid = (int *)malloc((gridCounter - 3)*sizeof(int));
	for (int arrayIndex = 0 ; arrayIndex < gridCounter ; arrayIndex = arrayIndex + 3) {
		gridX = bubbleGrid[arrayIndex];
		gridY = bubbleGrid[arrayIndex + 1];
		gridColor = bubbleGrid[arrayIndex + 2];
		if ((gridX == 1000)&&(gridY == 1000)&&(gridColor == 1000)) {
			//Do nothing
		} else {
			tempBubbleGrid[tempCounter] = gridX;
			tempBubbleGrid[tempCounter + 1] = gridY;
			tempBubbleGrid[tempCounter + 2] = gridColor;
			tempCounter = tempCounter + 3;
		}
	}
	gridCounter = gridCounter - 3;
	free(bubbleGrid);
	bubbleGrid = (int *)malloc(gridCounter * sizeof(int));
	for (int arrayIndex = 0 ; arrayIndex < gridCounter ; arrayIndex = arrayIndex + 1) {
		bubbleGrid[arrayIndex] = tempBubbleGrid[arrayIndex];
	}
	free(tempBubbleGrid);
	*/

}		//Bursts balls from grid END





int BallTouchedGrid(void) {		//Checks whether the ball has touched any other ball in Grid START
	int xOrdinate = xCO;
	int yOrdinate = yCO;
	int takenY;
	int takenX;
	int value = 0;
	double btwLength;
	int length;
	int midX1 = (xCO + (xCO + 50)) / 2;
	int midY1 = (yCO + (yCO + 50)) / 2;
	int midX2 , midY2;
	for (int arrayIndex = 0 ; arrayIndex < gridCounter ; arrayIndex = arrayIndex + 3) {
		takenX = bubbleGrid[arrayIndex];
		takenY = bubbleGrid[arrayIndex + 1];
		midX2 = (takenX + (takenX + 50)) / 2;
		midY2 = (takenY + (takenY + 50)) / 2;
		btwLength = ((midX2 - midX1)*(midX2 - midX1)) + ((midY2 - midY1)*(midY2 - midY1));
		btwLength = sqrt(btwLength);
		length = btwLength;
		if (value == 1) {
			break;
		}
		if (btwLength <= 51) {
			value = 1;
		}
	}
	return value;
}	//Checks whether the ball has touched any other ball in Grid END





void BubbleThrow(void) {		//Throws the bubble START
	float velocityX = 10*cos(theta); 
	float velocityY = -10*sin(theta);
	
	if (thrownBallCopy == 0) {
		putimage(xCO , yCO , blueBall , XOR_PUT);
		xCO = xCO + velocityX;
		yCO = yCO + velocityY;
		if ((rightBoundTouched == 1)||(leftBoundTouched)) {
			xCO = xCO - (2 * velocityX);
		}
		putimage(xCO , yCO , blueBall , XOR_PUT);
	}
	if (thrownBallCopy == 1) {
		putimage(xCO , yCO , yellowBall , XOR_PUT);
		xCO = xCO + velocityX;
		yCO = yCO + velocityY;
		if ((rightBoundTouched == 1)||(leftBoundTouched)) {
			xCO = xCO - (2 * velocityX);
		}
		putimage(xCO , yCO , yellowBall , XOR_PUT);
	}
	if (thrownBallCopy == 2) {
		putimage(xCO , yCO , redBall , XOR_PUT);
		xCO = xCO + velocityX;
		yCO = yCO + velocityY;
		if ((rightBoundTouched == 1)||(leftBoundTouched)) {
			xCO = xCO - (2 * velocityX);
		}
		putimage(xCO , yCO , redBall , XOR_PUT);
	}
	delay(15);
}		//Throws the bubble END





void StartingGrid(void) {	//Creates the starting bubble grid START
	//NOTES TO REMEMBER!
	//GRID ARRAY WORKS ON MULTIPLES OF THREE SYSTEM!
	//FIRST INDEX IS X COORDINATE OF BUBBLE
	//SECOND INDEX IS Y COORDINATE OF BUBBLE
	//THIRD INDEX IS INTEGER VALUE FOR ITS COLOR
	//AND IT REPEATS
	int strtPointX = 0;
	int strtPointY = 0;
	int ballColor;
	int ballCount = 0;
	int arrayIndex = 0;
	int lastBallLimit = xLimit;
	int proceedBall;
	delay(8);
	while (ballCount <= 42) {
		RSEED = RSEED + 3;
		srand(RSEED);
		//srand(time(NULL));
		ballColor = rand() % 3;
		proceedBall = 1;
		if (ballCount >= 2) {
			//Horizontal Ball CHECK START
			if (ballColor == bubbleGrid[arrayIndex - 1]) {	//Matches with one previous ball
				if (ballColor == bubbleGrid[arrayIndex - 4]) {	//Matches with two previous balls
					proceedBall = 0;
				}
			}
		}
		//Horizontal Ball CHECK END
		if (ballCount >= 30) {	//If TRUE then valid for vertical check
			//ADD A FULL CHECK FUNCTION
			proceedBall = NewBallCheck(strtPointX , strtPointY , ballColor , arrayIndex);
		}
		if (proceedBall == 1) {
			bubbleGrid[arrayIndex] = strtPointX;
			bubbleGrid[arrayIndex + 1] = strtPointY;
			bubbleGrid[arrayIndex + 2] = ballColor;
			gridCounter = gridCounter + 3;
			ballCount = ballCount + 1;
			arrayIndex = arrayIndex + 3;
			if (ballColor == 0) {
				putimage(strtPointX , strtPointY , blueBall , XOR_PUT);
			}
			if (ballColor == 1) {
				putimage(strtPointX , strtPointY , yellowBall , XOR_PUT);
			}
			if (ballColor == 2) {
				putimage(strtPointX , strtPointY , redBall , XOR_PUT);
			}
			strtPointX = strtPointX + 50;
			if (strtPointX > lastBallLimit) {
				lastBallLimit = lastBallLimit - 60;
				if (ballCount <= 29) {
					strtPointX = 50;
				} else {
					strtPointX = 100;
				}
				strtPointY = strtPointY + 50;
			}
		}
		delay(7);
	}
}		//Creates the starting bubble grid END





int NewBallCheck(int newBallX , int newBallY , int newBallColor , int newBallArrayIndex) {	//Checks to stop three times repeatition START
	int check = 1;
	int loopCont = 1;
	int arrayIndex = 0;
	int loopArrayIndex = 0;
	int ballColor_1 = -1;
	int ballColor_2 = -1;
	//X coordinates for balls above the new ball placement
	int midLeftX = newBallX - 50;
	int midX = newBallX;
	int midRightX = newBallX + 50;
	//Y coordinates for balls above the new ball placement
	int midY = newBallY - 50;
	//X coordinates for balls at the third level
	int topLeftX = newBallX - 100;
	int topX = newBallX;
	int topRightX = newBallX + 100;
	//Y coordinates for balls at the third level
	int topY = newBallY - 100;
	int preX , preY;	//Coordinates from bubbleGrid

	while ((loopArrayIndex < newBallArrayIndex)&&(check != 0)) {
		preX = bubbleGrid[loopArrayIndex];
		preY = bubbleGrid[loopArrayIndex + 1];
		loopCont = 1;
		if ((topLeftX == preX)&&(topY == preY)) {
			ballColor_1 = bubbleGrid[loopArrayIndex + 2];
			arrayIndex = 0;
			while ((arrayIndex < newBallArrayIndex)&&(loopCont)) {
				preX = bubbleGrid[arrayIndex];
				preY = bubbleGrid[arrayIndex + 1];
				if ((midLeftX == preX)&&(midY == preY)) {
					ballColor_2 = bubbleGrid[arrayIndex + 2];
					loopCont = 0;
				}
				arrayIndex = arrayIndex + 1;
			}
			if (newBallColor == ballColor_1) {
				if (newBallColor == ballColor_2) {
					check = 0;
				}
			}
		}

		if ((topX == preX)&&(topY == preY)) {
			ballColor_1 = bubbleGrid[loopArrayIndex + 2];
			arrayIndex = 0;
			while ((arrayIndex < newBallArrayIndex)&&(loopCont)) {
				preX = bubbleGrid[arrayIndex];
				preY = bubbleGrid[arrayIndex + 1];
				if ((midX == preX)&&(midY == preY)) {
					ballColor_2 = bubbleGrid[arrayIndex + 2];
					loopCont = 0;
				}
				arrayIndex = arrayIndex + 1;
			}
			if (newBallColor == ballColor_1) {
				if (newBallColor == ballColor_2) {
					check = 0;
				}
			}
		}

		if ((topRightX == preX)&&(topY == preY)) {
			ballColor_1 = bubbleGrid[loopArrayIndex + 2];
			arrayIndex = 0;
			while ((arrayIndex < newBallArrayIndex)&&(loopCont)) {
				preX = bubbleGrid[arrayIndex];
				preY = bubbleGrid[arrayIndex + 1];
				if ((midRightX == preX)&&(midY == preY)) {
					ballColor_2 = bubbleGrid[arrayIndex + 2];
					loopCont = 0;
				}
				arrayIndex = arrayIndex + 1;
			}
			if (newBallColor == ballColor_1) {
				if (newBallColor == ballColor_2) {
					check = 0;
				}
			}
		}
	
		loopArrayIndex = loopArrayIndex + 1;
	}

	return check;
}		//Checks to stop three times repeatition END





void BubbleBoundaryCheck(void) {	//shows whether the ball has touched the boundaries START
	if (xCO >= xLimit - 60) {
		rightBoundTouched = 1;
	}

	if (xCO <= 0) {
		leftBoundTouched = 1;
	}
	if (yCO <= endLine + 18) {
		upBoundTouched = 1;
	}
}	//shows whether the ball has touched the boundaries END





int RandomThrowBall(void) {		//Creates a random ball for throwing START
	int Num;
	//srand(RSEED);
	srand(time(NULL));
	Num = rand() % 3;
	if (Num == 0) {
		putimage(360 , 540 , blueBall , XOR_PUT);
		thrownBallCopy = 0;
	}
	if (Num == 1) {
		putimage(360 , 540 , yellowBall , XOR_PUT);
		thrownBallCopy = 1;
	}
	if (Num == 2) {
		putimage(360 , 540 , redBall , XOR_PUT);
		thrownBallCopy = 2;
	}
	return Num;
}		//Creates a random ball for throwing END





void AimLine(char btnPress) {		//Displays aiming line START
	setcolor(BLACK);
	line(xOrigin, yOrigin - 5, 100*x_shooter+xOrigin, 100*y_shooter+yOrigin);
	if((btnPress == 'a') && (theta < PI-PI/6)) {
		theta += PI/100;
	}
	if((btnPress == 'd') && (theta > PI/6)) {
		theta -= PI/100;
	}
	x_shooter = cos(theta);
	y_shooter = -sin(theta);
	setcolor(YELLOW);
	line(xOrigin, yOrigin - 5, 100*x_shooter+xOrigin, 100*y_shooter+yOrigin);
}		//Displays aiming line END





char Main_Menu(void){		//Displays Game starting menu START
	char choice;
	cleardevice();
	setcolor(YELLOW);
	outtextxy(10 , 10 , "Bubble Shooter");
	setcolor(WHITE);
	outtextxy(20 , 40 , "1. Proceed to game.");
	outtextxy(20 , 70 , "2. Learn about game and developers.");
	outtextxy(20 , 100 , "3. Exit Game.");
	choice = getch();
	return choice;
}		//Displays Game starting menu END





void Developers(void) {		//Displays Developers and Game Introduction START
	cleardevice();
	setcolor(WHITE);
	outtextxy(10 , 10 , "Made by Khayyam Akhtar and Aamir Abbas!");
	getch();
}		//Displays Developers and Game Introduction END





void main(void) {
	char userChoice;
	char aimMove;
	int gridMoveCounter = 0;
	int burstBall;
	char keyPress = 'l';
	int imgSize;
	int roundNo;
	int gameStop = 0;
	int restrictBalls = 0;
	int revertBalls = 0;
	int hangingBalls = 1;
	//RSEED = 23;
	initwindow(xLimit, yLimit, "Bubble Shooter", 10, 10, false, true);		//Displays windows
	//Adding balls into memory START
	readimagefile("blueBall.jpg" , 10 , 10 , 60 , 60);
	imgSize = imagesize(10 , 10 , 60 , 60);
	blueBall = malloc(imgSize);
	getimage(10 , 10 ,60 , 60 , blueBall);
	putimage(80 , 80 , blueBall , XOR_PUT);
	cleardevice();
	readimagefile("redBall.jpg" , 10 , 10 , 60 , 60);
	imgSize = imagesize(10 , 10 , 60 , 60);
	redBall = malloc(imgSize);
	getimage(10 , 10 ,60 , 60 , redBall);
	putimage(80 , 80 , redBall , XOR_PUT);
	cleardevice();
	readimagefile("yellowBall.jpg" , 10 , 10 , 60 , 60);
	imgSize = imagesize(10 , 10 , 60 , 60);
	yellowBall = malloc(imgSize);
	getimage(10 , 10 ,60 , 60 , yellowBall);
	putimage(80 , 80 , yellowBall , XOR_PUT);
	cleardevice();
	readimagefile("firework.jpg" , 10 , 10 , 60 , 60);
	imgSize = imagesize(10 , 10 , 60 , 60);
	fireWork = malloc(imgSize);
	getimage(10 , 10 ,60 , 60 , fireWork);
	putimage(80 , 80 , fireWork , XOR_PUT);
	cleardevice();
	//Adding balls into memory END


	userChoice = Main_Menu();		//Takes user choice for main menu
	while (userChoice != '3') {		//Main game loop START
		userChoice = Main_Menu();
		if (userChoice == '1') {
			//Plays games
			cleardevice();
			//readimagefile("cannon.jpg",350,520,425,595);	//Displays cannon
			//gridCounter = 126;
			//bubbleGrid = (int *)malloc(126 * sizeof(int));
			//Drawing line START
			setcolor(YELLOW);
			line(0, endLine, xLimit , endLine);
			setcolor(WHITE);
			//Drawing line END
			gridCounter = 0;
			bubbleGrid = (int *)malloc(600 * sizeof(int));
			StartingGrid();
			roundNo = 1;
			score = 0;
			while ((keyPress != 'o')||(gameStop != 1)) {
				system("cls");
				printf("Round: %d\n" , roundNo);
				printf("Your Score is %d!" , score);
				if (gameStop == 1) {
					cleardevice();
					break;
				} else { //MAJOR CHANGE TAKEN!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					xCO = 360 , yCO = 540;
					srand(time(NULL));
					RSEED = 21 + (rand() % 30);
					ballStop = 0;
					/*if (gridCounter <= 6) {
						restrictBalls = 1;
					}
					if (restrictBalls == 1) {
						ballColorThrown = EditedThrowBall();
					} else {
						ballColorThrown = RandomThrowBall();		//Creates a random ball
					}*/

					ballColorThrown = EditedThrowBall();
					//ballColorThrown = RandomThrowBall();		//Creates a random ball TEMP
					rightBoundTouched = 0;
					leftBoundTouched = 0;
					upBoundTouched = 0;
					//keyPress = getch();
					while ((keyPress != 'x')||(keyPress != 'o')||(ballStop != 1)) {
						//AimLine(keyPress);		//Moves the aim sight
						keyPress = getch();
						AimLine(keyPress);		//Moves the aim sight
						if (keyPress == 'x') {
							while (ballStop != 1) {
								BubbleBoundaryCheck();
								BubbleThrow();
								ballStop = BallTouchedGrid();
								if (upBoundTouched == 1) {
									ballStop = 1;
								}
								if (ballStop == 1) {
									burstBall = BubbleBurstCheck();
									//if your new thrown ball is not interactive, add it to bubble grid here
									if (burstBall == 1) {
										//DestroyBalls below
										BubbleBursting();
										free(bubbleBurst);
									} else {
										//bubbleGrid = (int *)realloc(bubbleGrid , (gridCounter + 2) * sizeof(int));
										bubbleGrid[gridCounter] = xCO;
										bubbleGrid[gridCounter + 1] = yCO;
										bubbleGrid[gridCounter + 2] = ballColorThrown;
										gridCounter = gridCounter + 3;

									}
								}
							}
						}
						if (ballStop == 1) {
							break;
						}
					}
					gridMoveCounter = gridMoveCounter + 1;
					if (gridMoveCounter == 7) {
						gridMoveCounter = 0;
						EndLineMovement();
					}
					if (gridCounter <= 0) {
						roundNo = 2;
						//setcolor(BLACK);
						//line(0, endLine, xLimit , endLine);
						cleardevice();
						setcolor(YELLOW);
						endLine = 0;
						line(0, endLine, xLimit , endLine);
						restrictBalls = 0;
						StartingGrid();
					}
					gameStop = FallenGrid();
				}
				while (hangingBalls == 1) {
					hangingBalls = FreeBubbleBurstCheck();
					if (hangingBalls == 1) {
						BubbleBursting();
						free(bubbleBurst);
					}
				}
			}
			getch();
		}
		if (userChoice == '2') {
			Developers();
		}
	}		//Main game loop END
	cleardevice();
	setcolor(WHITE);
	outtextxy(10 , 10 , "Until next time then!");		//Last message when game ends
	free(bubbleGrid);
	free(bubbleBurst);
	getch();
}