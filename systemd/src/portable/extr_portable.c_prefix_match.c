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
 int IN_SET (char const,char,char,char,int /*<<< orphan*/ ) ; 
 char* startswith (char const*,char const*) ; 

__attribute__((used)) static bool prefix_match(const char *unit, const char *prefix) {
        const char *p;

        p = startswith(unit, prefix);
        if (!p)
                return false;

        /* Only respect prefixes followed by dash or dot or when there's a complete match */
        return IN_SET(*p, '-', '.', '@', 0);
}