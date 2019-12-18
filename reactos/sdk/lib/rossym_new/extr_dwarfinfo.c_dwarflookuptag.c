#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong ;
struct TYPE_8__ {int /*<<< orphan*/  tag; } ;
struct TYPE_9__ {TYPE_1__ attrs; } ;
typedef  TYPE_2__ DwarfSym ;
typedef  int /*<<< orphan*/  Dwarf ;

/* Variables and functions */
 scalar_t__ dwarfenumunit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ dwarflookupchildtag (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ dwarfnextsym (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  werrstr (char*,int /*<<< orphan*/ ) ; 

int
dwarflookuptag(Dwarf *d, ulong unit, ulong tag, DwarfSym *s)
{
    DwarfSym compunit = { };
    if (dwarfenumunit(d, unit, &compunit) < 0) {
        return -1;
    }
    do {
        if (compunit.attrs.tag == tag) {
            *s = compunit;
            return 0;
        }
        if (dwarflookupchildtag(d, &compunit, tag, s) == 0)
            return 0;
    } while(dwarfnextsym(d, &compunit) == 0);
    werrstr("symbol with tag 0x%lux not found", tag);
    return -1;
}