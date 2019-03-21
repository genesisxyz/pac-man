/*
 *  math.c
 *  Pac-Man Remake
 *
 *  Created by Damiano Collu on 11/07/11.
 *  Copyright 2011 Università Cagliari Informatica. All rights reserved.
 *
 */

#include "math.h"

unsigned int digits (unsigned int number) {
	
	return ((unsigned int)log10((double)number) + 1);
}
