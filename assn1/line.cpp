#include <cstdlib>
#include "line.h"

void Line::addPoint(int x, int y){
	if (numPoints < 2){
		Point newPoint = {x,y};
		points[numPoints] = newPoint;
		numPoints++;
	}
}

Point Line::getPoint(int index) {return points[index];}

int Line::getNumPoints(){
	return numPoints;
}

bool Line::haveAllPoints(){return numPoints == maxPoints;}

int Line::getXdiff(){
	return points[1].x-points[0].x;
}

int Line::getYdiff(){
	return points[1].y-points[0].y;
}

float Line::getSlope(){
	return (float)getYdiff()/getXdiff();
}
