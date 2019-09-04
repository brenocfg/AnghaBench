#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong ;
struct TYPE_3__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  DwarfBuf ;
typedef  TYPE_1__ DwarfBlock ;

/* Variables and functions */
#define  FormDwarfBlock 131 
#define  FormDwarfBlock1 130 
#define  FormDwarfBlock2 129 
#define  FormDwarfBlock4 128 
 int /*<<< orphan*/  dwarfget1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarfget128 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarfget2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarfget4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarfgetnref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nil ; 

__attribute__((used)) static int
getblock(DwarfBuf *b, int form, DwarfBlock *bl)
{
	ulong n;

	switch(form){
	default:
		return -1;
	case FormDwarfBlock:
		n = dwarfget128(b);
		goto copyn;
	case FormDwarfBlock1:
		n = dwarfget1(b);
		goto copyn;
	case FormDwarfBlock2:
		n = dwarfget2(b);
		goto copyn;
	case FormDwarfBlock4:
		n = dwarfget4(b);
	copyn:
		bl->data = dwarfgetnref(b, n);
		bl->len = n;
		if(bl->data == nil)
			return -1;
		return 0;
	}
}