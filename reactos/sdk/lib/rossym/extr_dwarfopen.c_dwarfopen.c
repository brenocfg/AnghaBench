#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {TYPE_1__* data; } ;
struct TYPE_24__ {scalar_t__ (* loadsection ) (TYPE_1__*,char*,TYPE_4__*) ;TYPE_4__ info; TYPE_4__ str; TYPE_4__ ranges; TYPE_4__ pubnames; TYPE_4__ line; TYPE_4__ frame; TYPE_4__ aranges; TYPE_4__ abbrev; struct TYPE_24__* pe; } ;
typedef  TYPE_1__ Pe ;
typedef  TYPE_1__ Dwarf ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* mallocz (int,int) ; 
 TYPE_1__* nil ; 
 scalar_t__ stub1 (TYPE_1__*,char*,TYPE_4__*) ; 
 scalar_t__ stub2 (TYPE_1__*,char*,TYPE_4__*) ; 
 scalar_t__ stub3 (TYPE_1__*,char*,TYPE_4__*) ; 
 scalar_t__ stub4 (TYPE_1__*,char*,TYPE_4__*) ; 
 scalar_t__ stub5 (TYPE_1__*,char*,TYPE_4__*) ; 
 scalar_t__ stub6 (TYPE_1__*,char*,TYPE_4__*) ; 
 scalar_t__ stub7 (TYPE_1__*,char*,TYPE_4__*) ; 
 scalar_t__ stub8 (TYPE_1__*,char*,TYPE_4__*) ; 
 int /*<<< orphan*/  werrstr (char*) ; 

Dwarf*
dwarfopen(Pe *pe)
{
	Dwarf *d;

	if(pe == nil){
		werrstr("nil pe passed to dwarfopen");
		return nil;
	}

	d = mallocz(sizeof(Dwarf), 1);
	if(d == nil)
		return nil;

	d->pe = pe;
	if(pe->loadsection(pe, ".debug_abbrev", &d->abbrev) < 0
	|| pe->loadsection(pe, ".debug_aranges", &d->aranges) < 0
	|| pe->loadsection(pe, ".debug_line", &d->line) < 0
	|| pe->loadsection(pe, ".debug_pubnames", &d->pubnames) < 0
	|| pe->loadsection(pe, ".debug_info", &d->info) < 0)
		goto err;
	pe->loadsection(pe, ".debug_frame", &d->frame);
	pe->loadsection(pe, ".debug_ranges", &d->ranges);
	pe->loadsection(pe, ".debug_str", &d->str);

	return d;

err:
	DPRINT("Failed to open dwarf\n");
	free(d->abbrev.data);
	free(d->aranges.data);
	free(d->frame.data);
	free(d->line.data);
	free(d->pubnames.data);
	free(d->ranges.data);
	free(d->str.data);
	free(d->info.data);
	free(d);
	return nil;
}