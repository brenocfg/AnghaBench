#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int ulong ;
typedef  int u64int ;
typedef  int schar ;
typedef  int s64int ;
typedef  int s32int ;
typedef  int s16int ;
struct TYPE_13__ {scalar_t__ len; scalar_t__ data; } ;
struct TYPE_12__ {int /*<<< orphan*/ * d; scalar_t__ ep; scalar_t__ p; } ;
typedef  TYPE_1__ DwarfBuf ;
typedef  TYPE_2__ DwarfBlock ;
typedef  int /*<<< orphan*/  Dwarf ;

/* Variables and functions */
#define  OpAddr 139 
#define  OpConst1s 138 
#define  OpConst1u 137 
#define  OpConst2s 136 
#define  OpConst2u 135 
#define  OpConst4s 134 
#define  OpConst4u 133 
#define  OpConst8s 132 
#define  OpConst8u 131 
#define  OpConsts 130 
#define  OpConstu 129 
#define  OpPlusUconst 128 
 int TBlock ; 
 int TConstant ; 
 int dwarfget1 (TYPE_1__*) ; 
 int dwarfget128 (TYPE_1__*) ; 
 int dwarfget128s (TYPE_1__*) ; 
 int dwarfget2 (TYPE_1__*) ; 
 int dwarfget4 (TYPE_1__*) ; 
 int /*<<< orphan*/  dwarfget8 (TYPE_1__*) ; 
 int dwarfgetaddr (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
constblock(Dwarf *d, DwarfBlock *bl, ulong *pval)
{
	DwarfBuf b;

	memset(&b, 0, sizeof b);
	b.p = bl->data;
	b.ep = bl->data+bl->len;
	b.d = d;

	switch(dwarfget1(&b)){
	case OpAddr:
		*pval = dwarfgetaddr(&b);
		return TConstant;
	case OpConst1u:
		*pval = dwarfget1(&b);
		return TConstant;
	case OpConst1s:
		*pval = (schar)dwarfget1(&b);
		return TConstant;
	case OpConst2u:
		*pval = dwarfget2(&b);
		return TConstant;
	case OpConst2s:
		*pval = (s16int)dwarfget2(&b);
		return TConstant;
	case OpConst4u:
		*pval = dwarfget4(&b);
		return TConstant;
	case OpConst4s:
		*pval = (s32int)dwarfget4(&b);
		return TConstant;
	case OpConst8u:
		*pval = (u64int)dwarfget8(&b);
		return TConstant;
	case OpConst8s:
		*pval = (s64int)dwarfget8(&b);
		return TConstant;
	case OpConstu:
		*pval = dwarfget128(&b);
		return TConstant;
	case OpConsts:
		*pval = dwarfget128s(&b);
		return TConstant;
	case OpPlusUconst:
		*pval = dwarfget128(&b);
		return TConstant;
	default:
		return TBlock;
	}
}