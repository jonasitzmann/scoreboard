#include "Color.h"
Color::Color(ColorType type)
{
	Color c(0, 0, 0);
	switch (type) {
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
	default: {
		c = Color(0, 0, 0);
	}
	}
	c.type = type;
	r = c.r;
	g = c.g;
	b = c.b;
}

void Color::changeToNext()
{
	//find next type
	type =  (Color::ColorType)(((int)type + 1) % (int)Color::NUM_COLORS);
	//make color from next type
	Color newColor(type);
	// copy attributes to this
	r = newColor.r;
	g = newColor.g;
	b = newColor.b;
}

String Color::toString()
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
