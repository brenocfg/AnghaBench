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
 size_t strlen (char const*) ; 
 int strncmp (char const*,char const*,size_t) ; 

__attribute__((used)) static int
strrcmp(const char *s1, const char *s2)
{
    size_t m, n;
    m = strlen(s1);
    n = strlen(s2);
    if (n > m)
        return 1;
    return strncmp(s1 + m - n, s2, n);
}