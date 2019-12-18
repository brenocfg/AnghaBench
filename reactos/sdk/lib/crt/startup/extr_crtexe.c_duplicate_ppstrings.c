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
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int strlen (char*) ; 

__attribute__((used)) static void duplicate_ppstrings (int ac, char ***av)
{
	char **avl;
	int i;
	char **n = (char **) malloc (sizeof (char *) * (ac + 1));

	avl=*av;
	for (i=0; i < ac; i++)
	  {
		size_t l = strlen (avl[i]) + 1;
		n[i] = (char *) malloc (l);
		memcpy (n[i], avl[i], l);
	  }
	n[i] = NULL;
	*av = n;
}