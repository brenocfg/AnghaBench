#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pubnames; } ;
typedef  int /*<<< orphan*/  DwarfSym ;
typedef  TYPE_1__ Dwarf ;

/* Variables and functions */
 int _dwarfnametounit (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
dwarflookupname(Dwarf *d, char *name, DwarfSym *sym)
{
	return _dwarfnametounit(d, name, &d->pubnames, sym);
}