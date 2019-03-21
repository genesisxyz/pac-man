/*
 *  Pacman.c
 *  Pac-Man Remake
 *
 *  Created by Damiano Collu on 11/07/11.
 *  Copyright 2011 Università Cagliari Informatica. All rights reserved.
 *
 */

#include "Pacman.h"

void* pacmanController (pacmanController_ARG) {
	
	unsigned int name;
	
	union N n;
	
	name = PACMAN;	
	
	do {
		
		n.value = wgetch(stdscr);
		
		switch (n.value) {
				
			case KEY_UP:
			case KEY_DOWN:	
			case KEY_LEFT:
			case KEY_RIGHT:
				
#ifdef THREADS 
				
				bufferWrite (bufferWrite_VALUES);
				
#else
#ifdef PROCESSES
				
				bufferWrite (bufferWrite_VALUES);
				
#endif
#endif
				break;
			case ' ':
				
				n.value = MISSILE;
				bufferWrite (bufferWrite_VALUES);
				
				break;
				
		}
		
	} while (1);
	
	return NULL;
}

void setNewPacmanPositionFromBuffer (Point* pacmanNextMove, struct bufferElement* element) {
	
	Point newPacmanPosition;
	
	switch (element->n.value) {
			
		case KEY_UP:
			newPacmanPosition.x =  0;
			newPacmanPosition.y = -1;
			break;
		case KEY_DOWN:
			newPacmanPosition.x =  0;
			newPacmanPosition.y =  1;
			break;
		case KEY_LEFT:
			newPacmanPosition.x = -2;
			newPacmanPosition.y =  0;
			break;
		case KEY_RIGHT:
			newPacmanPosition.x =  2;
			newPacmanPosition.y =  0;
			break;
	}
	
	*pacmanNextMove = newPacmanPosition;
}

int scoreUpdate (unsigned int* pills, Points* points, unsigned int* highscore, Layer labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS], Point* pacmanPosition, unsigned int *hit) {
	
	if (*hit == BLUE_GHOST) {
		
		points->value += (400 * points->multiplier);
		points->multiplier++;
		
		attron(A_BOLD);
		
		mvprintw(1, (int)(TAB_SIZE + strlen("1UP") - digits(points->value) + 1), "%d", points->value);
		
		if (points->value > *highscore) {
			
			*highscore = points->value;
			mvprintw(1, (WINDOW_HALF_SIZE_X - digits(*highscore) + 1), "%d", *highscore);
		}
		
		attroff(A_BOLD);
	}
	
	if (labyrinth[(pacmanPosition->y - LABYRINTH_Y)][pacmanPosition->x + 1].element == PILL) {
		
		*pills -= 1;
		
		points->value += 10;
		
		attron(A_BOLD);
		/*
		 raggiungo un numero negativo non viene più aggiornato il punteggio (secondo paremetro di mvprintw)
		 */
		mvprintw(1, (int)(TAB_SIZE + strlen("1UP") - digits(points->value) + 1), "%d", points->value);
		
		if (points->value > *highscore) {
			
			*highscore = points->value;
			mvprintw(1, (WINDOW_HALF_SIZE_X - digits(*highscore) + 1), "%d", *highscore);
		}
		
		attroff(A_BOLD);
		
		labyrinth[(pacmanPosition->y - LABYRINTH_Y)][pacmanPosition->x + 1].element = EMPTY;
		
		return PILL;
	}
	
	else if (labyrinth[(pacmanPosition->y - LABYRINTH_Y)][pacmanPosition->x + 1].element == POWER_PILL) {
		
		*pills -= 1;
		
		points->value += 50;
		
		attron(A_BOLD);
		mvprintw(1, (int)(TAB_SIZE + strlen("1UP") - digits(points->value) + 1), "%d", points->value);
		
		if (points->value > *highscore) {
			
			*highscore = points->value;
			mvprintw(1, (WINDOW_HALF_SIZE_X - digits(*highscore) + 1), "%d", *highscore);
		}
		
		attroff(A_BOLD);
		
		labyrinth[(pacmanPosition->y - LABYRINTH_Y)][pacmanPosition->x + 1].element = EMPTY;
		
		return POWER_PILL;
	}
	
	else {
		
		return ERR;
	}
}

void newPacmanController (newPacmanController_ARG) {

#ifdef THREADS
	
	pthread_create(thread, NULL, &pacmanController, NULL);
	
	pthread_detach(*thread);
	
#endif
	
#ifdef PROCESSES
	
	*process = fork();
	
	if (*process == 0) {
		
		close(buffer[0]);
		pacmanController(buffer[1]);
		/* exit(0) non neccessario (la funzione ghostName ha un ciclo infinito while(1){...}) */
	}
	
	else if (*process == ERR) {
		
		endwin();
		printf("fork() failed.\n");
		exit(1);
	}
	
#endif
    
#ifdef SYSTEM_V
    
    *process = fork();
	
	if (*process == 0) {
        
		pacmanController();
		/* exit(0) non neccessario (la funzione ghostName ha un ciclo infinito while(1){...}) */
	}
	
	else if (*process == ERR) {
		
		endwin();
		printf("fork() failed.\n");
		exit(1);
	}
    
#endif
}
