#include "main.h"

int main() {
	
	char labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS] = {
		
		{" [--------------------------------------------------------] "},
		{" |+[------------------------]++[------------------------]+| "},
		{" |+| . . . . . . . . . . . .|++| . . . . . . . . . . . .|+| "},
		{" |+| .[------] .[--------] .|++| .[--------] .[------] .|+| "},
		{" |+| 0|++++++| .|++++++++| .|++| .|++++++++| .|++++++| 0|+| "},
		{" |+| .(------) .(--------) .(--) .(--------) .(------) .|+| "},
		{" |+| . . . . . . . . . . . . . . . . . . . . . . . . . .|+| "},
		{" |+| .[------] .[--] .[--------------] .[--] .[------] .|+| "},
		{" |+| .(------) .|++| .(-----]++[-----) .|++| .(------) .|+| "},
		{" |+| . . . . . .|++| . . . .|++| . . . .|++| . . . . . .|+| "},
		{" |+(---------] .|++(-----]  |++|  [-----)++| .[---------)+| "},
		{" (---------]+| .|++[-----)  (--)  (-----]++| .|+[---------) "},
		{" ++++++++++|+| .|++|                    |++| .|+|++++++++++ "},
		{"-----------)+| .|++|  [----]____[----]  |++| .|+(-----------"},
		{"-------------) .(--)  |+[--)G1G2(--]+|  (--) .(-------------"},
		{"               .      I+I   G3G4   I+I       .              "},
		{"-------------] .[--]  |+(--]____[--)+|  [--] .[-------------"},
		{"-----------]+| .|++|  (----)    (----)  |++| .|+[-----------"},
		{" ++++++++++|+| .|++|                    |++| .|+|++++++++++ "},
		{" [---------)+| .|++|  [--------------]  |++| .|+(---------] "},
		{" |+[---------) .(--)  (-----]++[-----)  (--) .(---------]+| "},
		{" |+| . . . . . . . . . . . .|++| . . . . . . . . . . . .|+| "},
		{" |+| .[------] .[--------] .|++| .[--------] .[------] .|+| "},
		{" |+| .(---]++| .(--------) .(--) .(--------) .|++[---) .|+| "},
		{" |+| 0 . .|++| . . . . . . .P    . . . . . . .|++| . . 0|+| "},
		{" | (---] .|++| .[--] .[--------------] .[--] .|++| .[---) | "},
		{" | [---) .(--) .|++| .(-----]++[-----) .|++| .(--) .(---] | "},
		{" |+| . . . . . .|++| . . . .|++| . . . .|++| . . . . . .|+| "},
		{" |+| .[---------)++(-----] .|++| .[-----)++(---------] .|+| "},
		{" |+| .(------------------) .(--) .(------------------) .|+| "},
		{" |+| . . . . . . . . . . . . . . . . . . . . . . . . . .|+| "},
		{" |+(----------------------------------------------------)+| "},
		{" (--------------------------------------------------------) "},
		
	};
	
	Layer tempLabyrinth[LABYRINTH_ROWS][LABYRINTH_COLS];
	Pills pills;
	
	/* PAC-MAN */
	Sprite pacman;
	/* tiene l'ultimo tasto di movimento premuto (in base al tasto premuto viene salvata la prossima direzione da fare) */
	Point pacmanNextMove;
	/* usata per segnare se Pac-Man è stato colpito da un fantasma e viceversa */
	unsigned int hit;
	/* usata per muovere (eventualmente) pacman ogni tot microsecondi */
	unsigned int pacmanSchedule;
	Lifes lifes;
	Points points = { 0, 0 };
	unsigned int highscore = 0;
	
	/* FANTASMI */
	Sprite ghost[GHOSTS_NUMBER];
	
	/* usata per contare quante volte un fantasma è morto (solo per la prima metà dei fantasmi) */
	unsigned int ghostHits[(GHOSTS_NUMBER / 2)];
	
	/* usata per far lampeggiare l'indicatore del giocatore corrente ogni tot microsecondi */
	unsigned int player1LabelSchedule;
	/* usata per far lampeggiare i fantasmi quando sono vulnerabili ogni tot microsecondi */
	unsigned int ghostsBlinkingSchedule;
	/* usata per rendere vulnerabili i fantasmi per un certo tempo (microsecondi) */
	int ghostsTransformCountdown;
	
	/* inizializzazione buffer */
	
	struct bufferElement element;
	
