#include"color.h"

color::color()
	:_r(0), _g(0), _b(0)
{

}

color::color(float n)
	: _r(n), _g(n), _b(n)
{

}

color::color(float r, float g, float b)
	: _r(r), _g(g), _b(b)
{

}

color::color(const color &c)
	: _r(c._r), _g(c._g), _b(c._b)
{

}

color color::operator+(const color &c) {
	return color(_r + c._r, _g + c._g, _b + c._b);
}
color& color::operator=(const color &c) {
	_r = c._r;
	_g = c._g;
	_b = c._b;
	return *this;
}
color color::operator*(float n) {
	return color(_r*n, _g*n, _b*n);
}