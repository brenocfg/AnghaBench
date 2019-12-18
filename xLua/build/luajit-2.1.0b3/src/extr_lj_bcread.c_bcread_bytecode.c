#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; int /*<<< orphan*/  framesize; } ;
typedef  int MSize ;
typedef  int /*<<< orphan*/  LexState ;
typedef  TYPE_1__ GCproto ;
typedef  int /*<<< orphan*/  BCIns ;

/* Variables and functions */
 int /*<<< orphan*/  BCINS_AD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BC_FUNCF ; 
 int /*<<< orphan*/  BC_FUNCV ; 
 int PROTO_VARARG ; 
 int /*<<< orphan*/  bcread_block (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ bcread_swap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_bswap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * proto_bc (TYPE_1__*) ; 

__attribute__((used)) static void bcread_bytecode(LexState *ls, GCproto *pt, MSize sizebc)
{
  BCIns *bc = proto_bc(pt);
  bc[0] = BCINS_AD((pt->flags & PROTO_VARARG) ? BC_FUNCV : BC_FUNCF,
		   pt->framesize, 0);
  bcread_block(ls, bc+1, (sizebc-1)*(MSize)sizeof(BCIns));
  /* Swap bytecode instructions if the endianess differs. */
  if (bcread_swap(ls)) {
    MSize i;
    for (i = 1; i < sizebc; i++) bc[i] = lj_bswap(bc[i]);
  }
}