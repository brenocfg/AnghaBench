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
 int /*<<< orphan*/  strlen (char const*) ; 
 size_t strnscpy (char*,size_t,char const*,int /*<<< orphan*/ ) ; 

size_t strscpy(char *dest, size_t size, const char *src) {
        assert(dest);
        assert(src);

        return strnscpy(dest, size, src, strlen(src));
}