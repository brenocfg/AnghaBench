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
hmac(uint32_t x[2], uint32_t y[2], uint32_t result[2]) {
	uint32_t w[16];
	uint32_t r[4];
	int i;
	for (i=0;i<16;i+=4) {
		w[i] = x[1];
		w[i+1] = x[0];
		w[i+2] = y[1];
		w[i+3] = y[0];
	}

	digest_md5(w,r);

	result[0] = r[2]^r[3];
	result[1] = r[0]^r[1];
}