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
 int /*<<< orphan*/  Strncat (char*,char*,size_t) ; 
 int /*<<< orphan*/  Strncpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char const*) ; 

void
AbbrevStr(char *dst, const char *src, size_t max, int mode)
{
	int len;

	len = (int) strlen(src);
	if (len > (int) max) {
		if (mode == 0) {
			/* ...Put ellipses at left */
			(void) strcpy(dst, "...");
			(void) Strncat(dst, (char *) src + len - (int) max + 3, max + 1);
		} else {
			/* Put ellipses at right... */
			(void) Strncpy(dst, (char *) src, max + 1);
			(void) strcpy(dst + max - 3, "...");
		}
	} else {
		(void) Strncpy(dst, (char *) src, max + 1);
	}
}