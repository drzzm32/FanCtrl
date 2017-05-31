#include "util.h"

void main() {
	pwmInit();
	
	while (1) {
		P3 = 0xFF;
		posA = (FANC_A ? FAN_V : 0);
		posB = (FANC_B ? FAN_V : 0);
		posC = (FANC_C ? FAN_V : 0);
	}
}