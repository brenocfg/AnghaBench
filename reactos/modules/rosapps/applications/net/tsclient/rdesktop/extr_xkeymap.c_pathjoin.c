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
 int PATH_MAX ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strncat (char*,char const*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 char* xmalloc (int) ; 

__attribute__((used)) static char *
pathjoin(const char *a, const char *b)
{
	char *result;
	result = xmalloc(PATH_MAX * 2 + 1);

	if (b[0] == '/')
	{
		strncpy(result, b, PATH_MAX);
	}
	else
	{
		strncpy(result, a, PATH_MAX);
		strcat(result, "/");
		strncat(result, b, PATH_MAX);
	}
	return result;
}