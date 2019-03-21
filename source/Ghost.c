/*
 *  Ghost.c
 *  Pac-Man Remake
 *
 *  Created by Damiano Collu on 11/07/11.
 *  Copyright 2011 Università Cagliari Informatica. All rights reserved.
 *
 */

#include "Ghost.h"

void* ghostNewDirection (ghostNewDirection_ARG) {
	
	union N n;
	
#if defined THREADS
	
	unsigned int name;
	
	name = *((unsigned int*)arg);
	
#endif
	
	/* Attesa prima di iniziare a muoversi */
	sleep(((rand()%3) + 1));
	
	while (1) {
        
		/* probabilità di lancio dei missili, se il numero generato casualmente è 0 i missili se non ci sono ostacoli vengono lanciati (1 per direzione, orizzontalmente e verticalmente) */
		if (rand()%SHOOT_MISSILE == 0) {
			
			/* scrive il numero che identifica il missile */
			n.value = MISSILE;
			
			/* scrive il numero nel buffer */
			bufferWrite(bufferWrite_VALUES);
		}
		
		else {
			
			/* Il numero impostato qui servirà poi al main() per muovere il fantasma ed eventualmente farli cambiare direzione */
			n.value = rand() % 3;
			
			/* scrive il numero nel buffer */
			bufferWrite(bufferWrite_VALUES);
			
			usleep(GHOST_SPEED);
		}
	}
	
	return NULL;
}

unsigned int ghostHitPacman (Layer labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS], Point *position, Sprite* pacman, Sprite ghost[GHOSTS_NUMBER], unsigned int ghostHits[(GHOSTS_NUMBER / 2)]) {
	
	/* Sprite sul labirinto da controllare */
	Sprite2x1* sprite = labyrinth[(position->y - LABYRINTH_Y)][position->x].sprite;
	
	unsigned int missileFromSprite;
	
    unsigned int hit = 0;
    
    /* controlla se c'è un missile in quella posizione  */
    if (labyrinth[(position->y - LABYRINTH_Y)][position->x].missile != NULL) {
        
        /* questo calcolo determina chi ha lanciato il missile */
        missileFromSprite = ((4 * (PACMAN + 1)) + (labyrinth[(position->y - LABYRINTH_Y)][position->x].missile->image.name - MISSILE)) / 5;
        
        /* se la Sprite è Pac-Man, segna come colpito (Pac-Man non scrive mai la sua posizione prima di controllare una collisione) */
        if (missileFromSprite != pacman->image.name && labyrinth[(position->y - LABYRINTH_Y)][position->x].missile->image.position.x == pacman->image.position.x &&
                 labyrinth[(position->y - LABYRINTH_Y)][position->x].missile->image.position.y == pacman->image.position.y) {
            
            /* elimina il missile */
            killMissile(labyrinth[(position->y - LABYRINTH_Y)][position->x].missile, &ghost[missileFromSprite], labyrinth);
            
            hit = MISSILE;
        }
        
        /* se il missile arriva da Pac-Man, uccide il fantasma che si trova nella posizione */
        else if (sprite != NULL && sprite != &pacman->image && missileFromSprite == PACMAN) {
            
            /* elimina il missile */
            killMissile(labyrinth[(position->y - LABYRINTH_Y)][position->x].missile, pacman, labyrinth);
            
            /* il fantasma colpito ritorna alla posizione iniziale */
            resetSprite(&ghost[sprite->name - PACMAN - 1], '-');
            
            /* il contatore che tiene traccia di quante volte il fantasma è stato colpito viene incrementato di 1 */
            ghostHits[sprite->name - PACMAN - 1]++;
            
            hit = NO;
        }
    }
    
	/* controlla se c'è una Sprite in quella posizione */
	if (sprite != NULL) {
		
		/* caso in cui Pac-Man si trova nella stessa posizione di un fantasma */
		if (sprite != &pacman->image && (pacman->image.position.x == sprite->position.x && pacman->image.position.y == sprite->position.y)) {
		
			/* controlla se il fantasma è sotto l'effetto di una power pill */
			if (sprite->colorPair < PACMAN) {
				
				/* il fantasma ritorna alla posizione iniziale */
				resetSprite(&ghost[sprite->name - PACMAN - 1], '-');
				
				/* il contatore che tiene traccia di quante volte il fantasma è stato colpito viene incrementato di 1 */
				ghostHits[sprite->name - PACMAN - 1]++;
				
				hit = BLUE_GHOST;
			}
			
			else {
				
				hit = YES;
			}
		}

	}
    
    return hit;
}

