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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT_RANDOM ; 
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 void* ULONG_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getauxval (int /*<<< orphan*/ ) ; 
 scalar_t__ gettid () ; 
 scalar_t__ now (int /*<<< orphan*/ ) ; 
 scalar_t__ rdrand (unsigned long*) ; 
 scalar_t__ siphash24 (void const*,int,int const*) ; 
 int /*<<< orphan*/  srand (unsigned int) ; 

void initialize_srand(void) {
        static bool srand_called = false;
        unsigned x;
#if HAVE_SYS_AUXV_H
        const void *auxv;
#endif
        unsigned long k;

        if (srand_called)
                return;

#if HAVE_SYS_AUXV_H
        /* The kernel provides us with 16 bytes of entropy in auxv, so let's try to make use of that to seed
         * the pseudo-random generator. It's better than nothing... But let's first hash it to make it harder
         * to recover the original value by watching any pseudo-random bits we generate. After all the
         * AT_RANDOM data might be used by other stuff too (in particular: ASLR), and we probably shouldn't
         * leak the seed for that. */

        auxv = ULONG_TO_PTR(getauxval(AT_RANDOM));
        if (auxv) {
                static const uint8_t auxval_hash_key[16] = {
                        0x92, 0x6e, 0xfe, 0x1b, 0xcf, 0x00, 0x52, 0x9c, 0xcc, 0x42, 0xcf, 0xdc, 0x94, 0x1f, 0x81, 0x0f
                };

                x = (unsigned) siphash24(auxv, 16, auxval_hash_key);
        } else
#endif
                x = 0;

        x ^= (unsigned) now(CLOCK_REALTIME);
        x ^= (unsigned) gettid();

        if (rdrand(&k) >= 0)
                x ^= (unsigned) k;

        srand(x);
        srand_called = true;
}