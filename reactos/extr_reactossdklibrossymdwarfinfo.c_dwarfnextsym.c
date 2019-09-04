#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ulong ;
struct TYPE_16__ {scalar_t__ haskids; } ;
struct TYPE_15__ {scalar_t__ p; scalar_t__ ep; } ;
struct TYPE_12__ {scalar_t__ len; scalar_t__ data; } ;
struct TYPE_14__ {TYPE_1__ info; } ;
struct TYPE_13__ {scalar_t__ depth; int allunits; scalar_t__ nextunit; scalar_t__ uoff; scalar_t__ unit; TYPE_5__ attrs; TYPE_4__ b; int /*<<< orphan*/  aoff; } ;
typedef  TYPE_2__ DwarfSym ;
typedef  int /*<<< orphan*/  DwarfAbbrev ;
typedef  TYPE_3__ Dwarf ;

/* Variables and functions */
 scalar_t__ dwarfenumunit (TYPE_3__*,scalar_t__,TYPE_2__*) ; 
 scalar_t__ dwarfget128 (TYPE_4__*) ; 
 int /*<<< orphan*/ * dwarfgetabbrev (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * nil ; 
 scalar_t__ parseattrs (TYPE_4__*,scalar_t__,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  werrstr (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 

int
dwarfnextsym(Dwarf *d, DwarfSym *s)
{
	ulong num;
	DwarfAbbrev *a;

	if(s->attrs.haskids)
		s->depth++;
top:
	if(s->b.p >= s->b.ep){
		if(s->allunits && s->nextunit < d->info.len){
			if(dwarfenumunit(d, s->nextunit, s) < 0) {
				return -1;
			}
			s->allunits = 1;
			goto top;
		}
		return 0;
	}

	s->uoff = s->b.p - (d->info.data+s->unit);
	num = dwarfget128(&s->b);
	if(num == 0){
		if(s->depth == 0) {
			return 0;
		}
		if(s->depth > 0)
			s->depth--;
		goto top;
	}

	a = dwarfgetabbrev(d, s->aoff, num);
	if(a == nil){
		werrstr("getabbrev %ud %ud for %ud,%ud: %r\n", s->aoff, num, s->unit, s->uoff);
		return -1;
	}
	if(parseattrs(&s->b, s->unit, a, &s->attrs) < 0) {
		return -1;
	}
	return 1;
}