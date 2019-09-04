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
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 
 size_t strlen (char*) ; 
 char* xrealloc (char*,size_t) ; 

__attribute__((used)) static void
cmd_string_copy(char **dst, char *src, size_t *len)
{
	size_t srclen;

	srclen = strlen(src);

	*dst = xrealloc(*dst, *len + srclen + 1);
	strlcpy(*dst + *len, src, srclen + 1);

	*len += srclen;
	free(src);
}