void setNewGhostPosition (Sprite ghost[GHOSTS_NUMBER], Layer labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS], struct bufferElement* element) {
	
	Sprite* ghostToRefresh;
	
	Point newSpritePosition;
	
	int i = 0;
	
	/* fantasma da aggiornare */
	ghostToRefresh = &ghost[(element->name - PACMAN - 1)];
	
	newSpritePosition.x = (ghostToRefresh->image.position.x + ghostToRefresh->image.lastMove.x);
	newSpritePosition.y = (ghostToRefresh->image.position.y + ghostToRefresh->image.lastMove.y);
	
	/* controlla se un fantasma sta per passare sopra un altro fantasma, in questo caso si invertono le direzioni di questi fantasmi che andrebbero a collidere (rimbalzo) */
	if (newSpritePosition.x > 0 && newSpritePosition.x < LABYRINTH_COLS &&
		labyrinth[newSpritePosition.y - LABYRINTH_Y][newSpritePosition.x].sprite != NULL &&
		labyrinth[newSpritePosition.y - LABYRINTH_Y][newSpritePosition.x].sprite->name > PACMAN &&
		labyrinth[newSpritePosition.y - LABYRINTH_Y][newSpritePosition.x].sprite->name < MISSILE) {
		
		/* il fantasma contro il cui si stava andando a collidere prende la direzione del fantasma corrente */
		ghost[labyrinth[newSpritePosition.y - LABYRINTH_Y][newSpritePosition.x].sprite->name - PACMAN-1].image.lastMove = ghostToRefresh->image.lastMove;
		
		/* il fantasma corrente inverte la sua direzione */
		inverseDirectionForSprite(&ghostToRefresh->image);
	}
	
	newSpritePosition = ghostToRefresh->image.lastMove;
	
	/* ad ogni nuovo spostamento il fantasma prova direzioni diverse (in base al numero che "riceve" dal buffer) */
	do {
		
		ghostToRefresh->image.lastMove = newSpritePosition;
		
		/* Prova tutte le direzioni possibili tranne quella inversa a quella corrente (le direzioni possibili al massimo sono 4), se tutte queste non sono possibili, inverte la direzione */
		if (i == 3) {
			
			inverseDirectionForSprite(&ghostToRefresh->image);
		}
		
		else {
			
			/*
			 Nel caso il numero che è stato recuperato dal buffer sia 0, il fantasma prova a continuare a muoversi nella direzione corrente, negli altri 2 casi prova le direzioni opposte:
			 esempio: il fantasma si muove a destra, dal buffer verrà preso il numero che identifica se vuole cambiare direzioni o meno, a prescindere da questo in questo caso avremo che 
			 se il numero è 0 verrà provato di nuovo il movimento verso destra, nel caso sia 1 proverà a muoversi verso l'alto, verso il basso nell'altro caso (2)
			*/
			
			/* il fantasma si sta muovendo verso sinistra */
			if (ghostToRefresh->image.lastMove.x == -2) {
				
				switch (element->n.value) {
						
					case 0:
						ghostToRefresh->image.lastMove.x = -2;
						ghostToRefresh->image.lastMove.y = 0;
						break;
					case 1:
						ghostToRefresh->image.lastMove.x = 0;
						ghostToRefresh->image.lastMove.y = -1;
						break;
					case 2:
						ghostToRefresh->image.lastMove.x = 0;
						ghostToRefresh->image.lastMove.y = 1;
						break;
				}
			}
			
			/* il fantasma si sta muovendo verso destra */
			else if (ghostToRefresh->image.lastMove.x == 2) {
				
				switch (element->n.value) {
						
					case 0:
						ghostToRefresh->image.lastMove.x = 2;
						ghostToRefresh->image.lastMove.y = 0;
						break;
					case 1:
						ghostToRefresh->image.lastMove.x = 0;
						ghostToRefresh->image.lastMove.y = -1;
						break;
					case 2:
						ghostToRefresh->image.lastMove.x = 0;
						ghostToRefresh->image.lastMove.y = 1;
						break;
				}
			}
			
			/* il fantasma si sta muovendo verso l'alto */
			else if (ghostToRefresh->image.lastMove.y == -1) {
				
				switch (element->n.value) {
						
					case 0:
						ghostToRefresh->image.lastMove.x = 0;
						ghostToRefresh->image.lastMove.y = -1;
						break;
					case 1:
						ghostToRefresh->image.lastMove.x = -2;
						ghostToRefresh->image.lastMove.y = 0;
						break;
					case 2:
						ghostToRefresh->image.lastMove.x = 2;
						ghostToRefresh->image.lastMove.y = 0;
						break;
				}
			}
			
			/* il fantasma si sta muovendo verso il basso */
			else if (ghostToRefresh->image.lastMove.y == 1) {
				
				switch (element->n.value) {
						
					case 0:
						ghostToRefresh->image.lastMove.x = 0;
						ghostToRefresh->image.lastMove.y = 1;
						break;
					case 1:
						ghostToRefresh->image.lastMove.x = -2;
						ghostToRefresh->image.lastMove.y = 0;
						break;
					case 2:
						ghostToRefresh->image.lastMove.x = 2;
						ghostToRefresh->image.lastMove.y = 0;
						break;
				}
			}
			
			element->n.value = (element->n.value + 1) % 3;
			
			i++;				
		}
		
		/* prova la nuova posizione finche non ne trova una possibile (se il fantasma si trova circondato da muri in questo caso il programma non va avanti) */
	} while (!canMove(&ghostToRefresh->image.position, &ghostToRefresh->image.lastMove, labyrinth));
	
	/* elimina la vecchia posizione del fantasma */
	eraseSprite(ghostToRefresh->image.position, labyrinth);
	
	/* imposta la nuova posizione */
	setSpritePositionFromLastMove(ghostToRefresh);
	
	/* disegna il fantasma sulla nuova posizione e lo segna sul labirinto */
	drawSpriteInLabyrinth(&ghostToRefresh->image, labyrinth);
}

