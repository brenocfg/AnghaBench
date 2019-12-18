#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int ulong ;
typedef  int /*<<< orphan*/  uchar ;
struct TYPE_15__ {int len; int /*<<< orphan*/ * data; } ;
struct TYPE_19__ {int addrsize; TYPE_1__ frame; } ;
struct TYPE_18__ {int addrsize; int /*<<< orphan*/ * ep; int /*<<< orphan*/ * p; TYPE_5__* d; } ;
struct TYPE_16__ {int /*<<< orphan*/ * ep; int /*<<< orphan*/ * p; } ;
struct TYPE_17__ {int loc; int endloc; TYPE_2__ init; void* nr; void* rareg; int /*<<< orphan*/  dquantum; void* iquantum; } ;
typedef  TYPE_3__ State ;
typedef  TYPE_4__ DwarfBuf ;
typedef  TYPE_5__ Dwarf ;

/* Variables and functions */
 int dwarfget1 (TYPE_4__*) ; 
 void* dwarfget128 (TYPE_4__*) ; 
 int /*<<< orphan*/  dwarfget128s (TYPE_4__*) ; 
 int dwarfget4 (TYPE_4__*) ; 
 int dwarfgetaddr (TYPE_4__*) ; 
 char* dwarfgetstring (TYPE_4__*) ; 
 int /*<<< orphan*/ * nil ; 
 scalar_t__ trace ; 
 int /*<<< orphan*/  werrstr (char*,...) ; 

__attribute__((used)) static int
findfde(Dwarf *d, ulong pc, State *s, DwarfBuf *fde)
{
	static int nbad;
	char *aug;
	uchar *next;
	int i, vers;
	ulong len, id, base, size;
	DwarfBuf b;

	if(d->frame.data == nil){
		werrstr("no frame debugging information");
		return -1;
	}
	b.d = d;
	b.p = d->frame.data;
	b.ep = b.p + d->frame.len;
	b.addrsize = d->addrsize;
	if(b.addrsize == 0)
		b.addrsize = 4;	/* where should i find this? */

	for(; b.p < b.ep; b.p = next){
		if((i = (b.p - d->frame.data) % b.addrsize))
			b.p += b.addrsize - i;
		len = dwarfget4(&b);
		if(len > b.ep-b.p){
			werrstr("bad length in cie/fde header");
			return -1;
		}
		next = b.p+len;
		id = dwarfget4(&b);
		if(id == 0xFFFFFFFF){	/* CIE */
			vers = dwarfget1(&b);
			if (trace) werrstr("CIE len %x id %x vers %x", len, id, vers);
			if(vers != 1 && vers != 2 && vers != 3){
				if(++nbad == 1)
					werrstr("unknown cie version %d (wanted 1-3)", vers);
				continue;
			}
			aug = dwarfgetstring(&b);
			if(aug && *aug){
				if(++nbad == 1)
					werrstr("unknown augmentation: %s", aug);
				continue;
			}
			s->iquantum = dwarfget128(&b);
			s->dquantum = dwarfget128s(&b);
			s->rareg = dwarfget128(&b);
			if(s->rareg > s->nr){
				werrstr("return address is register %d but only have %d registers",
					s->rareg, s->nr);
				return -1;
			}
			s->init.p = b.p;
			s->init.ep = next;
		}else{	/* FDE */
			base = dwarfgetaddr(&b);
			size = dwarfgetaddr(&b);
            if (trace) werrstr("FDE: base %x-%x (want pc %x)", base, base+size, pc);
			fde->p = b.p;
			fde->ep = next;
			s->loc = base;
			s->endloc = base+size;
			if(base <= pc && pc < base+size)
				return 0;
		}
	}
	werrstr("cannot find call frame information for pc 0x%lx", pc);
	return -1;

}