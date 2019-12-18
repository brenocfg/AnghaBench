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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  strtol (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char* parse_token(const char *current, int32_t *val_out) {
        char *next;
        int32_t val;

        if (!current)
                return NULL;

        val = strtol(current, &next, 0);
        if (*next && *next != ':')
                return NULL;

        if (next != current)
                *val_out = val;

        if (*next)
                next++;

        return next;
}