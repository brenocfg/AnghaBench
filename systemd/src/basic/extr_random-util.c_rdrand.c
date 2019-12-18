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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  success ;

/* Variables and functions */
 int EAGAIN ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EUCLEAN ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 unsigned long ULONG_MAX ; 
 scalar_t__ __get_cpuid (int,int*,int*,int*,int*) ; 
 int bit_RDRND ; 
 int log_debug_errno (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  msan_unpoison (int /*<<< orphan*/ *,int) ; 

int rdrand(unsigned long *ret) {

        /* So, you are a "security researcher", and you wonder why we bother with using raw RDRAND here,
         * instead of sticking to /dev/urandom or getrandom()?
         *
         * Here's why: early boot. On Linux, during early boot the random pool that backs /dev/urandom and
         * getrandom() is generally not initialized yet. It is very common that initialization of the random
         * pool takes a longer time (up to many minutes), in particular on embedded devices that have no
         * explicit hardware random generator, as well as in virtualized environments such as major cloud
         * installations that do not provide virtio-rng or a similar mechanism.
         *
         * In such an environment using getrandom() synchronously means we'd block the entire system boot-up
         * until the pool is initialized, i.e. *very* long. Using getrandom() asynchronously (GRND_NONBLOCK)
         * would mean acquiring randomness during early boot would simply fail. Using /dev/urandom would mean
         * generating many kmsg log messages about our use of it before the random pool is properly
         * initialized. Neither of these outcomes is desirable.
         *
         * Thus, for very specific purposes we use RDRAND instead of either of these three options. RDRAND
         * provides us quickly and relatively reliably with random values, without having to delay boot,
         * without triggering warning messages in kmsg.
         *
         * Note that we use RDRAND only under very specific circumstances, when the requirements on the
         * quality of the returned entropy permit it. Specifically, here are some cases where we *do* use
         * RDRAND:
         *
         *         • UUID generation: UUIDs are supposed to be universally unique but are not cryptographic
         *           key material. The quality and trust level of RDRAND should hence be OK: UUIDs should be
         *           generated in a way that is reliably unique, but they do not require ultimate trust into
         *           the entropy generator. systemd generates a number of UUIDs during early boot, including
         *           'invocation IDs' for every unit spawned that identify the specific invocation of the
         *           service globally, and a number of others. Other alternatives for generating these UUIDs
         *           have been considered, but don't really work: for example, hashing uuids from a local
         *           system identifier combined with a counter falls flat because during early boot disk
         *           storage is not yet available (think: initrd) and thus a system-specific ID cannot be
         *           stored or retrieved yet.
         *
         *         • Hash table seed generation: systemd uses many hash tables internally. Hash tables are
         *           generally assumed to have O(1) access complexity, but can deteriorate to prohibitive
         *           O(n) access complexity if an attacker manages to trigger a large number of hash
         *           collisions. Thus, systemd (as any software employing hash tables should) uses seeded
         *           hash functions for its hash tables, with a seed generated randomly. The hash tables
         *           systemd employs watch the fill level closely and reseed if necessary. This allows use of
         *           a low quality RNG initially, as long as it improves should a hash table be under attack:
         *           the attacker after all needs to to trigger many collisions to exploit it for the purpose
         *           of DoS, but if doing so improves the seed the attack surface is reduced as the attack
         *           takes place.
         *
         * Some cases where we do NOT use RDRAND are:
         *
         *         • Generation of cryptographic key material 🔑
         *
         *         • Generation of cryptographic salt values 🧂
         *
         * This function returns:
         *
         *         -EOPNOTSUPP → RDRAND is not available on this system 😔
         *         -EAGAIN     → The operation failed this time, but is likely to work if you try again a few
         *                       times ♻
         *         -EUCLEAN    → We got some random value, but it looked strange, so we refused using it.
         *                       This failure might or might not be temporary. 😕
         */

#if defined(__i386__) || defined(__x86_64__)
        static int have_rdrand = -1;
        unsigned long v;
        uint8_t success;

        if (have_rdrand < 0) {
                uint32_t eax, ebx, ecx, edx;

                /* Check if RDRAND is supported by the CPU */
                if (__get_cpuid(1, &eax, &ebx, &ecx, &edx) == 0) {
                        have_rdrand = false;
                        return -EOPNOTSUPP;
                }

/* Compat with old gcc where bit_RDRND didn't exist yet */
#ifndef bit_RDRND
#define bit_RDRND (1U << 30)
#endif

                have_rdrand = !!(ecx & bit_RDRND);
        }

        if (have_rdrand == 0)
                return -EOPNOTSUPP;

        asm volatile("rdrand %0;"
                     "setc %1"
                     : "=r" (v),
                       "=qm" (success));
        msan_unpoison(&success, sizeof(success));
        if (!success)
                return -EAGAIN;

        /* Apparently on some AMD CPUs RDRAND will sometimes (after a suspend/resume cycle?) report success
         * via the carry flag but nonetheless return the same fixed value -1 in all cases. This appears to be
         * a bad bug in the CPU or firmware. Let's deal with that and work-around this by explicitly checking
         * for this special value (and also 0, just to be sure) and filtering it out. This is a work-around
         * only however and something AMD really should fix properly. The Linux kernel should probably work
         * around this issue by turning off RDRAND altogether on those CPUs. See:
         * https://github.com/systemd/systemd/issues/11810 */
        if (v == 0 || v == ULONG_MAX)
                return log_debug_errno(SYNTHETIC_ERRNO(EUCLEAN),
                                       "RDRAND returned suspicious value %lx, assuming bad hardware RNG, not using value.", v);

        *ret = v;
        return 0;
#else
        return -EOPNOTSUPP;
#endif
}