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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  digest_md5 (int*,int*) ; 

__attribute__((used)) static void
hmac_md5(uint32_t x[2], uint32_t y[2], uint32_t result[2]) {
	uint32_t w[16];
	uint32_t r[4];
	int i;
	for (i=0;i<12;i+=4) {
		w[i] = x[0];
		w[i+1] = x[1];
		w[i+2] = y[0];
		w[i+3] = y[1];
	}

	w[12] = 0x80;
	w[13] = 0;
	w[14] = 384;
	w[15] = 0;

	digest_md5(w,r);

	result[0] = (r[0] + 0x67452301u) ^ (r[2] + 0x98badcfeu);
	result[1] = (r[1] + 0xefcdab89u) ^ (r[3] + 0x10325476u);
}