void ghostsTransform (int* countdown, Sprite ghost[GHOSTS_NUMBER], unsigned int* ghostsBlinkingSchedule) {
	
	int i;
	
	for (i = 0; i < GHOSTS_NUMBER; i++) {
		
		/* controlla se il thread del fantasma è già stato creato */
		if (ghost[i].name != _NULL) {
			
			/* rende vulnerabile il fantasma, cambia aspetto e inverte la direzione */
			modifySprite(&ghost[i].image, BLUE_GHOST, '\'');
			inverseDirectionForSprite(&ghost[i].image);
			drawSprite(&ghost[i].image);
		}
	}
	
	/* tempo per cui deve rimanere in questo stato */
	*countdown = (FAKE_FPS * REFRESH * GHOST_INFECTED);
	*ghostsBlinkingSchedule = 0;
}

void checkGhostsTransform (int* countdown, Sprite ghost[GHOSTS_NUMBER], unsigned int* ghostsBlinkingSchedule) {
	
	int i;
	
	if (*countdown > 0) {
		
		/* i fantasmi vulnerabili iniziano a lampeggiare */
		if (*countdown < (FAKE_FPS * REFRESH * GHOST_INFECTED_END) && *ghostsBlinkingSchedule >= (FAKE_FPS * REFRESH * GHOST_INFECTED_BLINK)) {
			
			for (i = 0; i < GHOSTS_NUMBER; i++) {
				
				/* controlla che il colore del fantasma non sia quello normale (non vulnerabile) */
				if (!(ghost[i].image.colorPair > PACMAN)) {
					
					/* alterna i colori */					
					switch (ghost[i].image.colorPair) {
						case BLUE_GHOST:
							modifyColor(&ghost[i].image, BLUE_GHOST_BLINK);
							drawSprite(&ghost[i].image);
							break;
						case BLUE_GHOST_BLINK:
							modifyColor(&ghost[i].image, BLUE_GHOST);
							drawSprite(&ghost[i].image);
							break;
					}
				}
			}
			
			*countdown -= REFRESH;
			
			*ghostsBlinkingSchedule = 0;
		}
		
		else {
			
			*countdown -= REFRESH;
			*ghostsBlinkingSchedule += REFRESH;
		}
	}
	
	else if (*countdown == 0) {
		
		*countdown = ERR;
		
		for (i = 0; i < GHOSTS_NUMBER; i++) {
			
			/* i fantasmi ancora vulnerabili ritorno allo stato di non vulnerabilità */
			if (ghost[i].name != _NULL) {
			
				modifySprite(&ghost[i].image, ghost[i].image.name, '-');
				drawSprite(&ghost[i].image);
			}
		}
	}
}

