#ifndef CURVE_H
#define CURVE_H

#include "line.h"

class Curve{
public:
	Curve(): points(new Point[4]), numPoints(0), maxPoints(4) {}

	~Curve(){ delete[] points; }

	void addPoint(int x, int y);
	Point getPoint(float u);
	int getNumPoints();
	bool haveAllPoints();
  void clearPoints();

private:
  int factorial(int n);
  int calculateCi(int i);
	Point* points;
	int numPoints;
	int maxPoints;
};
#endif
