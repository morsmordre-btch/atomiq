#include "color.h"

Color::Color(Colors colorValue)
{
	if (colorValue >= Colors::Red && colorValue <= Colors::Blue)
	{
		_value = colorValue;
	}
	else
	{
		throw 1;
	}
}

Colors Color::getColor()
{
	return _value;
}

std::ostream &operator<<(std::ostream &out, Color &colo)
{
	switch (colo._value)
	{
		case Colors::Red :
			out << "RED";
		break;
		case Colors::Green :
			out << "GREEN";
		break;
		case Colors::Blue :
			out << "BLUE";
		break;
	}
	return out;
}