void newGhost (newGhost_ARG) {
	
#ifdef THREADS
	
	pthread_create(thread, NULL, &ghostNewDirection, ghostName);
	
	pthread_detach(*thread);
	
#endif
	
#ifdef PROCESSES
	
	*process = fork();
	
	if (*process == 0) {
		
		close(buffer[0]);
		ghostNewDirection(*ghostName, buffer[1]);
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
        
		ghostNewDirection(*ghostName);
	}
	
	else if (*process == ERR) {
		
		endwin();
		printf("fork() failed.\n");
		exit(1);
	}
    
#endif
	
}

void ghostWaiting (ghostWaiting_ARG) {

	int i;
	
	/* i fantasmi si nascondono dietro le pillole (no power pill), aspettano che Pac-Man mangi la pillola sotto la quale si trovano per iniziare a muoversi (dopo un ritardo) */
	for (i = 0; i < (GHOSTS_NUMBER / 2); i++) {
		
		if (ghost[i].name == _NULL &&
			labyrinth[(ghost[i].image.position.y - LABYRINTH_Y)][ghost[i].image.position.x + 1].element == EMPTY) {
			
			newGhost(newGhost_VALUE_ghost(i));
		}
	}
}

void duplicateGhosts (duplicateGhosts_ARG) {

	int i, k = 0;

	/* controlla che tutti i fantasmi siano morti almeno 1 volta */
	for (i = 0; i < (GHOSTS_NUMBER / 2); i++) {
		
		if (ghostHits[i] > 0) {
			
			k++;
		}
	}
	
	/* nel caso i fantasmi siano morti almeno 1 volta duplica i fantasmi in gioco */
	if (k == (GHOSTS_NUMBER / 2)) {
		
		for (i = (GHOSTS_NUMBER / 2); i < GHOSTS_NUMBER; i++) {
			
			if (ghost[i].name == _NULL) {
				
				drawSprite(&ghost[i].image);
				newGhost(newGhost_VALUE_ghost(i));
			}
		}
	}
}

void ghostHideUnderPill (Sprite ghost[GHOSTS_NUMBER], Layer labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS]) {

	int i;
	
	for (i = 0; i < (GHOSTS_NUMBER / 2); i++) {
		
		do {
			
			ghost[i].image.position.x = rand()%LABYRINTH_COLS;
			ghost[i].image.position.y = rand()%(LABYRINTH_ROWS + LABYRINTH_Y);
			
		} while (labyrinth[ghost[i].image.position.y - LABYRINTH_Y][ghost[i].image.position.x].element != PILL);
		
		ghost[i].name = _NULL;		
		ghost[i].image.position.x--;
	}
}

void resetGhostHits (unsigned int ghostHits[(GHOSTS_NUMBER / 2)]) {

	int i;
	
	for (i = 0; i < (GHOSTS_NUMBER / 2); i++) {
		
		ghostHits[i] = 0;
	}
}

void drawIngameGhosts (Sprite ghost[GHOSTS_NUMBER]) {

    int i;
    
    for (i = 0; i < (GHOSTS_NUMBER / 2); i++) {
        
        drawSprite(&ghost[i].image);
    }
}
