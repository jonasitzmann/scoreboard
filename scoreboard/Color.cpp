#include "Color.h"
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
	memcpy(this, &newColor, sizeof(newColor));
}

String Color::toString() const
{
	String str;
	str += "color: {\t";
	str += "type: ";
	str += String(type);
	str += "\tr:";
	str += String(r);
	str += "\tg:";
	str += String(g);
	str += "\tb:";
	str += String(b);
	str += "}";
	return str;
}
