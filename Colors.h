#ifndef COLORS.H
#define COLORS.H

/*
INTENSIVITY:   1	2	3	4	5	6	7	8	9	10	11	12	13	14	15	16
HEX:           0	1	2	3	5	7	A	F	16	1F	37	3F	5A	7F	B4	FF
DEC:           0	1	2	3	5	7	10	15	22	31	44	63	90	127	180	255

FORMULA: 2^(INTENSIVITY/2) - 0.5 -> cast to int, round down
*/

#define ROUND_OFFSET 0.5

#define RED_MASK 0xFF0000
#define GREEN_MASK 0x00FF00
#define BLUE_MASK 0x0000FF


#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define WHITE 0xFFFFFF

#define LIGHTRED 0x800000
#define LIGHTGREEN 0x008000
#define LIGHTBLUE 0x000080
#define PINK 0xFF0040

#define ORANGE 0xFF4020
#define CYAN 0x00FFFF
#define PURPLE 0xFF00FF
#define LIGHTPINK 0xFF0010

#define NIGHTBLUE 0x000010


byte red(long rgb) {
	return (RED_MASK & rgb) >> 16;
}
byte green(long rgb) {
	return (GREEN_MASK & rgb) >> 8;
}
byte blue(long rgb) {
	return BLUE_MASK & rgb;
}

unsigned int convertToIntensivity(byte color) {
	if (!color) return 1;
	return (log(color) / log(2)) * 2 + 0.5;
}

byte convertToColor(unsigned int intensivity) {
	return pow(2, intensivity / 2.0) - 0.5;
}

#endif
