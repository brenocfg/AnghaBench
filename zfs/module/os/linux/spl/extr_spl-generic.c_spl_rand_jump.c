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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  JUMP ;

/* Variables and functions */
 int /*<<< orphan*/  spl_rand_next (int*) ; 

__attribute__((used)) static inline void
spl_rand_jump(uint64_t *s)
{
	static const uint64_t JUMP[] =
	    { 0x8a5cd789635d2dff, 0x121fd2155c472f96 };

	uint64_t s0 = 0;
	uint64_t s1 = 0;
	int i, b;
	for (i = 0; i < sizeof (JUMP) / sizeof (*JUMP); i++)
		for (b = 0; b < 64; b++) {
			if (JUMP[i] & 1ULL << b) {
				s0 ^= s[0];
				s1 ^= s[1];
			}
			(void) spl_rand_next(s);
		}

	s[0] = s0;
	s[1] = s1;
}