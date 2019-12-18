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
 int /*<<< orphan*/  assert (char const*) ; 
 size_t strnpcpy (char**,size_t,char const*,size_t) ; 

size_t strnscpy(char *dest, size_t size, const char *src, size_t len) {
        char *s;

        assert(dest);
        assert(src);

        s = dest;
        return strnpcpy(&s, size, src, len);
}