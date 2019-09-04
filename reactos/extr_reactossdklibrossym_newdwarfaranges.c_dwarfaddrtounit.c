#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int ulong ;
typedef  int /*<<< orphan*/  uchar ;
struct TYPE_10__ {int len; int /*<<< orphan*/ * data; } ;
struct TYPE_12__ {int addrsize; TYPE_1__ aranges; } ;
struct TYPE_11__ {int addrsize; int /*<<< orphan*/ * p; int /*<<< orphan*/ * ep; TYPE_3__* d; } ;
typedef  TYPE_2__ DwarfBuf ;
typedef  TYPE_3__ Dwarf ;

/* Variables and functions */
 int /*<<< orphan*/  USED (int) ; 
 void* dwarfget1 (TYPE_2__*) ; 
 int dwarfget2 (TYPE_2__*) ; 
 int dwarfget4 (TYPE_2__*) ; 
 int dwarfgetaddr (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * nil ; 
 int /*<<< orphan*/  werrstr (char*,...) ; 

int
dwarfaddrtounit(Dwarf *d, ulong addr, ulong *unit)
{
    DwarfBuf b;
    int segsize, i;
    ulong len, id, off, base, size;
    uchar *start, *end;

    memset(&b, 0, sizeof b);
    b.d = d;
    b.p = d->aranges.data;
    b.ep = b.p + d->aranges.len;

    while(b.p < b.ep){
        start = b.p;
        len = dwarfget4(&b);
        if (!len) { b.ep = b.p - 4; return -1; }
        if((id = dwarfget2(&b)) != 2){
            if(b.p == nil){
            underflow:
                werrstr("buffer underflow reading address ranges header");
            }else
                werrstr("bad dwarf version 0x%x in address ranges header", id);
            return -1;
        }
        off = dwarfget4(&b);
        b.addrsize = dwarfget1(&b);
        if(d->addrsize == 0)
            d->addrsize = b.addrsize;
        segsize = dwarfget1(&b);
        USED(segsize);	/* what am i supposed to do with this? */
        if(b.p == nil)
            goto underflow;
        if((i = (b.p-start) % (2*b.addrsize)) != 0)
            b.p += 2*b.addrsize - i;
        end = start+4+len;
        while(b.p!=nil && b.p<end){
            base = dwarfgetaddr(&b);
            size = dwarfgetaddr(&b);
            if (!size) continue;
            if(b.p == nil)
                goto underflow;
            if(base <= addr && addr < base+size){
                *unit = off;
                return 0;
            }
        }
        if(b.p == nil)
            goto underflow;
        b.p = end;
    }
    werrstr("address 0x%lux is not listed in dwarf debugging symbols", addr);
    return -1;
}