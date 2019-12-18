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
 int strcasecmp (char const*,char const*) ; 

__attribute__((used)) static inline int
CompareStrings(const char *a, const char *b)
{
    if (a && b)
        return strcasecmp(a, b);
    if (!a && !b)
        return 0;
    return a ? 1 : -1;
}