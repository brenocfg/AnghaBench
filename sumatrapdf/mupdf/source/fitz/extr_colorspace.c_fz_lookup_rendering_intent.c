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
 int FZ_RI_RELATIVE_COLORIMETRIC ; 
 int /*<<< orphan*/ * fz_intent_names ; 
 scalar_t__ nelem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

int fz_lookup_rendering_intent(const char *name)
{
	int i;
	for (i = 0; i < (int)nelem(fz_intent_names); i++)
		if (!strcmp(name, fz_intent_names[i]))
			return i;
	return FZ_RI_RELATIVE_COLORIMETRIC;
}