#ifdef THREADS

	buffer = NULL;
	last = NULL;
	
	pthread_mutex_init (&IOBuffer, NULL);
	
#elif defined PROCESSES
	
	int buffer[2];
	
	if(pipe(buffer) == ERR) {
		perror(PIPE_ERR);
		exit(1);
	}
	
	/* il programma è scritto in modo tale che si esegua un certe tot di volte al secondo (FAKE_FAKE_FPS), questi file descriptors non devono bloccare il processo che li usa */
	fcntl(buffer[0], F_SETFL, O_NONBLOCK);
	fcntl(buffer[1], F_SETFL, O_NONBLOCK);
	
#endif
    
#ifdef SYSTEM_V
    
    id = semget(IPC_PRIVATE, 1, IPC_CREAT|IPC_EXCL|0666);
		/* https://stackoverflow.com/a/37577959/232194 */
		union semun {
    	int val;
    	struct semid_ds *buf;
    	unsigned short  *array;
		} init;
    // union semun init;
    init.val = 1;
    semctl(id, 0, SETVAL, init);
    
    buffer = shmget (IPC_PRIVATE, sizeof(struct bufferElement), IPC_CREAT | IPC_EXCL);
    last = shmget (IPC_PRIVATE, sizeof(struct bufferElement), IPC_CREAT | IPC_EXCL);
    
