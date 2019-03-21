/*
 *  Point.c
 *  Pac-Man Remake
 *
 *  Created by Damiano Collu on 13/07/11.
 *  Copyright 2011 Università Cagliari Informatica. All rights reserved.
 *
 */

#include "Point.h"

bool pointIntersectsRect (Point* point, Point* pointA, Point* pointB) {
	
	if (point->x >= pointA->x && point->x <= pointB->x && point->y >= pointA->y && point->y <= pointB->y) {
		
		return TRUE;
	}
	
	else {
		
		return FALSE;
	}
}
