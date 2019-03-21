/*
 *  Missile.c
 *  Pac-Man Remake
 *
 *  Created by Damiano Collu on 11/07/11.
 *  Copyright 2011 Università Cagliari Informatica. All rights reserved.
 *
 */

#include "Missile.h"

void newMissile (newMissile_ARG) {
	
#ifdef THREADS
	
	pthread_create(thread, NULL, &missileShot, missileName);
	
	pthread_detach(*thread);
	
#endif
	
#ifdef PROCESSES
	
	*process = fork();
	
	if (*process == 0) {
		
		close(buffer[0]);
		/* questo processo si occuperà di scrivere sul buffer una nuova direzione per il missile */
		missileShot(*missileName, buffer[1]);
	}
	
	else if (*process == ERR) {
		
		endwin();
		printf("fork() failed.\n");
		exit(1);
	}
	
#endif
	
}

void* missileShot (missileShot_ARG) {
	
#ifdef THREADS
	
	struct bufferElement element;
	
	/* questo  potrebbe essere utile se vogliamo reperire dall'elemento preso dal buffer, il thread usato dal missile */
	element.n.id = pthread_self();
	
	element.name = *((unsigned int*)arg);
	
#endif
	
#ifdef PROCESSES
	
	union N n;
	
	/* questo  potrebbe essere utile se vogliamo reperire dall'elemento preso dal buffer, il processo usato dal missile */
	n.id = getpid();
	
#endif
	
	while (1) {
		
#ifdef THREADS
		
		bufferWrite(element.name, element.n);
		
#endif
		
#ifdef PROCESSES
		
		bufferWrite(name, n, buffer_write);
		
#endif
		
		usleep(100000);
	}
	
	return NULL;
	
}

void prepareMissile (prepareMissile_ARG) {
	
	/*
	 Ci sono 4 missili, ogni missile ha una direzione prestabilita (quando viene lanciato non cambia direzione, sa già dove andare).
	 Per ognuno viene fatto un controllo (È possibile lanciare il missile?), ogni oggetto nella sua traiettoria fa esplodere il missile.
	 Ogni missile per essere identificato nel buffer ha un numero univoco che è formato dal nome della Sprite che lo ha generato,
	 dal numero del missile lanciato (da 0 a 3, sono 4 missili) e da un numero predefinito (#define MISSILE).
	 Questo numero verrà scomposto per trovare quale missile è stato prelevato dal buffer e chi lo ha sparato (questo ovviamente non accade qui).
	*/
	
	Point direction = { 0, 1 };
	
	if (sprite->missile[0].name == _NULL && 
		labyrinth[sprite->image.position.y + direction.y - LABYRINTH_Y][sprite->image.position.x /*+ direction.x*/ + 1].element == EMPTY &&
		labyrinth[sprite->image.position.y + direction.y - LABYRINTH_Y][sprite->image.position.x /*+ direction.x*/ + 1].sprite == NULL) {
		
		sprite->missile[0].image.name = MISSILE + sprite->image.name + ((sprite->image.name - PACMAN - 1) * 4) + 0;
		
#ifdef THREADS
		
		newMissile (&sprite->missile[0].name, &sprite->missile[0].image.name);
		
#endif
		
#ifdef PROCESSES
		
		newMissile (&sprite->missile[0].name, &sprite->missile[0].image.name, buffer);
		
#endif
		
	}
	
	direction.y = -1;
	
	if (sprite->missile[1].name == _NULL &&
		labyrinth[sprite->image.position.y + direction.y - LABYRINTH_Y][sprite->image.position.x /*+ direction.x*/ + 1].element == EMPTY &&
		labyrinth[sprite->image.position.y + direction.y - LABYRINTH_Y][sprite->image.position.x /*+ direction.x*/ + 1].sprite == NULL) {
		
		sprite->missile[1].image.name = MISSILE + sprite->image.name + ((sprite->image.name - PACMAN - 1) * 4) + 1;
		
#ifdef THREADS
		
		newMissile (&sprite->missile[1].name, &sprite->missile[1].image.name);
		
#endif
		
#ifdef PROCESSES
		
		newMissile (&sprite->missile[1].name, &sprite->missile[1].image.name, buffer);
		
#endif
		
	}
	
	direction.x = 2;
	direction.y = 0;
	
	if (sprite->missile[2].name == _NULL &&
		labyrinth[sprite->image.position.y /*+ direction.y*/ - LABYRINTH_Y][sprite->image.position.x + direction.x + 1].element == EMPTY &&
		labyrinth[sprite->image.position.y /*+ direction.y*/ - LABYRINTH_Y][sprite->image.position.x + direction.x + 1].sprite == NULL) {
		
		sprite->missile[2].image.name = MISSILE + sprite->image.name + ((sprite->image.name - PACMAN - 1) * 4) + 2;
		
#ifdef THREADS
		
		newMissile (&sprite->missile[2].name, &sprite->missile[2].image.name);
		
#endif
		
#ifdef PROCESSES
		
		newMissile (&sprite->missile[2].name, &sprite->missile[2].image.name, buffer);
		
#endif
		
	}
	
	direction.x = -2;
	
	if (sprite->missile[3].name == _NULL &&
		labyrinth[sprite->image.position.y /*+ direction.y*/ - LABYRINTH_Y][sprite->image.position.x + direction.x + 1].element == EMPTY &&
		labyrinth[sprite->image.position.y /*+ direction.y*/ - LABYRINTH_Y][sprite->image.position.x + direction.x + 1].sprite == NULL) {
		
		sprite->missile[3].image.name = MISSILE + sprite->image.name + ((sprite->image.name - PACMAN - 1) * 4) + 3;
		
#ifdef THREADS
		
		newMissile (&sprite->missile[3].name, &sprite->missile[3].image.name);
		
#endif
		
#ifdef PROCESSES
		
		newMissile (&sprite->missile[3].name, &sprite->missile[3].image.name, buffer);
		
#endif
		
	}
}

