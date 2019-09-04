#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint8_t ;

/* Variables and functions */

__attribute__((used)) static int
pack_seg(const uint8_t *src, uint8_t * buffer, int sz, int n) {
	uint8_t header = 0;
	int notzero = 0;
	int i;
	uint8_t * obuffer = buffer;
	++buffer;
	--sz;
	if (sz < 0)
		obuffer = NULL;

	for (i=0;i<8;i++) {
		if (src[i] != 0) {
			notzero++;
			header |= 1<<i;
			if (sz > 0) {
				*buffer = src[i];
				++buffer;
				--sz;
			}
		}
	}
	if ((notzero == 7 || notzero == 6) && n > 0) {
		notzero = 8;
	}
	if (notzero == 8) {
		if (n > 0) {
			return 8;
		} else {
			return 10;
		}
	}
	if (obuffer) {
		*obuffer = header;
	}
	return notzero + 1;
}