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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char* memcpy (char*,char const*,int) ; 
 char* pp_xmalloc (int) ; 
 int strlen (char const*) ; 

char *pp_xstrdup(const char *str)
{
	char *s;
	int len;

	assert(str != NULL);
	len = strlen(str)+1;
	s = pp_xmalloc(len);
	if(!s)
		return NULL;
	return memcpy(s, str, len);
}