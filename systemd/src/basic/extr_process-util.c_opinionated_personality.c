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
 int /*<<< orphan*/  PERSONALITY_INVALID ; 
 unsigned long PER_LINUX ; 
 unsigned long PER_LINUX32 ; 
 int safe_personality (int /*<<< orphan*/ ) ; 

int opinionated_personality(unsigned long *ret) {
        int current;

        /* Returns the current personality, or PERSONALITY_INVALID if we can't determine it. This function is a bit
         * opinionated though, and ignores all the finer-grained bits and exotic personalities, only distinguishing the
         * two most relevant personalities: PER_LINUX and PER_LINUX32. */

        current = safe_personality(PERSONALITY_INVALID);
        if (current < 0)
                return current;

        if (((unsigned long) current & 0xffff) == PER_LINUX32)
                *ret = PER_LINUX32;
        else
                *ret = PER_LINUX;

        return 0;
}