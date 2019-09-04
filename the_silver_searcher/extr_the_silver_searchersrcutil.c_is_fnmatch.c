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
 int /*<<< orphan*/ * strpbrk (char const*,char*) ; 

int is_fnmatch(const char *filename) {
    char fnmatch_chars[] = {
        '!',
        '*',
        '?',
        '[',
        ']',
        '\0'
    };

    return (strpbrk(filename, fnmatch_chars) != NULL);
}