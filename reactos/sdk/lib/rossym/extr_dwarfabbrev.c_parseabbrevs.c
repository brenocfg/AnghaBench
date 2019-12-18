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
struct TYPE_12__ {scalar_t__ len; scalar_t__ data; } ;
struct TYPE_16__ {TYPE_1__ abbrev; } ;
struct TYPE_15__ {int haskids; int nattr; TYPE_3__* attr; scalar_t__ tag; scalar_t__ num; } ;
struct TYPE_14__ {scalar_t__ form; scalar_t__ name; } ;
struct TYPE_13__ {scalar_t__ p; scalar_t__ ep; } ;
typedef  TYPE_2__ DwarfBuf ;
typedef  TYPE_3__ DwarfAttr ;
typedef  TYPE_4__ DwarfAbbrev ;
typedef  TYPE_5__ Dwarf ;

/* Variables and functions */
 int dwarfget1 (TYPE_2__*) ; 
 scalar_t__ dwarfget128 (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nil ; 
 int /*<<< orphan*/  werrstr (char*,...) ; 

__attribute__((used)) static int
parseabbrevs(Dwarf *d, ulong off, DwarfAbbrev *abbrev, DwarfAttr *attr, int *pnabbrev, int *pnattr)
{
	int i, nabbrev, nattr, haskids;
	ulong num, tag, name, form;
	DwarfBuf b;

	if(off >= d->abbrev.len){
		werrstr("bad abbrev section offset 0x%lux >= 0x%lux\n", off, d->abbrev.len);
		return -1;
	}

	memset(&b, 0, sizeof b);
	b.p = d->abbrev.data + off;
	b.ep = d->abbrev.data + d->abbrev.len;

	nabbrev = 0;
	nattr = 0;
	for(;;){
		if(b.p == nil){
			werrstr("malformed abbrev data");
			return -1;
		}
		num = dwarfget128(&b);
		if(num == 0)
			break;
		tag = dwarfget128(&b);
		haskids = dwarfget1(&b);
		for(i=0;; i++){
			name = dwarfget128(&b);
			form = dwarfget128(&b);
			if(name == 0 && form == 0)
				break;
			if(attr){
				attr[i].name = name;
				attr[i].form = form;
			}
		}
		if(abbrev){
			abbrev->num = num;
			abbrev->tag = tag;
			abbrev->haskids = haskids;
			abbrev->attr = attr;
			abbrev->nattr = i;
			abbrev++;
			attr += i;
		}
		nabbrev++;
		nattr += i;
	}
	if(pnabbrev)
		*pnabbrev = nabbrev;
	if(pnattr)
		*pnattr = nattr;
	return 0;
}