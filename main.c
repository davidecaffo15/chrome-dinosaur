/**
  \file main.c
  \author Ambrosi Vlad
  \version 1.0
  \date 29-01-2023
 */

#include <ncurses.h>
#include <stdio.h>
#include "menu.h"
#include "minunit.h"
/**
  \fn int main(int argc, char **argv)
  \brief this file simplly recalls all other files into one
  \param the only paramaters in this function we have only argc and argv but they are not being used
  \return in this function our return is "0"
 */
int main(int argc, char **argv) {
	initscr();
	start_color();
	curs_set(FALSE);
	startMenu();
	endwin();

    return 0;
}
