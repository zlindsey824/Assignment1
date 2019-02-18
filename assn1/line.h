#ifndef LINE_H
#define LINE_H

typedef struct{
	int x;
	int y;
} Point;


class Line{
public:
	Line(): points(new Point[2]), numPoints(0), maxPoints(2) {}

	~Line(){ delete[] points; }

	void addPoint(int x, int y);
	Point getPoint(int index);
	int getNumPoints();
	bool haveAllPoints();
  void clearPoints();

	int getXdiff();
	int getYdiff();
	float getSlope();
  float getInvSlope();
private:
	Point* points;
	int numPoints;
	int maxPoints;
};
#endif
