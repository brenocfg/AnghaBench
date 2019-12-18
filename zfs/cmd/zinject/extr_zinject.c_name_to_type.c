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
typedef  int err_type_t ;

/* Variables and functions */
 int TYPE_INVAL ; 
 int /*<<< orphan*/ * errtable ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static err_type_t
name_to_type(const char *arg)
{
	int i;
	for (i = 0; i < TYPE_INVAL; i++)
		if (strcmp(errtable[i], arg) == 0)
			return (i);

	return (TYPE_INVAL);
}