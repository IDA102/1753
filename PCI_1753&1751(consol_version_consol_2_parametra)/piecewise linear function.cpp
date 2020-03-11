// Функция вывода на экран информации о пинах и портах
#include "include.h"

int  PiecewiseLinearFunction(int PortPin[2], int key)
{
	float q, w, e, r, t, y, u, i, o, p;
	float q1, w1, e1, r1, t1, y1, u1, i1, o1, p1;
	int PIN;
	int PORT;
	q = ((1 - k) / 2)*key;
	w = ((-k - 1) / 2)*abs(key - k);
	e = ((1 + k) / 2)*abs(key - (k + 1));
	r = ((-k - 1) / 2)*abs(key - (2 * k + 1));
	t = ((1 + k) / 2)*abs(key - (2 * k + 2));
	y = ((-k - 1) / 2)*abs(key - (3 * k + 2));
	u = ((1 + k) / 2)*abs(key - (3 * k + 3));
	i = ((-k - 1) / 2)*abs(key - (4 * k + 3));
	o = ((1 + k) / 2)*abs(key - (4 * k + 4));
	p = ((-k - 1) / 2)*abs(key - (5 * k + 1));
	PIN = q + w + e + r + t + y + u + i + o + p + 128;
	PortPin[0] = PIN;
	q1 = -0.5 * abs(key - (4 * k + 2));
	w1 = 0.5 * abs(key - (4 * k + 1));
	e1 = -0.5 * abs(key - (3 * k + 3));
	r1 = 0.5 * abs(key - (3 * k + 2));
	t1 = -0.5 * abs(key - (2 * k + 2));
	y1 = 0.5 * abs(key - (2 * k + 1));
	u1 = -0.5 * abs(key - (k + 1));
	i1 = 0.5 * abs(key - k);
	PORT = q1 + w1 + e1 + r1 + t1 + y1 + u1 + i1 + 2;
	PortPin[1] = PORT;
	return (PortPin[2]);
}