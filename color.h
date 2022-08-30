#ifndef COLOR_H
#define COLOR_H

#include <ostream>

#include <string>
#include <array>

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

	Colors getColor() const;

    friend std::ostream &operator<<(std::ostream &out, Color &colo);

private:
	Colors _value;

	static const std::array<const std::string, 3> _colorLookUp;

};

#endif // COLOR_H
