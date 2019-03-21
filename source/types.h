/*
 *  types.h
 *  Pac-Man Remake
 *
 *  Created by Damiano Collu on 01/07/11.
 *  Copyright 2011 Università Cagliari Informatica. All rights reserved.
 *
 */

#ifndef TYPES
#define TYPES

#include <sys/types.h>
#include <ncurses.h>

/* il programma può bloccarsi a causa dei seguenti errori */
#define PIPE_ERR	"pipe error"

/* tabulazione definita come 8 spazi verso destra */
#define TAB_SIZE	8

#define NO					0
#define YES					1

#define MICROSECOND			1000000
#define SECOND				MICROSECOND

#define FAKE_FPS                 1000

#define REFRESH				(SECOND/FAKE_FPS)                

#define READY_LABEL_POSITION	(18 + LABYRINTH_Y), 27
#define GAMEOVER_LABEL_POSITION	(18 + LABYRINTH_Y), 25
#define LABYRINTH_ROWS				33
#define LABYRINTH_COLS				60
/* posizione assoluta del labirinto */
#define LABYRINTH_Y				2
#define LABYRINTH_X				0

#define WINDOW_SIZE_X		LABYRINTH_COLS
#define WINDOW_SIZE_Y		(LABYRINTH_Y + LABYRINTH_ROWS)
#define WINDOW_HALF_SIZE_X	(WINDOW_SIZE_X / 2)
#define WINDOW_HALF_SIZE_Y	(WINDOW_SIZE_Y / 2)

#define LABYRINTH_WALL_BLINK		200000
#define LABYRINTH_WALL_WIN_TIMES	4

/*
 Determina anche la grandezza dell'array che conterrà i fantasmi.
*/

#define GHOSTS_NUMBER			8

/* probabilità di lanciare un missile */
#define SHOOT_MISSILE			5

#define GHOST_INFECTED			10
#define GHOST_INFECTED_END		3
#define GHOST_INFECTED_BLINK	0.2

#define GHOST_SPEED			(SECOND/5)

#define PACMAN_SCHEDULE		(REFRESH * FAKE_FPS * 0.1)

/*
 Non puoi usare il valore 0, puoi modificare queste a piacimento (anche l'ordine)
*/
#define DEFAULT_COLOR 		1
#define EMPTY			2
#define LABYRINTH_WALL 		3
#define GHOST_GATE		4
#define GHOST_DOOR		5
#define PILL			6
#define POWER_PILL		7
#define READY_LABEL		8
#define GAMEOVER_LABEL		9
#define START_LABEL		10
#define PLAYERS_LABEL		11
#define BONUS_LABEL		12
#define COPYRIGHT_LABEL		13
#define LABYRINTH_WALL_WIN	14
#define BLUE_GHOST		15
#define BLUE_GHOST_BLINK	16

/*
 la definizione di Pac-Man e quelle successive devono essere numeri sequenziali senza buchi.
 Esempio:
 PACMAN = 10, RED_GHOST = 11 (corretto)
 PACMAN = 10, RED_GHOST = 12 (sbagliato)
*/
#define PACMAN				17
/*
 Pac-Man perde una vita se incontra uno di questi oggetti.
 */
#define RED_GHOST			18
#define GREEN_GHOST 			19
#define CYAN_GHOST			20
#define WHITE_GHOST 			21

#define RED_GHOST_			22
#define GREEN_GHOST_		23
#define CYAN_GHOST_         24
#define WHITE_GHOST_		25

#define MISSILE				26

#ifdef THREADS

#ifdef _MACHTYPES_H_

#define _NULL NULL

#else 

#define _NULL 0

#endif

#endif

#if defined PROCESSES || defined SYSTEM_V

#define _NULL 0

#endif

typedef struct point {
	
	int x, y;
	
} Point;

/* definisce un oggetto per un elemento grafico che sia grande 2 caratteri (in larghezza) */
typedef struct sprite2x1 {
	
	unsigned int colorPair;
	chtype charEyes;
	
	Point position;
	Point lastMove;
	
	unsigned int name;
	
} Sprite2x1;

typedef struct missile {

	Sprite2x1 image;
	
#ifdef THREADS
	
	pthread_t name;
	
#endif
	
#if defined PROCESSES || defined SYSTEM_V
	
	pid_t name;
	
#endif
	
} Missile;

typedef struct layer {
	
	unsigned int element;
	Sprite2x1 *sprite;
	Missile *missile;
} Layer;

/* per utilizzare un solo buffer per il missile che scrive un diverso valore dal fantasma e da Pac-Man */
union N {
	
#ifdef THREADS
	
	pthread_t id;
	
#endif
	
#ifdef PROCESSES
	
	pid_t id;
	
#endif
	
	unsigned int value;
};

#ifdef THREADS

struct bufferElement {
	
	/* dati */
	union N n;
	unsigned int name;
	/* elemento successivo */
	struct bufferElement* next;
};

#endif

#ifdef PROCESSES

struct bufferElement {
	
	/* dati */
	union N n;
	unsigned int name;
};

#endif

#ifdef SYSTEM_V

struct bufferElement {
	
	/* dati */
	union N n;
	unsigned int name;
	/* elemento successivo */
	int next;
};

#endif

typedef struct pills {
	
	unsigned int value;
	unsigned int initialValue;
} Pills;

typedef struct lifes {

	unsigned int value;
	/* barra della vita corrente */
	unsigned int life;
} Lifes;

typedef struct points {

	unsigned int value;
	/* moltiplicatore punteggio fantasma mangiato */
	unsigned int multiplier;
} Points;

typedef struct sprite {
	
#ifdef THREADS
	
	pthread_t name;
	
#endif
	
#if defined PROCESSES || SYSTEM_V
	
	pid_t name;
	
#endif
	
	Sprite2x1 image;
	Point initialPosition;
	
	/* un missile per ogni direzione (solo verticale e orizzontale) */
	Missile missile[4];
	
} Sprite;

#endif
