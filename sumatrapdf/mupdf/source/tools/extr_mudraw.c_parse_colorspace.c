#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int colorspace; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int CS_ICC ; 
 TYPE_1__* cs_name_table ; 
 char const* icc_filename ; 
 scalar_t__ nelem (TYPE_1__*) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
parse_colorspace(const char *name)
{
	int i;

	for (i = 0; i < (int)nelem(cs_name_table); i++)
	{
		if (!strcmp(name, cs_name_table[i].name))
			return cs_name_table[i].colorspace;
	}

	/* Assume ICC. We will error out later if not the case. */
	icc_filename = name;
	return CS_ICC;
}