#endif
    
    /* sarebbe meglio un #define */
    system("resize -s 36 60");
    
	initscr();
	resize_term(WINDOW_SIZE_Y + 1, WINDOW_SIZE_X);
	curs_set(0);
	start_color();
	keypad(stdscr, TRUE);
	cbreak();
	noecho();
	
	srand((unsigned)time(NULL));
	
	initColors();
	
	pressStartButton(&highscore, &points.value);
	
	initLabyrinth(labyrinth, tempLabyrinth, &pacman, ghost, &pills);
	
	while (1) {
		
		/* registra l'ultima direzione premuta e la esegue appena possibile (più giocabile) */
		pacmanNextMove = pacman.image.lastMove;
		
		/* perse tutte le vite, i punti tornano a 0 */
		points.value = 0;
		
		/* vite iniziali */
		lifes.value = 3;
		/* Pac-Man non è stato colpito */
		hit = FALSE;
        
        drawAllInitialPacmanLifes(&pacman, &lifes.value);
        
        refresh();
        
        ready();
        
		/* finchè ci sono vite disponibili */
		while (lifes.value > 0) {
            
            remainingLives(&pacman, &lifes.value);
            
            refresh();
			
			lifes.life = 10;
			
			pacmanNextMove = pacman.image.lastMove;
			
			newPacmanController(newPacmanController_VALUES);
			
			pacmanSchedule = 0;
			player1LabelSchedule = 0;
			/* il valore ERR blocca la funzione che userà questa variabile */
			ghostsTransformCountdown = ERR;
            
			resetGhostHits(ghostHits);
            
			/* il livello continua finche Pac-Man non ha mangiato tutte le pillole o se non viene colpito */
			while (pills.value > 0 && !(hit == YES) && lifes.life > 0) {
				
				player1LabelBlinking(&player1LabelSchedule);
				/* queste funzioni aspettano un particolare evento per eseguirsi, la maggior parte delle volte vengono richiamate inutilmente */
				checkGhostsTransform(&ghostsTransformCountdown, ghost, &ghostsBlinkingSchedule);
				ghostWaiting(ghostWaiting_VALUES);
				
				if (pacmanSchedule >= PACMAN_SCHEDULE) {
					
					/* 
					 Se viene premuta una direzione e questa non è fattibile viene riprovata a ogni "frame" (FAKE_FPS).
					 In questo modo si ha un movimento più naturale (lo spostamento di Pac-Man a ogni passo ha una lunghezza di un carattere,
					 viene difficile altrimenti beccare la coincidenza in cui Pac-Man arriva ad un bivio e vogliamo cambiare direzione.
					*/
					
					if (canMove (&pacman.image.position, &pacmanNextMove, tempLabyrinth)) {
						
						pacman.image.lastMove = pacmanNextMove;
					}
					
					if (canMove (&pacman.image.position, &pacman.image.lastMove, tempLabyrinth)) {
						
						eraseSprite(pacman.image.position, tempLabyrinth);
						
						setSpritePositionFromLastMove(&pacman);
						
						hit = ghostHitPacman(tempLabyrinth, &pacman.image.position, &pacman, ghost, ghostHits);
						
						if (hit == MISSILE) {
							
							lifes.life--;
							
							pacmanSchedule = 0;
						}
						
						else if (!(hit == YES)) {
							
							if (scoreUpdate(&pills.value, &points, &highscore, tempLabyrinth, &pacman.image.position, &hit) == POWER_PILL) {
								
								/* moltiplicatore usato per aggiornare il punteggio nel caso Pac-Man mangi un fantasma (dopo il primo fantasma il punteggio si moltiplica per il numero dei fantasmi mangiati) */
								points.multiplier = 1;
								
								ghostsTransform (&ghostsTransformCountdown, ghost, &ghostsBlinkingSchedule);
							}
							
							pacmanSchedule = 0;
						}
						
						drawSpriteInLabyrinth(&pacman.image, tempLabyrinth);
					}
					
					else {
						
						pacmanSchedule = 0;
					}
				}
				
				else {
					
					pacmanSchedule += REFRESH;

					if ((bufferRead(bufferRead_VALUES)) != FALSE) {
						
						if (element.name == PACMAN) {
							
							if (element.n.value == MISSILE) {
								
#ifdef THREADS
								
								prepareMissile(&pacman, tempLabyrinth);
								
#endif
								
#ifdef PROCESSES
								
								prepareMissile(&pacman, tempLabyrinth, buffer);
								
#endif
							}
							
							/* se l'elemento preso dal buffer non è un missile è sicuramente una nuova direzione */
							else {
								
								setNewPacmanPositionFromBuffer(&pacmanNextMove, &element);
							}
						}
						
						/* l'elemento preso dla buffer riguarda un fantasma */
						else if (element.name < MISSILE) {
							
							if (element.n.value == MISSILE) {
								
								/* se ha deciso di lanciare un missile lo può fare solo nel caso non sia nello stato di vulnerabilità */
								if (ghost[(element.name - PACMAN - 1)].image.colorPair > PACMAN) {
									
#ifdef THREADS
									
									prepareMissile(&ghost[(element.name - PACMAN - 1)], tempLabyrinth);
									
#endif
									
#ifdef PROCESSES
									
									prepareMissile(&ghost[(element.name - PACMAN - 1)], tempLabyrinth, buffer);
									
#endif
								}
							}
							
							else {
								
								setNewGhostPosition(ghost, tempLabyrinth, &element);
								
								hit = ghostHitPacman(tempLabyrinth, &ghost[(element.name - PACMAN - 1)].image.position, &pacman, ghost, ghostHits);
								
								if (hit == MISSILE) {
								
									lifes.life--;
								}
								
								else if (!(hit == YES)) {
								
									drawSpriteInLabyrinth(&pacman.image, tempLabyrinth);
								}
							}
						}
						
						else {
							
							hit = missileMove(&element.name, &pacman, ghost, ghostHits, tempLabyrinth);
							
							if (hit == MISSILE) {
								
								lifes.life--;
							}
						}
					}
				}
				
				duplicateGhosts(duplicateGhosts_VALUES);
				
				refresh();
					
				usleep(REFRESH);
			}
            
            attron(A_BOLD);
            attron(COLOR_PAIR(DEFAULT_COLOR));
            mvprintw(0, 0, "\t1UP");
            attroff(COLOR_PAIR(DEFAULT_COLOR));
            attroff(A_BOLD);

            refresh();
            
			killAllThreads(&pacman, ghost, tempLabyrinth);
			
			if (pills.value == 0) {
					
				/* pausa vittoria, prima dell'effeto lampeggio del labirinto */
				usleep(3000000);
				
				labyrinthBlinking(labyrinth, ghost);
					
				usleep(2000000);
				
				resetPillsInLabyrinth (labyrinth, tempLabyrinth, &pills);
				resetSpritesPositions(tempLabyrinth, &pacman, ghost);
                
				hit = NO;
                
				ghostHideUnderPill(ghost, tempLabyrinth);
				
                ready();
                
			}
			
			else {
				
				lifes.value--;
				
				if (lifes.value > 0) {
					
					usleep(5000000);
					
					resetSpritesPositions(tempLabyrinth, &pacman, ghost);
					drawIngameGhosts(ghost);
                    
					hit = FALSE;
					
					refresh();
					
					usleep(2500000);
					
					newGhost(newGhost_VALUE_ghost(0));
					newGhost(newGhost_VALUE_ghost(1));
					newGhost(newGhost_VALUE_ghost(2));
					newGhost(newGhost_VALUE_ghost(3));
				}
				
				else {
					
                    sleep(3);
                    
                    resetSpritesPositions(tempLabyrinth, &pacman, ghost);
                    
                    eraseSprite(pacman.image.position, tempLabyrinth);
                    
                    gameover();
                    
                    sleep(5);
                    
					clear();
					
					pressStartButton(&highscore, &points.value);
					
					resetLabyrinth (labyrinth, tempLabyrinth, &pills);
                    
					ghostHideUnderPill(ghost, tempLabyrinth);
				}
			}
		}
	}

	/* codice irraggiungibile, non c'è nessun tasto che permetta la chiusura del programma (oltre ctrl + c (hangup) o chiudendo direttamente il terminale)
	endwin();*/
	
	return 0;
}

