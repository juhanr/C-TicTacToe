/*
 * Author: Juhan-Rasmus Risti
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

char HUMAN = 'X';
char AI = 'O';
char EMPTY = '-';
char board[9] = { '-', '-', '-', '-', '-', '-', '-', '-', '-' };
int locations[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
int isGameOver = 0;
int AIMoves = 0;

void startGame();
char getChar();
int getInt();
int charToInt(char c);
void startTurn(char player);
void move(char player, int location);
int getAIMoveLocation();
int getIntArrayLength(int array[]);
void checkIfWon(char player);
void checkIfBoardFull();
void setBoardValues(int result[]);
void gameOver(char* message);
void showBoard();
void showLocations();

int main() {
	startGame();
	return 0;
}

void startGame() {
	char input;
	printf("=== Tic-Tac-Toe ===\n\n"
			"Do you want to start first? (Y/N): ");
	input = getChar();
	if (input == 'Y')
		startTurn(HUMAN);
	else if (input == 'N')
		startTurn(AI);
	else {
		printf("Invalid input!\n");
		startGame();
	}
}

char getChar() {
	char str[BUFSIZ];
	scanf("%s", str);
	return toupper(str[0]);
}

int getInt() {
	char str[BUFSIZ];
	scanf("%s", str);
	return charToInt(str[0]);
}

int charToInt(char c) {
	return c - '0';
}

void startTurn(char player) {
	if (player == HUMAN) {
		int x;
		printf("\n--- Your turn ---\n\n");
		showBoard();
		showLocations();
		printf("\n");
		while (1) {
			printf("Please choose a location: ");
			x = getInt();
			if (x >= 0 && x < 9) {
				if (board[x] != EMPTY)
					printf("The location is already taken!\n");
				else {
					printf("You made a move to location %d.\n", x);
					move(player, x);
					if (!isGameOver)
						startTurn(AI);
					break;
				}
			} else
				printf("Invalid input!\n");
		}
	} else {
		printf("\n--- AI's turn ---\n\n"
				"AI made his move.\n");
		move(AI, getAIMoveLocation());
		AIMoves++;
		if (!isGameOver)
			startTurn(HUMAN);
	}
}

void move(char player, int location) {
	board[location] = player;
	checkIfWon(player);
	if (!isGameOver)
		checkIfBoardFull();
}

int getAIMoveLocation() {
	int k, i, j, boardValues[8], combinations[3];
	combinations[0] = 2 * AI + EMPTY;
	combinations[1] = 2 * HUMAN + EMPTY;
	combinations[2] = AI + 2 * EMPTY;
	setBoardValues(boardValues);
	for (k = 0; k < 3; k++) {
		for (i = 0; i < 8; i++) {
			if (boardValues[i] == combinations[k]) {
				switch (i) {
				case 0:
					for (j = 0; j < 3; j++)
						if (board[j] == EMPTY)
							return j;
					break;
				case 1:
					for (j = 3; j < 6; j++)
						if (board[j] == EMPTY)
							return j;
					break;
				case 2:
					for (j = 6; j < 9; j++)
						if (board[j] == EMPTY)
							return j;
					break;
				case 3:
					for (j = 0; j < 9; j = j + 3)
						if (board[j] == EMPTY)
							return j;
					break;
				case 4:
					for (j = 1; j < 9; j = j + 3)
						if (board[j] == EMPTY)
							return j;
					break;
				case 5:
					for (j = 2; j < 9; j = j + 3)
						if (board[j] == EMPTY)
							return j;
					break;
				case 6:
					for (j = 2; j < 7; j = j + 2)
						if (board[j] == EMPTY)
							return j;
					break;
				case 7:
					for (j = 0; j < 9; j = j + 4)
						if (board[j] == EMPTY)
							return j;
					break;
				}
			}
		}
	}

	if (AIMoves == 0) {
		if (board[4] == EMPTY)
			return 4;
		else {
			int cornerMoves[4] = { 0, 2, 6, 8 };
			srand(time(NULL));
			return cornerMoves[rand() % getIntArrayLength(cornerMoves)];
		}
	} else {
		while (1) {
			int randomIndex;
			srand(time(NULL));
			randomIndex = rand() % strlen(board);
			if (board[randomIndex] == EMPTY)
				return randomIndex;
		}
	}
	return 0;
}

int getIntArrayLength(int array[]) {
	return (int) (sizeof(array) / sizeof(array[0]));
}

void checkIfWon(char player) {
	int boardValues[8], i;
	setBoardValues(boardValues);
	if (player == HUMAN) {
		for (i = 0; i < 8; i++) {
			if (boardValues[i] == 3 * HUMAN) {
				gameOver("You won!");
				break;
			}
		}
	} else {
		for (i = 0; i < 8; i++) {
			if (boardValues[i] == 3 * AI) {
				gameOver("You lost!");
				break;
			}
		}
	}
}

void checkIfBoardFull() {
	int i;
	for (i = 0; i < 9; i++) {
		if (board[i] == EMPTY)
			return;
	}
	gameOver("It's a tie!");
}

void setBoardValues(int result[]) {
	result[0] = board[0] + board[1] + board[2]; /* row 1 */
	result[1] = board[3] + board[4] + board[5]; /* row 2 */
	result[2] = board[6] + board[7] + board[8]; /* row 3 */
	result[3] = board[0] + board[3] + board[6]; /* column 1 */
	result[4] = board[1] + board[4] + board[7]; /* column 2 */
	result[5] = board[2] + board[5] + board[8]; /* column 3 */
	result[6] = board[2] + board[4] + board[6]; /* diagonal 1 */
	result[7] = board[0] + board[4] + board[8]; /* diagonal 2 */
}

void gameOver(char* message) {
	printf("\n");
	showBoard();
	printf("\n%s\n", message);
	isGameOver = 1;
	while (1) {
		char input;
		printf("Do you want to start a new game? (Y/N):");
		input = getChar();
		printf("\n");
		if (input == 'Y')
			startGame();
		else if (input == 'N')
			break;
		else
			printf("Invalid input!\n");
	}
}

void showBoard() {
	int i;
	printf("- Board -\n");
	for (i = 0; i < 9; i = i + 3)
		printf("  %c %c %c\n", board[i], board[i + 1], board[i + 2]);
}

void showLocations() {
	int i;
	printf("\n- Locations -\n");
	for (i = 0; i < 9; i = i + 3)
		printf("  %d %d %d\n", locations[i], locations[i + 1],
				locations[i + 2]);
}
