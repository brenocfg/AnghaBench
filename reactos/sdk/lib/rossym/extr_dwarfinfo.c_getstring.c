#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong ;
struct TYPE_9__ {TYPE_2__* d; } ;
struct TYPE_7__ {scalar_t__ data; int /*<<< orphan*/  len; } ;
struct TYPE_8__ {TYPE_1__ str; } ;
typedef  TYPE_3__ DwarfBuf ;

/* Variables and functions */
#define  FormString 129 
#define  FormStrp 128 
 int /*<<< orphan*/  dwarfget4 (TYPE_3__*) ; 
 char* dwarfgetstring (TYPE_3__*) ; 
 char* nil ; 
 int /*<<< orphan*/  werrstr (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
getstring(DwarfBuf *b, int form, char **s)
{
	static int nbad;
	ulong u;

	switch(form){
	default:
		return -1;

	case FormString:
		*s = dwarfgetstring(b);
		return 0;

	case FormStrp:
		u = dwarfget4(b);
		if(u >= b->d->str.len){
			if(++nbad == 1)
				werrstr("dwarf: bad string pointer 0x%lux in attribute", u);
			/* don't return error - maybe can proceed */
			*s = nil;
		}else
			*s = (char*)b->d->str.data + u;
		return 0;

	}
}