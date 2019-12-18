#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong ;
struct TYPE_6__ {scalar_t__ type; } ;
typedef  TYPE_1__ DwarfExpr ;
typedef  int /*<<< orphan*/  Dwarf ;

/* Variables and functions */
 scalar_t__ RuleSame ; 
 scalar_t__ dwarfunwind (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,TYPE_1__*,int) ; 
 int nelem (TYPE_1__*) ; 
 int /*<<< orphan*/  print (char*,...) ; 

void
printrules(Dwarf *d, ulong pc)
{
	int i;
	DwarfExpr r[10];
	DwarfExpr cfa, ra;

	if(dwarfunwind(d, pc, &cfa, &ra, r, nelem(r)) < 0)
		print("\tcannot unwind from pc 0x%lux: %r\n", pc);

	print("\tpc=0x%lux cfa=%R ra=%R", pc, &cfa, &ra);
	for(i=0; i<nelem(r); i++)
		if(r[i].type != RuleSame)
			print(" r%d=%R", i, &r[i]);
	print("\n");
}