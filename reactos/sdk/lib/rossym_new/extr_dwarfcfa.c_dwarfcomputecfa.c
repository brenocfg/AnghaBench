#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ulong ;
struct TYPE_6__ {int type; size_t reg; scalar_t__ offset; } ;
struct TYPE_5__ {scalar_t__* Registers; } ;
typedef  TYPE_1__* PROSSYM_REGISTERS ;
typedef  TYPE_2__ DwarfExpr ;
typedef  int /*<<< orphan*/  Dwarf ;

/* Variables and functions */
#define  RuleRegOff 128 
 int /*<<< orphan*/  werrstr (char*,int,...) ; 

int dwarfcomputecfa(Dwarf *d, DwarfExpr *cfa, PROSSYM_REGISTERS registers, ulong *cfaLocation)
{
    switch (cfa->type) {
    case RuleRegOff:
        *cfaLocation = registers->Registers[cfa->reg] + cfa->offset;
        werrstr("cfa reg %d (%x) offset %x = %x", cfa->reg, (ulong)registers->Registers[cfa->reg], cfa->offset, cfaLocation);
        break;
    default:
        werrstr("cfa->type %x", cfa->type);
        return -1;
    }

    return 0;
}