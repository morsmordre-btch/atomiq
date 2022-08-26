#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <list>
#include <queue>
#include <string>

#include <cassert>

#include <thread>
#include <mutex>
#include <atomic>

enum class Colors : int
{
	Red = 0,
	Green,
	Blue
};

class Color
{
public:
	Color(Colors colorValue);

	Colors getColor();

	friend	std::ostream &operator<<(std::ostream &out, Color &colo);

private:
	Colors _value;

};

#endif // COLOR_H
