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
struct environ {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  environ_set (struct environ*,char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strchr (char const*,char) ; 
 size_t strcspn (char*,char*) ; 
 char* xstrdup (char const*) ; 

void
environ_put(struct environ *env, const char *var)
{
	char	*name, *value;

	value = strchr(var, '=');
	if (value == NULL)
		return;
	value++;

	name = xstrdup(var);
	name[strcspn(name, "=")] = '\0';

	environ_set(env, name, "%s", value);
	free(name);
}