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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ rlim_t ;

/* Variables and functions */
 int ERANGE ; 
 scalar_t__ PRIO_MAX ; 
 int PRIO_MIN ; 
 int safe_atou64 (char const*,scalar_t__*) ; 

__attribute__((used)) static int rlimit_parse_nice(const char *val, rlim_t *ret) {
        uint64_t rl;
        int r;

        /* So, Linux is weird. The range for RLIMIT_NICE is 40..1, mapping to the nice levels -20..19. However, the
         * RLIMIT_NICE limit defaults to 0 by the kernel, i.e. a value that maps to nice level 20, which of course is
         * bogus and does not exist. In order to permit parsing the RLIMIT_NICE of 0 here we hence implement a slight
         * asymmetry: when parsing as positive nice level we permit 0..19. When parsing as negative nice level, we
         * permit -20..0. But when parsing as raw resource limit value then we also allow the special value 0.
         *
         * Yeah, Linux is quality engineering sometimes... */

        if (val[0] == '+') {

                /* Prefixed with "+": Parse as positive user-friendly nice value */
                r = safe_atou64(val + 1, &rl);
                if (r < 0)
                        return r;

                if (rl >= PRIO_MAX)
                        return -ERANGE;

                rl = 20 - rl;

        } else if (val[0] == '-') {

                /* Prefixed with "-": Parse as negative user-friendly nice value */
                r = safe_atou64(val + 1, &rl);
                if (r < 0)
                        return r;

                if (rl > (uint64_t) (-PRIO_MIN))
                        return -ERANGE;

                rl = 20 + rl;
        } else {

                /* Not prefixed: parse as raw resource limit value */
                r = safe_atou64(val, &rl);
                if (r < 0)
                        return r;

                if (rl > (uint64_t) (20 - PRIO_MIN))
                        return -ERANGE;
        }

        *ret = (rlim_t) rl;
        return 0;
}