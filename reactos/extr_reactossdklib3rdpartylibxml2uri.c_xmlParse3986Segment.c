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
 scalar_t__ ISA_PCHAR (char const*) ; 
 int /*<<< orphan*/  NEXT (char const*) ; 

__attribute__((used)) static int
xmlParse3986Segment(const char **str, char forbid, int empty)
{
    const char *cur;

    cur = *str;
    if (!ISA_PCHAR(cur)) {
        if (empty)
	    return(0);
	return(1);
    }
    while (ISA_PCHAR(cur) && (*cur != forbid))
        NEXT(cur);
    *str = cur;
    return (0);
}