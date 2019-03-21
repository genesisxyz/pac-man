/*
 *  Buffer.c
 *  Pac-Man Remake
 *
 *  Created by Damiano Collu on 25/06/11.
 *  Copyright 2011 Università Cagliari Informatica. All rights reserved.
 *
 */

#include "Buffer.h"

void bufferWrite (bufferWrite_ARG) {
	
#ifdef THREADS
	
	struct bufferElement* temp;
	
	/* viene allocato l'elemento da inserire nel buffer */
	temp = malloc(sizeof(struct bufferElement));
    
	if (temp != NULL) {
		
		/* i dati vengono scritti nell'elemento */
		temp->name = name;
		temp->n =  n;
		temp->next = NULL;
		
		pthread_mutex_lock(&IOBuffer);
		
		/* viene inserito l'elemento */
		
		if (last != NULL) {
			
			last->next = temp;
			last = temp;
		}
		
		else {
			
			buffer = temp;
			last = temp;
		}
		
		pthread_mutex_unlock(&IOBuffer);
	}
	
#elif defined PROCESSES
	
	struct bufferElement temp;
	
	/* i dati vengono scritti nell'elemento */
	temp.name = name;
	temp.n = n;
	
	/* l'elemento viene inserito nella pipe */
	write(buffer_write, &temp, sizeof(struct bufferElement));	
	
#elif defined SYSTEM_V
    
    struct sembuf incr = {0, 1, 0};
    
    struct sembuf decr = {0, -1, 0};
    
    int segment_id;
    
    semop(id, &decr, 1);
    
    segment_id = shmget (IPC_PRIVATE, sizeof(struct bufferElement), IPC_CREAT | IPC_EXCL);
    
    struct bufferElement *shared_memory = (struct bufferElement *) shmat (segment_id, NULL, 0);
    
    struct bufferElement *shared_memory2;
    
    if (shared_memory != NULL) {
		
		/* i dati vengono scritti nell'elemento */
		shared_memory->name = name;
		shared_memory->n =  n;
		shared_memory->next = ERR;
		
		//pthread_mutex_lock(&IOBuffer);
		
		/* viene inserito l'elemento */
		if (last != ERR) {
			
            shared_memory2 = (struct bufferElement *) shmat (last, NULL, 0);
            
			shared_memory2->next = segment_id;
            *shared_memory2 = *shared_memory;
            
            shmdt (shared_memory2);
		}
		
		else {
			
            shared_memory2 = (struct bufferElement *) shmat (buffer, NULL, 0);
            
			*shared_memory2 = *shared_memory;
            
            shmdt (shared_memory2);
            
            shared_memory2 = (struct bufferElement *) shmat (last, NULL, 0);
            
			*shared_memory2 = *shared_memory;
            
            shmdt (shared_memory2);
		}
		
		//pthread_mutex_unlock(&IOBuffer);
	}
    
    shmdt (shared_memory);
    
    semop(id, &incr, 1);
    
#endif
	
}

bool bufferRead (bufferRead_ARG) {
	
#ifdef THREADS
	
	struct bufferElement* nextBufferElement;
	
	pthread_mutex_lock(&IOBuffer);
	
	/* controlla che il buffer non sia vuoto */
	if (buffer != NULL) {
		
		
		/* prende il primo elemento dal buffer */
		*element = *buffer;
		
		/* salva l'elemento successivo temporaneamente */
		nextBufferElement = buffer->next;
		
		/* distrugge il primo elemento del buffer dalla memoria */
		free(buffer);
		
		/* l'elemento salvato prima viene inserito come primo elemento */
		buffer = nextBufferElement;
		
		pthread_mutex_unlock(&IOBuffer);
		
		return TRUE;
	}
	
	else {
		
		/* se il buffer è vuoto l'ultimo elemento non esiste */
		last = NULL;
		
		pthread_mutex_unlock(&IOBuffer);
		
		return FALSE;
	}
	
#elif defined PROCESSES
	
	/* legge l'elemento dalla pipe */
	if (read(pipeRead, element, sizeof(struct bufferElement)) != ERR) {
		
		return TRUE;
	}
	
	else {
		
		return FALSE;
	}	
	
#endif
    
#ifdef SYSTEM_V
    
    struct sembuf incr = {0, 1, 0};
    
    struct sembuf decr = {0, -1, 0};
    
    int nextBufferElement;
    
    semop(id, &decr, 1);
    
    struct bufferElement *shared_memory = (struct bufferElement *) shmat (buffer, NULL, 0);
    
    if (shared_memory != NULL) {
        
        *element = *shared_memory;
        
        /* salva l'elemento successivo temporaneamente */
		nextBufferElement = shared_memory->next;
        
        /* distrugge il primo elemento del buffer dalla memoria */
        shmctl (buffer, IPC_RMID, 0);
        
        /* l'elemento salvato prima viene inserito come primo elemento */
		shared_memory =  (struct bufferElement *) shmat (nextBufferElement, NULL, 0);
        
        shmdt (shared_memory);
        
        semop(id, &incr, 1);
        
        return TRUE;
    }
    
    else {
		
		/* se il buffer è vuoto l'ultimo elemento non esiste */
		shared_memory = (struct bufferElement *) shmat (last, NULL, 0);;
		
        shared_memory = NULL;
        
        shmdt (shared_memory);
        
        semop(id, &incr, 1);
        
		return FALSE;
	}
    
#endif
	
}
