#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include "curve.h"

void Curve::addPoint(int x, int y){
	if (numPoints < maxPoints){
		Point newPoint = {x,y};
		points[numPoints] = newPoint;
		numPoints++;
	}
}

Point Curve::getPoint(float u) {
  float uX = 0;
  float uY = 0;
  float n = maxPoints-1;
  for(float i = 0; i < maxPoints; i++){
    int C = calculateCi(i);
    float uI = pow(u,i);
    float uNI = pow(1-u, n-i);
    uX += points[(int)i].x * C * uI * uNI;
    uY += points[(int)i].y * C * uI * uNI;
  }
  int X = round(uX);
  int Y = round(uY);
  Point calcPoint = {X,Y};
  return calcPoint;

}

int Curve::getNumPoints(){
	return numPoints;
}

bool Curve::haveAllPoints(){return numPoints == maxPoints;}

void Curve::clearPoints(){
  delete[] points;
  points = new Point[maxPoints];
  numPoints = 0;
}

int Curve::factorial(int n){
  if (n == 0 || n == 1)
    return 1;

  return n * factorial(n-1);
}

int Curve::calculateCi(int i){
  int n = maxPoints - 1;
  int top = factorial(n);
  int bottom = factorial(i) * factorial(n-i);
  return top/bottom;
}
