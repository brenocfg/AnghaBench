#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_8__ {int* mcp; } ;
typedef  int Reg ;
typedef  int MCode ;
typedef  TYPE_1__ ASMState ;

/* Variables and functions */
 int REX_64 ; 
 int /*<<< orphan*/  RID_DISPATCH ; 
 int /*<<< orphan*/  RID_RIP ; 
 scalar_t__ XI_MOVri ; 
 int /*<<< orphan*/  XM_REG ; 
 int /*<<< orphan*/  XO_LEA ; 
 int /*<<< orphan*/  XO_MOVmi ; 
 scalar_t__ checki32 (scalar_t__) ; 
 scalar_t__ checku32 (scalar_t__) ; 
 scalar_t__ dispofs (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  emit_loadi (TYPE_1__*,int,scalar_t__) ; 
 int* emit_opm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*,int) ; 
 int /*<<< orphan*/  emit_rmro (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ mcpofs (TYPE_1__*,scalar_t__) ; 
 scalar_t__ mctopofs (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void emit_loadu64(ASMState *as, Reg r, uint64_t u64)
{
  if (checku32(u64)) {  /* 32 bit load clears upper 32 bits. */
    emit_loadi(as, r, (int32_t)u64);
  } else if (checki32((int64_t)u64)) {  /* Sign-extended 32 bit load. */
    MCode *p = as->mcp;
    *(int32_t *)(p-4) = (int32_t)u64;
    as->mcp = emit_opm(XO_MOVmi, XM_REG, REX_64, r, p, -4);
#if LJ_GC64
  } else if (checki32(dispofs(as, u64))) {
    emit_rmro(as, XO_LEA, r|REX_64, RID_DISPATCH, (int32_t)dispofs(as, u64));
  } else if (checki32(mcpofs(as, u64)) && checki32(mctopofs(as, u64))) {
    /* Since as->realign assumes the code size doesn't change, check
    ** RIP-relative addressing reachability for both as->mcp and as->mctop.
    */
    emit_rmro(as, XO_LEA, r|REX_64, RID_RIP, (int32_t)mcpofs(as, u64));
#endif
  } else {  /* Full-size 64 bit load. */
    MCode *p = as->mcp;
    *(uint64_t *)(p-8) = u64;
    p[-9] = (MCode)(XI_MOVri+(r&7));
    p[-10] = 0x48 + ((r>>3)&1);
    p -= 10;
    as->mcp = p;
  }
}