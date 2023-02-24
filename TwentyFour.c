/*
/ Robert Barrera
/ CS 141 at UIC
/ Program 1: TWENTY FOUR
/
/ Retry of Program 1 in CS 141 in C
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displayIntro() {
	printf("Author: Robert Barrera\n");
	printf("Program: #1, TwentyFour\n");
	printf("TA: Forgot\n");
	printf("Aug 01, 2020\n\n");
	
	printf("Welcome to the game of TwentyFour.  Using each of the four numbers shown\n");
	printf("below exactly once, combining them somehow with the basic mathematical\n");
	printf("operators (+,-,*,/) to yield the value twenty-four.\n\n");
}


void displayExit() {
	printf("\nThanks for playing. Exiting program...\n");	
}


char getOperatorAndAnswer(int count, float *answer, float var1, float var2) {	
	switch (count) {
		case 1:
			*answer = var1 + var2;
			return '+';
		case 2:
			*answer = var1 - var2;
			return '-';
		case 3:
			*answer = var1 * var2;
			return '*';
		case 4:
			*answer = var1 / var2;
			return '/';
	}
}


void displaySolutions(int *num1, int *num2, int *num3, int *num4) {
	int debug = 1;
	float answer = 0.0;
	int var1, var2, var3, var4;
	int count1, count2, count3;
	char operator1, operator2, operator3 = 'x';
	char finalOp1, finalOp2, finalOp3 = 'x';
	int randomNumber = (rand()%3185) + 1;
	
	
	if (debug) {
		printf("*** Start Debug Display ***\n");
		printf("All possible solutions are:\n");
	}
	
	int count = 1;
	for (var1 = 1; var1 <= 9; var1++) {
		for (var2 = 1; var2 <= 9; var2++) {
			for (var3 = 1; var3 <= 9; var3++) {
				for (var4 = 1; var4 <= 9; var4++) {
					for (count1 = 1; count1 <= 4; count1++) {
						for (count2 = 1; count2 <= 4; count2++) {
							for (count3 = 1; count3 <= 4; count3++) {
								operator1 = getOperatorAndAnswer(count1, &answer, (float)var1, (float)var2);
								operator2 = getOperatorAndAnswer(count2, &answer, answer, (float)var3);
								operator3 = getOperatorAndAnswer(count3, &answer, answer, (float)var4);
								
								if(answer == 24.00) {
									if (randomNumber == count) {
										*num1 = var1;
										*num2 = var2;
										*num3 = var3;
										*num4 = var4;
										finalOp1 = operator1;
										finalOp2 = operator2;
										finalOp3 = operator3;	
									}
									
									if (debug) {
										printf("%d: %d%c%d%c%d%c%d\n", 
											count, var1, operator1, var2, operator2, var3, operator3, var4);
									}
										
									count++;
								}
							}
						}
					}
				}
			}
		}
	}
	
	printf("Puzzle to choose is #%d: %d%c%d%c%d%c%d\n", 
		randomNumber, *num1, finalOp1, *num2, finalOp2, *num3, finalOp3, *num4);
	if (debug) {
		printf("*** End Debug Display ***\n");	
	}
}


int checkInputCharacters(char *userInput) {
	int counter;
	
	for (counter = 0; counter <= 2; counter++) {
		if (userInput[counter] != '+' && 
				userInput[counter] != '-' && 
				userInput[counter] != '*' && 
				userInput[counter] != '/') {
			return 1;
		}
	}
	
	return 0;
}


float solve2Numbers(float num1, float num2, char op) {
	if (op == '+') {
		return num1 + num2;
	}
	else if (op == '-') {
		return num1 - num2;
	}
	else if (op == '*') {
		return num1 * num2;
	}
	else if (op == '/') {
		return num1 / num2;
	}
}


void getSolution(int num1, int num2, int num3, int num4) {
	char op1, op2, op3;
	int count1, count2, count3;
	float answer;
	
	for (count1 = 1; count1 <= 4; count1++) {
		for (count2 = 1; count2 <= 4; count2++) {
			for (count3 = 1; count3 <= 4; count3++) {
				op1 = getOperatorAndAnswer(count1, &answer, (float)num1, (float)num2);
				op2 = getOperatorAndAnswer(count2, &answer, answer, (float)num3);
				op3 = getOperatorAndAnswer(count3, &answer, answer, (float)num4);
				
				if(answer == 24.00) {
					printf("Sorry, that was not correct. The correct answer was: %d%c%d%c%d%c%d\n\n", 
													num1, op1, num2, op2, num3, op3, num4);	
				}
			}
		}
	}
	
		
}


void solveUserInput(char *userInput, int num1, int num2, int num3, int num4) {
	float answer;
	
	printf("%3.1f %c %d is: ", (float)num1, userInput[0], num2);
	answer = solve2Numbers((float)num1, (float)num2, userInput[0]);
	printf("%3.1f\n", answer);
	
	printf("%3.1f %c %d is: ", answer, userInput[1], num3);
	answer = solve2Numbers(answer, (float)num3, userInput[1]);
	printf("%3.1f\n", answer);
	
	printf("%3.1f %c %d is: ", answer, userInput[2], num4);
	answer = solve2Numbers(answer, (float)num4, userInput[2]);
	printf("%3.1f\n\n", answer);
	
	if (answer == 24.00) {
		printf("Well done, genius!\n\n");	
	}
	else {
		getSolution(num1, num2, num3, num4);
	}
	
}


void requestUserInput(int *keepPlaying, int num1, int num2, int num3, int num4) {
	int incorrectInput = 0;
	int retry = 0;
	char yesNo[4];
	char userInput[4];
	
	do {
		printf("Enter the three operators to be used (+,-,*, or /):\n");
		scanf("%s", userInput);
		
		if (strlen(userInput) != 3) {
			retry = 1;
			printf("*** Sorry, that input is the wrong length. Please retry. ***\n");
		}
		else if (checkInputCharacters(userInput)) {
			retry = 1;
			printf("*** Sorry, invalid characters in input. Please retry. ***\n");	
		}
		else {
		retry = 0;	
		}
	} while(retry);
	
	solveUserInput(userInput, num1, num2, num3, num4);
	
	do {
			printf("Would you like to play again (Y/N): \n");
			scanf("%s", yesNo);
			
			if (yesNo[0] == 'N' || yesNo[0] == 'n') {
				*keepPlaying = 0;
				incorrectInput = 0;
			}
			else if (yesNo[0] == 'Y' || yesNo[0] == 'y') {
				*keepPlaying = 1;
				incorrectInput = 0;
			}
			else {
				incorrectInput = 1;
			}
		} while (incorrectInput);
}


int main() {
	int num1, num2, num3, num4 = 0;
	int keepPlaying = 1;
	char yesNo[3] = "   ";
	
	srand(time(0));

	displayIntro();
	
	do {
		displaySolutions(&num1, &num2, &num3, &num4);
		
		printf("\nThe numbers to use are: %d, %d, %d, %d\n\n", num1, num2, num3, num4);
			
		requestUserInput(&keepPlaying, num1, num2, num3, num4);
	} while (keepPlaying);	 
	displayExit();	
	
	return 0;
}