unsigned int missileMove (unsigned int* missileName, Sprite *pacman, Sprite ghost[GHOSTS_NUMBER], unsigned int ghostHits[(GHOSTS_NUMBER / 2)], Layer labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS]) {

	Sprite* sprite;
	Missile* missile;
	
	unsigned int hit;
	
	int ghostNumber;
	unsigned int missileNumber;
	
	/*
	 calcolo per trovare quale è il missile da muovere e chi lo ha lanciato (formula inversa)
	*/
	missileNumber = ((4 * (PACMAN + 1)) + (*missileName - MISSILE));
	ghostNumber = (missileNumber/5);
	missileNumber = missileNumber - (ghostNumber * 5);
	ghostNumber -= (PACMAN + 1);
	
	if (ghostNumber < 0) {
		
		sprite = pacman;
	}
	
	else {
		
		sprite = &ghost[ghostNumber];
	}
	
	missile = &sprite->missile[missileNumber];
	
	/* il missile deve avere ancora il suo thread avviato senno' non avrebbe senso muoverlo (potrebbe essere già sparito dal gioco) */
	if (missile->name != _NULL) {
		
		if ((missile->image.position.x + missile->image.lastMove.x) >= 0 && (missile->image.position.x + missile->image.lastMove.x) < LABYRINTH_COLS &&
			labyrinth[missile->image.position.y + missile->image.lastMove.y - LABYRINTH_Y][missile->image.position.x + missile->image.lastMove.x + 1].element == EMPTY) {
			
			eraseSprite(missile->image.position, labyrinth);
			setSprite2x1PositionFromLastMove(&missile->image);
			
			labyrinth[missile->image.position.y - LABYRINTH_Y][missile->image.position.x].missile = missile;
			drawSprite(&missile->image);
			
            drawSprite(&sprite->image);
            
			hit = ghostHitPacman(labyrinth, &missile->image.position, pacman, ghost, ghostHits);
			
			if (hit == MISSILE && missile->name != _NULL) {
				
				killMissile(missile, sprite, labyrinth);
			}
			
			return hit;
		}
		
		else {
			
			killMissile(missile, sprite, labyrinth);
			
			return NO;
		}
	}
	
	else {
		
		return NO;
	}
}

void killMissile (Missile *missile, Sprite *sprite, Layer labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS]) {
	
#ifdef THREADS
	
	pthread_cancel(missile->name);
	
#endif
	
#ifdef PROCESSES
	
	kill(missile->name, 1);
	
#endif
	
	missile->name = _NULL;
	
	labyrinth[missile->image.position.y - LABYRINTH_Y][missile->image.position.x].missile = NULL;
	
	eraseSprite(missile->image.position, labyrinth);
	
	missile->image.position = sprite->image.position;
}
