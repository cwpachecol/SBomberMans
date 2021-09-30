#ifndef COORDINATES_H
#define COORDINATES_H

class coordinates
{
	int x;
	int y;
public:
	coordinates(int x, int y) : x(x), y(y) {}
	~coordinates() {}

	int get_x() { return x; }
	int get_y() { return y; }

	void change_x_to(int value) { x = value; }
	void change_y_to(int value) { y = value; }

	void add_to_x(int val) { x = x + val; }
	void add_to_y(int val) { y = y + val; }
};

#endif