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
struct TYPE_9__ {int addrsize; int /*<<< orphan*/  p; TYPE_1__* d; } ;
struct TYPE_8__ {int addrsize; } ;
typedef  TYPE_2__ DwarfBuf ;

/* Variables and functions */
 int /*<<< orphan*/  dwarfget1 (TYPE_2__*) ; 
 int /*<<< orphan*/  dwarfget2 (TYPE_2__*) ; 
 int /*<<< orphan*/  dwarfget4 (TYPE_2__*) ; 
 int /*<<< orphan*/  dwarfget8 (TYPE_2__*) ; 
 int /*<<< orphan*/  nil ; 
 int /*<<< orphan*/  werrstr (char*,int) ; 

ulong
dwarfgetaddr(DwarfBuf *b)
{
	static int nbad;

	if(b->addrsize == 0)
		b->addrsize = b->d->addrsize;

	switch(b->addrsize){
	case 1:
		return dwarfget1(b);
	case 2:
		return dwarfget2(b);
	case 4:
		return dwarfget4(b);
	case 8:
		return dwarfget8(b);
	default:
		if(++nbad == 1)
			werrstr("dwarf: unexpected address size %lud in dwarfgetaddr\n", b->addrsize);
		b->p = nil;
		return 0;
	}
}