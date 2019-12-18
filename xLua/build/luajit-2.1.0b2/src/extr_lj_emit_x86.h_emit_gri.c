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
typedef  int x86Group ;
typedef  scalar_t__ int32_t ;
struct TYPE_3__ {scalar_t__* mcp; } ;
typedef  int Reg ;
typedef  scalar_t__ MCode ;
typedef  TYPE_1__ ASMState ;

/* Variables and functions */
 int REX_64 ; 
 int /*<<< orphan*/  XG_TOXOi (int) ; 
 int /*<<< orphan*/  XG_TOXOi8 (int) ; 
 int /*<<< orphan*/  XM_REG ; 
 scalar_t__ checki8 (scalar_t__) ; 
 scalar_t__* emit_opm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void emit_gri(ASMState *as, x86Group xg, Reg rb, int32_t i)
{
  MCode *p = as->mcp;
  x86Op xo;
  if (checki8(i)) {
    *--p = (MCode)i;
    xo = XG_TOXOi8(xg);
  } else {
    p -= 4;
    *(int32_t *)p = i;
    xo = XG_TOXOi(xg);
  }
  as->mcp = emit_opm(xo, XM_REG, (Reg)(xg & 7) | (rb & REX_64), rb, p, 0);
}