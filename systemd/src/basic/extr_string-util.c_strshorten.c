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
 int /*<<< orphan*/  assert (char*) ; 
 size_t strnlen (char*,size_t) ; 

char* strshorten(char *s, size_t l) {
        assert(s);

        if (strnlen(s, l+1) > l)
                s[l] = 0;

        return s;
}