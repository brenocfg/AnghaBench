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
 int /*<<< orphan*/  Strncpy (char* const,char const* const,size_t const) ; 
 scalar_t__ strcmp (char const* const,char const* const) ; 
 scalar_t__ strncmp (char const* const,char const* const,size_t const) ; 

void
AbsoluteToRelative(char *const dst, const size_t dsize, const char *const dir, const char *const root, const size_t rootlen)
{
	*dst = '\0';
	if (strcmp(dir, root) != 0) {
		if (strcmp(root, "/") == 0) {
			(void) Strncpy(dst, dir + 1, dsize);
		} else if ((strncmp(root, dir, rootlen) == 0) && (dir[rootlen] == '/')) {
			(void) Strncpy(dst, dir + rootlen + 1, dsize);
		} else {
			/* Still absolute. */
			(void) Strncpy(dst, dir, dsize);
		}
	}
}