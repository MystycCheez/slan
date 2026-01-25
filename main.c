// Slope to angle & vice versa
//
// Used the following algorithm by John D. Cook
// https://www.johndcook.com/blog/2010/10/20/best-rational-approximation/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DENOMINATOR 16

typedef struct {
	int x;
	int y;
} Int2;

Int2 ansl(long double angle)
{
	Int2 slope = {0.0};
	
	long double decimal = tanl((M_PI / 180) * angle);

	Int2 lower = {0, 1};
	Int2 upper = {1, 1};
	
	while ((lower.y <= DENOMINATOR) && (upper.y <= DENOMINATOR)) {
		long double mediant = (long double)(lower.x + upper.x) / (long double)(lower.y + upper.y);
		if (decimal == mediant) {
			if ((lower.y + upper.y) < DENOMINATOR) {
				slope.x = lower.x + upper.x;
				slope.y = lower.y + upper.y;
				return slope;
			} else if (upper.y > lower.y) {
				slope.x = upper.x;
				slope.y = upper.y;
				return slope;
			} else {
				slope.x = lower.x;
				slope.y	= lower.y;
				return slope;
			}
		} else if (decimal > mediant) {
			lower.x = lower.x + upper.x;
			lower.y = lower.y + upper.y;
		} else {
			upper.x = lower.x + upper.x;
			upper.y = lower.y + upper.y;
		}
	}

	if (lower.y > DENOMINATOR) {
		slope.x = upper.x;
		slope.y = upper.y;
	} else {
		slope.x = lower.x;
		slope.y = lower.y;
	}

	return slope;
}

long double slan(int y, int x)
{
	long double angle = atan2l(x, y);

	return angle * (180 / M_PI);
}

int main(int argc, char* argv[])
{
	if ((argc <= 1) || (argc > 3)) {
		printf("Usage: slan <args>\n");
		printf("Converts slope to angle or vice versa.\n\n");
		printf("1 argument:  angle to slope\n");
		printf("2 arguments: slope to angle\n");
		return 0;
	}

	if (argc == 2) {
		Int2 slope = ansl(strtof(argv[1], NULL));
		printf("%d/%d\n", (int)slope.y, (int)slope.x);
	} else {
		long double angle = slan(atoi(argv[1]), atoi(argv[2]));
		printf("%Lf\n", angle);
	}
	
	return 0;
}