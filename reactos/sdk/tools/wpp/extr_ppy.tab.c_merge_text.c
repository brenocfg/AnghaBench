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
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* pp_xrealloc (char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *merge_text(char *s1, char *s2)
{
	int l1;
	int l2;
	char *snew;
	if(!s1)
		return s2;
	if(!s2)
		return s1;
	l1 = strlen(s1);
	l2 = strlen(s2);
	snew = pp_xrealloc(s1, l1+l2+1);
	if(!snew)
	{
		free(s2);
		return s1;
	}
	s1 = snew;
	memcpy(s1+l1, s2, l2+1);
	free(s2);
	return s1;
}