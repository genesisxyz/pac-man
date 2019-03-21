/*
 *  Point.h
 *  Pac-Man Remake
 *
 *  Created by Damiano Collu on 13/07/11.
 *  Copyright 2011 Università Cagliari Informatica. All rights reserved.
 *
 */

#include <stdbool.h>

#include "types.h"

/* controlla se il punto dato è dentro il rettangolo dato nel parametro */
bool pointIntersectsRect (Point* point, Point* pointA, Point* pointB);
