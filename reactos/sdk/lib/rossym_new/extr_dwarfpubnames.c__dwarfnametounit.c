#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ulong ;
typedef  int /*<<< orphan*/  uchar ;
struct TYPE_19__ {scalar_t__ data; } ;
struct TYPE_24__ {TYPE_2__ info; } ;
struct TYPE_23__ {int data; int len; } ;
struct TYPE_22__ {int p; int ep; TYPE_7__* d; } ;
struct TYPE_20__ {char* name; } ;
struct TYPE_18__ {scalar_t__ ep; scalar_t__ p; } ;
struct TYPE_21__ {TYPE_3__ attrs; TYPE_1__ b; } ;
typedef  TYPE_4__ DwarfSym ;
typedef  TYPE_5__ DwarfBuf ;
typedef  TYPE_6__ DwarfBlock ;
typedef  TYPE_7__ Dwarf ;

/* Variables and functions */
 scalar_t__ dwarfenumunit (TYPE_7__*,scalar_t__,TYPE_4__*) ; 
 int dwarfget2 (TYPE_5__*) ; 
 scalar_t__ dwarfget4 (TYPE_5__*) ; 
 char* dwarfgetstring (TYPE_5__*) ; 
 scalar_t__ dwarfnextsym (TYPE_7__*,TYPE_4__*) ; 
 char* nil ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  werrstr (char*,...) ; 

__attribute__((used)) static int
_dwarfnametounit(Dwarf *d, char *name, DwarfBlock *bl, DwarfSym *s)
{
	int vers;
	ulong len, unit, off;
	uchar *next;
	char *str;
	DwarfBuf b;

	b.d = d;
	b.p = bl->data;
	b.ep = b.p + bl->len;

	while(b.p < b.ep){
		len = dwarfget4(&b);
		if(len > b.ep-b.p){
			werrstr("bad length in dwarf name header");
			return -1;
		}
		next = b.p + len;
		vers = dwarfget2(&b);
		if(vers != 1 && vers != 2){
			werrstr("bad version %d in dwarf name header", vers);
			return -1;
		}
		unit = dwarfget4(&b);
		dwarfget4(&b);	/* unit length */
		while(b.p < next){
			off = dwarfget4(&b);
			if(off == 0)
				break;
			str = dwarfgetstring(&b);
			if(strcmp(str, name) == 0){
				if(dwarfenumunit(d, unit, s) < 0)
					return -1;
				if(unit + off >= s->b.ep - d->info.data){
					werrstr("bad offset in name entry");
					return -1;
				}
				s->b.p = d->info.data + unit + off;
				if(dwarfnextsym(d, s) < 0)
					return -1;
				if(s->attrs.name==nil || strcmp(s->attrs.name, name)!=0){
					werrstr("unexpected name %#q in lookup for %#q", s->attrs.name, name);
					return -1;
				}
				return 0;
			}
		}
		b.p = next;
	}
	werrstr("unknown name '%s'", name);
	return -1;
}