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

/* Variables and functions */
 int RANDOM_ALLOW_RDRAND ; 
 int RANDOM_EXTEND_WITH_PSEUDO ; 
 int RANDOM_MAY_FAIL ; 
 scalar_t__ genuine_random_bytes (void*,size_t,int) ; 
 int /*<<< orphan*/  pseudo_random_bytes (void*,size_t) ; 

void random_bytes(void *p, size_t n) {

        /* This returns high quality randomness if we can get it cheaply. If we can't because for some reason
         * it is not available we'll try some crappy fallbacks.
         *
         * What this function will do:
         *
         *         • This function will preferably use the CPU's RDRAND operation, if it is available, in
         *           order to return "mid-quality" random values cheaply.
         *
         *         • Use getrandom() with GRND_NONBLOCK, to return high-quality random values if they are
         *           cheaply available.
         *
         *         • This function will return pseudo-random data, generated via libc rand() if nothing
         *           better is available.
         *
         *         • This function will work fine in early boot
         *
         *         • This function will always succeed
         *
         * What this function won't do:
         *
         *         • This function will never fail: it will give you randomness no matter what. It might not
         *           be high quality, but it will return some, possibly generated via libc's rand() call.
         *
         *         • This function will never block: if the only way to get good randomness is a blocking,
         *           synchronous getrandom() we'll instead provide you with pseudo-random data.
         *
         * This function is hence great for things like seeding hash tables, generating random numeric UNIX
         * user IDs (that are checked for collisions before use) and such.
         *
         * This function is hence not useful for generating UUIDs or cryptographic key material.
         */

        if (genuine_random_bytes(p, n, RANDOM_EXTEND_WITH_PSEUDO|RANDOM_MAY_FAIL|RANDOM_ALLOW_RDRAND) >= 0)
                return;

        /* If for some reason some user made /dev/urandom unavailable to us, or the kernel has no entropy, use a PRNG instead. */
        pseudo_random_bytes(p, n);
}