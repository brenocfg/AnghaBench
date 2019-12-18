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
 int USFIELD_LAST ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * us_field_names ; 

__attribute__((used)) static int
us_field_index(char *field)
{
	int i;

	for (i = 0; i < USFIELD_LAST; i++) {
		if (strcmp(field, us_field_names[i]) == 0)
			return (i);
	}

	return (-1);
}