#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ulong ;
struct TYPE_13__ {scalar_t__ data; } ;
struct TYPE_17__ {TYPE_1__ info; } ;
struct TYPE_14__ {int /*<<< orphan*/  tag; } ;
struct TYPE_15__ {int /*<<< orphan*/  ep; scalar_t__ p; TYPE_5__* d; } ;
struct TYPE_16__ {TYPE_2__ attrs; TYPE_3__ b; } ;
typedef  TYPE_4__ DwarfSym ;
typedef  TYPE_5__ Dwarf ;

/* Variables and functions */
 scalar_t__ dwarfenumunit (TYPE_5__*,scalar_t__,TYPE_4__*) ; 
 int dwarfnextsymat (TYPE_5__*,TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  werrstr (char*,scalar_t__,scalar_t__,...) ; 

int
dwarfseeksym(Dwarf *d, ulong unit, ulong off, DwarfSym *s)
{
    DwarfSym compunit = { };
    if(dwarfenumunit(d, unit, &compunit) < 0)
        return -1;
    werrstr("dwarfseeksym: unit %x off %x\n", unit, off);
    s->b.d = d;
    s->b.p = d->info.data + unit + off;
    s->b.ep = compunit.b.ep;
    if(dwarfnextsymat(d, &compunit, s) == -1)
        return -1;
    werrstr("dwarfseeksym: unit %x off %x, tag %x", unit, off, s->attrs.tag);
    return 0;
}