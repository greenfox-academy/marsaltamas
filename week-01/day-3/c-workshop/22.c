#include <stdio.h>
#include <stdint.h>

int main() {

	uint8_t ac = 7;
	uint8_t time = 2;
	uint8_t out;

	if (time > 200)
        out = 0b010;
    else if (!(ac%4))
        out = 0b100;
    else
        out = 0b001;

    printf("%d", out);

	// if ac is dividable by 4
	// and time is not more than 200
	// set out to 0b100

	// if time is more than 200
	// set out to 0b010

	// otherwise set out to 0b001
	return 0;
}
