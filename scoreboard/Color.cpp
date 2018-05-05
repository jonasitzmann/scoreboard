#include "Color.h"
#include <string>
#include "stdlib_noniso.h"
Color::Color(ColorType type_)
{
	Color c(0, 0, 0);
	switch (type_) {
	case WHITE: {
		c = Color(255, 255, 255);
		break;
	}	case RED: {
		c = Color(255, 0, 0);
		break;
	}
	case ORANGE: {
		c = Color(255, 128, 0);
		break;
	}
	case YELLOW: {
		c = Color(255, 255, 0);
		break;
	}
	case GREEN: {
		c = Color(0, 255, 0);
		break;
	}
	case BLUE: {
		c = Color(0, 0, 255);
		break;
	}
	case PURPLE: {
		c = Color(127, 0, 255);
		break;
	}
	}
	type = type_;
	r = c.r;
	g = c.g;
	b = c.b;
}

bool Color::operator==(Color &other) const
{
	bool retval = true;
	retval &= (r == other.r);
	retval &= (g == other.g);
	retval &= (b == other.b);
	retval &= (type == other.type);
	return retval;
}

bool Color::operator!=(Color &other) const
{
	return !(*this == other);
}

void Color::changeToNext()
{
	int nextTypeNumber = static_cast<Color::ColorType>(type) + 1;
	nextTypeNumber %= Color::NUM_COLORS;
	Color newColor(static_cast<Color::ColorType>(nextTypeNumber));
	r = newColor.r;
	g = newColor.g;
	b = newColor.b;
	type = newColor.type;
}

string Color::toString() const
{
	char typeStr[10] = "";
	itoa(type, typeStr, 10);
	char rStr[10] = "";
	itoa(r, rStr, 10);
	char gStr[10] = "";
	itoa(g, gStr, 10);
	char bStr[10] = "";
	itoa(b, bStr, 10);
	string str;
	str += "color: {\t";
	str += "type: ";
	str += string(typeStr);
	str += "\tr:";
	str += string(rStr);
	str += "\tg:";
	str += string(gStr);
	str += "\tb:";
	str += string(bStr);
	str += "}";
	return str;
}
