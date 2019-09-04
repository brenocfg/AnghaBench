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
 scalar_t__ argv_to_string (char const**,char*,size_t,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 scalar_t__ strlen (char const*) ; 

char *
argv_to_string_alloc(const char *argv[], const char *sep)
{
	size_t i, size = 0;
	char *buf;

	for (i = 0; argv[i]; i++)
		size += strlen(argv[i]);

	buf = malloc(size + 1);
	if (buf && argv_to_string(argv, buf, size + 1, sep))
		return buf;
	free(buf);
	return NULL;
}