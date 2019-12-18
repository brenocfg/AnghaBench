#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ base; scalar_t__ idx; int /*<<< orphan*/  ofs; } ;
struct TYPE_10__ {TYPE_1__ mrm; } ;
typedef  int Reg ;
typedef  int /*<<< orphan*/  IRIns ;
typedef  TYPE_2__ ASMState ;

/* Variables and functions */
 int REX_GC64 ; 
 int /*<<< orphan*/  RID_MRM ; 
 scalar_t__ RID_NONE ; 
 int /*<<< orphan*/  RSET_GPR ; 
 int /*<<< orphan*/  XG_ARITHi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XO_LEA ; 
 int /*<<< orphan*/  XOg_ADD ; 
 int /*<<< orphan*/  asm_fusestrref (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_gri (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_loadi (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_mrm (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ra_dest (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asm_strref(ASMState *as, IRIns *ir)
{
  Reg dest = ra_dest(as, ir, RSET_GPR);
  asm_fusestrref(as, ir, RSET_GPR);
  if (as->mrm.base == RID_NONE)
    emit_loadi(as, dest, as->mrm.ofs);
  else if (as->mrm.base == dest && as->mrm.idx == RID_NONE)
    emit_gri(as, XG_ARITHi(XOg_ADD), dest|REX_GC64, as->mrm.ofs);
  else
    emit_mrm(as, XO_LEA, dest|REX_GC64, RID_MRM);
}