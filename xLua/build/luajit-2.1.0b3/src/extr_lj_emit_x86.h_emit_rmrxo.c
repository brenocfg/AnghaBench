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
typedef  int /*<<< orphan*/  x86Op ;
typedef  int /*<<< orphan*/  x86Mode ;
typedef  scalar_t__ int32_t ;
struct TYPE_3__ {scalar_t__* mcp; } ;
typedef  int Reg ;
typedef  scalar_t__ MCode ;
typedef  TYPE_1__ ASMState ;

/* Variables and functions */
 int RID_EBP ; 
 int /*<<< orphan*/  XM_OFS0 ; 
 int /*<<< orphan*/  XM_OFS32 ; 
 int /*<<< orphan*/  XM_OFS8 ; 
 scalar_t__ checki8 (scalar_t__) ; 
 scalar_t__* emit_opmx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,scalar_t__*) ; 

__attribute__((used)) static void emit_rmrxo(ASMState *as, x86Op xo, Reg rr, Reg rb, Reg rx,
		       x86Mode scale, int32_t ofs)
{
  MCode *p = as->mcp;
  x86Mode mode;
  if (ofs == 0 && (rb&7) != RID_EBP) {
    mode = XM_OFS0;
  } else if (checki8(ofs)) {
    mode = XM_OFS8;
    *--p = (MCode)ofs;
  } else {
    mode = XM_OFS32;
    p -= 4;
    *(int32_t *)p = ofs;
  }
  as->mcp = emit_opmx(xo, mode, scale, rr, rb, rx, p);
}