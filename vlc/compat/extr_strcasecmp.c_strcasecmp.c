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
 int /*<<< orphan*/  assert (unsigned char) ; 
 int stricmp (char const*,char const*) ; 
 int tolower (unsigned char) ; 

int strcasecmp (const char *s1, const char *s2)
{
#ifdef HAVE_STRICMP
    return stricmp (s1, s2);
#else
    for (size_t i = 0;; i++)
    {
        unsigned char c1 = s1[i], c2 = s2[i];
        int d = tolower (c1) - tolower (c2);
        if (d || !c1)
            return d;
        assert (c2);
    }
#endif
}