void killAllThreads (Sprite *pacman, Sprite ghost[GHOSTS_NUMBER], Layer labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS]) {

	int i, j;
	
#ifdef THREADS
	
	pthread_cancel(pacman->name);
	
#elif defined PROCESSES
	
	kill(pacman->name, 1);
	
#endif
	
	pacman->name = _NULL;
	
	for (j = 0; j < 4; j++) {
		
		if (pacman->missile[j].name != _NULL) {
			
#ifdef THREADS
			
			pthread_cancel(pacman->missile[j].name);
			
#elif defined PROCESSES
			
			kill(pacman->missile[j].name, 1);
			
#endif
			
			pacman->missile[j].name = _NULL;
			
			labyrinth[pacman->missile[j].image.position.y - LABYRINTH_Y][pacman->missile[j].image.position.y].missile = NULL;
			eraseSprite(pacman->missile[j].image.position, labyrinth);
		}
	}
	
	for (i = 0; i < GHOSTS_NUMBER; i++) {
		
		if (ghost[i].name != _NULL) {
			
#ifdef THREADS
			
			pthread_cancel(ghost[i].name);
			
#elif defined PROCESSES
			
			kill(ghost[i].name, 1);
			
#endif
			
			ghost[i].name = _NULL;
			
			for (j = 0; j < 4; j++) {
				
				if (ghost[i].missile[j].name != _NULL) {
					
#ifdef THREADS
					
					pthread_cancel(ghost[i].missile[j].name);
					
#elif PROCESSES
					
					kill(ghost[i].missile[j].name, 1);
					
#endif
					
					ghost[i].missile[j].name = _NULL;
					
					labyrinth[ghost[i].missile[j].image.position.y - LABYRINTH_Y][ghost[i].missile[j].image.position.y].missile = NULL;
					eraseSprite(ghost[i].missile[j].image.position, labyrinth);
				}
			}
		}
	}	
}
