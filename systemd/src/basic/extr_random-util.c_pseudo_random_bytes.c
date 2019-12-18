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
typedef  unsigned int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  RAND_STEP ; 
 int /*<<< orphan*/  initialize_srand () ; 
 scalar_t__ rand () ; 

void pseudo_random_bytes(void *p, size_t n) {
        uint8_t *q;

        /* This returns pseudo-random data using libc's rand() function. You probably never want to call this
         * directly, because why would you use this if you can get better stuff cheaply? Use random_bytes()
         * instead, see below: it will fall back to this function if there's nothing better to get, but only
         * then. */

        initialize_srand();

        for (q = p; q < (uint8_t*) p + n; q += RAND_STEP) {
                unsigned rr;

                rr = (unsigned) rand();

#if RAND_STEP >= 3
                if ((size_t) (q - (uint8_t*) p + 2) < n)
                        q[2] = rr >> 16;
#endif
#if RAND_STEP >= 2
                if ((size_t) (q - (uint8_t*) p + 1) < n)
                        q[1] = rr >> 8;
#endif
                q[0] = rr;
        }
}