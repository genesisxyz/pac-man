/*
 *  Buffer.h
 *  Pac-Man Remake
 *
 *  Created by Damiano Collu on 25/06/11.
 *  Copyright 2011 Università Cagliari Informatica. All rights reserved.
 *
 */

#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdbool.h>
#include <ncurses.h>
#include <unistd.h>
#include <sys/shm.h> 
#include <sys/stat.h>
#include <sys/sem.h>

#include "types.h"

#ifdef THREADS

struct bufferElement* buffer;

struct bufferElement* last;

pthread_mutex_t IOBuffer;

#elif defined PROCESSES

#define bufferRead_ARG struct bufferElement* element, int pipeRead
#define bufferRead_VALUES &element, buffer[0]

#define bufferWrite_ARG unsigned int name, union N n, int buffer_write
#define bufferWrite_VALUES name, n, buffer_write

#endif

#ifdef SYSTEM_V

int id;

int buffer;
int last;

#endif

#if defined THREADS || defined SYSTEM_V

#define bufferWrite_ARG unsigned int name, union N n
#define bufferWrite_VALUES name, n

#define bufferRead_ARG struct bufferElement* element
#define	bufferRead_VALUES &element

#endif

/*
 Il buffer è di tipo FIFO.
*/

/* scrive un elemento nel buffer */
void bufferWrite (bufferWrite_ARG);

/* legge il primo elemento dal buffer */
bool bufferRead (bufferRead_ARG);
