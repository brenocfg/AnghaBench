#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong ;
struct TYPE_6__ {scalar_t__ name; } ;
struct TYPE_7__ {TYPE_1__ attrs; } ;
typedef  TYPE_2__ DwarfSym ;
typedef  int /*<<< orphan*/  Dwarf ;

/* Variables and functions */
 scalar_t__ dwarfenumunit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int dwarfnextsymat (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  werrstr (char*,char*) ; 

int
dwarflookupnameinunit(Dwarf *d, ulong unit, char *name, DwarfSym *s)
{
	if(dwarfenumunit(d, unit, s) < 0)
		return -1;

	dwarfnextsymat(d, s, 0);	/* s is now the CompileUnit */
	while(dwarfnextsymat(d, s, 1) == 1)
		if(s->attrs.name && strcmp(s->attrs.name, name) == 0)
			return 0;
	werrstr("symbol '%s' not found", name);
	return -1;
}