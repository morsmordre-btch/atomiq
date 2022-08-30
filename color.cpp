#include "color.h"

const std::array<const std::string, 3> Color::_colorLookUp = {"RED",
															  "GREEN",
															  "BLUE"};

Color::Color(Colors colorValue)
{
	if (colorValue >= Colors::Red && colorValue <= Colors::Blue)
		_value = colorValue;
	else
		_value = Colors::Red;
}

Colors Color::getColor() const
{
	return _value;
}

std::ostream &operator<<(std::ostream &out, Color &colo)
{
	out << colo._colorLookUp[static_cast<int>(colo._value)];
	return out;
}


