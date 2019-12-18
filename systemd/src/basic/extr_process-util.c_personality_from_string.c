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
 unsigned long PERSONALITY_INVALID ; 
 unsigned long PER_LINUX ; 
 unsigned long PER_LINUX32 ; 
 int SECONDARY_ARCHITECTURE ; 
 int architecture_from_string (char const*) ; 
 int native_architecture () ; 

unsigned long personality_from_string(const char *p) {
        int architecture;

        if (!p)
                return PERSONALITY_INVALID;

        /* Parse a personality specifier. We use our own identifiers that indicate specific ABIs, rather than just
         * hints regarding the register size, since we want to keep things open for multiple locally supported ABIs for
         * the same register size. */

        architecture = architecture_from_string(p);
        if (architecture < 0)
                return PERSONALITY_INVALID;

        if (architecture == native_architecture())
                return PER_LINUX;
#ifdef SECONDARY_ARCHITECTURE
        if (architecture == SECONDARY_ARCHITECTURE)
                return PER_LINUX32;
#endif

        return PERSONALITY_INVALID;
}