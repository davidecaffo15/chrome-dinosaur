/**
  \file menu.c
  \author Ambrosi Vlad
  \version 1.0
  \date 29-01-2023
 */


#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#include "menu.h"
#include "game.h"
#include "appearance.h"

/**
  \fn void startMenu()
  \brief gets the highscore from highscore.txt file and the game asks u to insert ur username and age, also here we can find the commands "space" and "k"
  \param int maxX: this variable defines a maximum of letters for ur name
  \param int maxX: this variable defines a minimum of letters for ur name
  \return its a "VOID" function so it has no return
 */
void startMenu() {
	struct user firstUser;
	int highScore;
    // Read high score
	FILE *highScoreFile;
	highScoreFile = fopen("./highScore.txt", "r");
	fscanf(highScoreFile, "%d", &highScore);
	fclose(highScoreFile);
	int maxX = getmaxx(stdscr)/2;
	int maxY = getmaxy(stdscr)/2;
	init_pair(3,COLOR_GREEN,COLOR_BLACK);
	attron(COLOR_PAIR(3));
	showTrex(maxY, maxX);
	attroff(COLOR_PAIR(3));
	mvprintw(maxY+1, maxX-28, "Version 1.1.0");
    // Get info
	mvprintw(maxY+1, maxX-28, "Write inputs and press Enter to start the Game.");
    mvprintw(maxY+2, maxX-26, "When you had prize, fire it with 'k' key!");
	mvprintw(maxY+3, maxX-21, "You can jump with space key!");
	mvprintw(maxY+4, maxX-15, "Name: ");
	getstr(firstUser.name);
	mvprintw(maxY+5, maxX-15, "Last name: ");
	getstr(firstUser.lastName);
	mvprintw(maxY+6, maxX-15, "Age: ");
	getstr(firstUser.age);
	noecho();
	startEngine(highScore, firstUser);
}
/**
  \fn endGame(int score, int highScore, int diY, int diX, struct user firstUser)
  \brief once the game ends this function gets the current score and if the score is greater then the high score, the higscore will get deleted and the current score will be written in the .txt file, then the current user will be asked if he wants to close the program or restart it
  \return its a "VOID" function so it has no return
 */
void endGame(int score, int highScore, int diY, int diX, struct user firstUser) {
	nodelay(stdscr, FALSE);
	init_pair(2,COLOR_RED,COLOR_BLACK);
    // Save
	if (score > highScore) {
		highScore = score;
		FILE *highScoreFile;
		highScoreFile = fopen("./highScore.txt", "w");
		fprintf(highScoreFile, "%d", highScore);
		fclose(highScoreFile);
	}
	int maxX = getmaxx(stdscr)/2;
	int maxY = getmaxy(stdscr)/2;
	attron(COLOR_PAIR(2));
	showLoss(maxY, maxX);
	mvprintw(diY-4, diX, "          X-X ");
	mvprintw(diY, diX, "      ||");
	char keyToExit = getch();
    // Exit or restart
	if (keyToExit == 'r') {
		attroff(COLOR_PAIR(2));
		startEngine(highScore, firstUser);
	}
	else if (keyToExit == 'q') {
		return;
	}
	else {
		endGame(score, highScore, diY, diX, firstUser);
	}
}
