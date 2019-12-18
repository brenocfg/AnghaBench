#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ const uint64_t ;
typedef  void* int32_t ;
struct TYPE_14__ {scalar_t__ u64; } ;
struct TYPE_11__ {void* idx; void* base; void* ofs; } ;
struct TYPE_13__ {int mcbot; int mclim; TYPE_1__ mrm; void* mctop; } ;
struct TYPE_12__ {void* i; } ;
typedef  int /*<<< orphan*/  Reg ;
typedef  TYPE_2__ IRIns ;
typedef  TYPE_3__ ASMState ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_GC64 ; 
 int MCLIM_REDZONE ; 
 void* RID_DISPATCH ; 
 int /*<<< orphan*/  RID_MRM ; 
 void* RID_NONE ; 
 void* RID_RIP ; 
 int /*<<< orphan*/  XI_INT3 ; 
 scalar_t__ checki32 (intptr_t) ; 
 intptr_t dispofs (TYPE_3__*,scalar_t__ const*) ; 
 TYPE_6__* ir_k64 (TYPE_2__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 intptr_t mcpofs (TYPE_3__*,...) ; 
 intptr_t mctopofs (TYPE_3__*,scalar_t__ const*) ; 
 void* ptr2addr (scalar_t__ const*) ; 

__attribute__((used)) static Reg asm_fuseloadk64(ASMState *as, IRIns *ir)
{
  const uint64_t *k = &ir_k64(ir)->u64;
  if (!LJ_GC64 || checki32((intptr_t)k)) {
    as->mrm.ofs = ptr2addr(k);
    as->mrm.base = RID_NONE;
#if LJ_GC64
  } else if (checki32(dispofs(as, k))) {
    as->mrm.ofs = (int32_t)dispofs(as, k);
    as->mrm.base = RID_DISPATCH;
  } else if (checki32(mcpofs(as, k)) && checki32(mcpofs(as, k+1)) &&
	     checki32(mctopofs(as, k)) && checki32(mctopofs(as, k+1))) {
    as->mrm.ofs = (int32_t)mcpofs(as, k);
    as->mrm.base = RID_RIP;
  } else {
    if (ir->i) {
      lua_assert(*k == *(uint64_t*)(as->mctop - ir->i));
    } else {
      while ((uintptr_t)as->mcbot & 7) *as->mcbot++ = XI_INT3;
      *(uint64_t*)as->mcbot = *k;
      ir->i = (int32_t)(as->mctop - as->mcbot);
      as->mcbot += 8;
      as->mclim = as->mcbot + MCLIM_REDZONE;
    }
    as->mrm.ofs = (int32_t)mcpofs(as, as->mctop - ir->i);
    as->mrm.base = RID_RIP;
#endif
  }
  as->mrm.idx = RID_NONE;
  return RID_MRM;
}