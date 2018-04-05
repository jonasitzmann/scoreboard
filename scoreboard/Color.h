#ifndef COLOR
#define COLOR

#include <Arduino.h>
struct Color {
	enum ColorType {
		WHITE,
		RED,
		ORANGE,
		YELLOW,
		GREEN,
		BLUE,
		PURPLE,
		NUM_COLORS
	};
	Color(ColorType type = WHITE);
	Color(int r, int g, int b, ColorType type = WHITE) : r(r), g(g), b(b), type(type) {}
	void changeToNext();
	int r;
	int g;
	int b;
	ColorType type;
	int* toArray() {
		int arr[3] = { r, g, b };
		return arr;
	}
	String toString();
};
#endif // !COLOR