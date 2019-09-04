#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int haveoff; int off; int /*<<< orphan*/  namestr; scalar_t__ name; } ;
struct TYPE_7__ {int /*<<< orphan*/  tag; } ;
struct TYPE_10__ {TYPE_1__ attrs; } ;
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_9__ {TYPE_2__ b; } ;
typedef  TYPE_3__ DwarfVal ;
typedef  TYPE_4__ DwarfSym ;
typedef  int /*<<< orphan*/  Dwarf ;

/* Variables and functions */
 char TReference ; 
 char TString ; 
 TYPE_5__* plist ; 
 int /*<<< orphan*/  werrstr (char*,int /*<<< orphan*/ ,...) ; 

void
dwarfdumpsym(Dwarf *d, DwarfSym *s)
{
    int j;
    werrstr("tag %x\n", s->attrs.tag);
    for (j = 0; plist[j].name; j++) {
        char *have = ((char*)&s->attrs) + plist[j].haveoff;
        char *attr = ((char*)&s->attrs) + plist[j].off;
        if (*have == TString) {
            char *str = *((char **)attr);
            werrstr("%s: %s\n", plist[j].namestr, str);
        } else if (*have == TReference) {
            DwarfVal *val = ((DwarfVal*)attr);
            werrstr("%s: %x:%x\n", plist[j].namestr, val->b.data, val->b.len);
        } else if (*have)
            werrstr("%s: (%x)\n", plist[j].namestr, *have);
    }
}