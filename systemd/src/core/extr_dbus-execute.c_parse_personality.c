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
 int EINVAL ; 
 unsigned long PERSONALITY_INVALID ; 
 int /*<<< orphan*/  assert (unsigned long*) ; 
 unsigned long personality_from_string (char const*) ; 

__attribute__((used)) static int parse_personality(const char *s, unsigned long *p) {
        unsigned long v;

        assert(p);

        v = personality_from_string(s);
        if (v == PERSONALITY_INVALID)
                return -EINVAL;

        *p = v;
        return 0;
}