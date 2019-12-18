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
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strnlen (char const*,size_t) ; 
 char* uu_zalloc (size_t) ; 

char *
uu_strndup(const char *s, size_t n)
{
	size_t len;
	char *p;

	len = strnlen(s, n);
	p = uu_zalloc(len + 1);
	if (p == NULL)
		return (NULL);

	if (len > 0)
		(void) memcpy(p, s, len);
	p[len] = '\0';

	return (p);
}