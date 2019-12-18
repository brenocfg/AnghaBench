#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint ;
struct TYPE_16__ {scalar_t__ len; scalar_t__ data; } ;
struct TYPE_21__ {TYPE_3__ info; } ;
struct TYPE_19__ {scalar_t__ p; TYPE_5__* d; } ;
struct TYPE_14__ {scalar_t__ sibling; } ;
struct TYPE_15__ {scalar_t__ sibling; TYPE_1__ have; int /*<<< orphan*/  haskids; } ;
struct TYPE_20__ {scalar_t__ childoff; scalar_t__ unit; TYPE_6__ b; TYPE_2__ attrs; scalar_t__ depth; int /*<<< orphan*/  aoff; } ;
struct TYPE_17__ {scalar_t__ data; } ;
struct TYPE_18__ {TYPE_4__ info; } ;
typedef  TYPE_7__ DwarfSym ;
typedef  TYPE_8__ Dwarf ;

/* Variables and functions */
 int dwarfnextsym (TYPE_8__*,TYPE_7__*) ; 
 int /*<<< orphan*/  werrstr (char*,scalar_t__,...) ; 

int
dwarfnextsymat(Dwarf *d, DwarfSym *parent, DwarfSym *child)
{
    uint sib;

    if (!parent->attrs.haskids || !parent->childoff)
        return -1;

	child->unit = parent->unit;
    child->aoff = parent->aoff;
    child->depth = parent->depth + 1;
    if(child->attrs.have.sibling){
        sib = child->attrs.sibling;
        if(sib < d->info.len && d->info.data+sib > child->b.p)
            child->b.p = d->info.data+sib;
        else if (sib >= d->info.len) {
            werrstr("sibling reported as out of bounds %d vs %d", sib, d->info.len);
            return -1;
        } else if (d->info.data+sib+parent->unit < child->b.p) {
            werrstr("subsequent sibling is listed before prev %d vs %d", sib+parent->unit, child->b.p - d->info.data);
            return -1;
        }
    }

    // Uninitialized
    if (!child->b.d) {
        child->b = parent->b;
        child->b.p = parent->childoff + parent->b.d->info.data;
        werrstr("Rewound to childoff %x\n", parent->childoff);
    }

    return dwarfnextsym(d, child);
}