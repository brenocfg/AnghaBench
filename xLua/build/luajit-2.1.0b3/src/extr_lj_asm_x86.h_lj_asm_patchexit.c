#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  jit_State ;
typedef  int int32_t ;
struct TYPE_7__ {int /*<<< orphan*/  vmstate; } ;
struct TYPE_6__ {int /*<<< orphan*/  vmstate; } ;
struct TYPE_5__ {int* mcode; int szmcode; } ;
typedef  int MSize ;
typedef  int MCode ;
typedef  TYPE_1__ GCtrace ;
typedef  int /*<<< orphan*/  ExitNo ;

/* Variables and functions */
 scalar_t__ GG_OFS (int /*<<< orphan*/ ) ; 
 TYPE_4__* J2G (int /*<<< orphan*/ *) ; 
 int LJ_64 ; 
 int LJ_GC64 ; 
 int XI_JMP ; 
 int XI_MOVmi ; 
 int /*<<< orphan*/  asm_x86_inslen (int*) ; 
 int /*<<< orphan*/  dispatch ; 
 int* exitstub_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__ g ; 
 int jmprel (int*,int*) ; 
 int* lj_mcode_patch (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  lj_mcode_sync (int*,int*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 scalar_t__ u32ptr (int /*<<< orphan*/ *) ; 

void lj_asm_patchexit(jit_State *J, GCtrace *T, ExitNo exitno, MCode *target)
{
  MCode *p = T->mcode;
  MCode *mcarea = lj_mcode_patch(J, p, 0);
  MSize len = T->szmcode;
  MCode *px = exitstub_addr(J, exitno) - 6;
  MCode *pe = p+len-6;
#if LJ_GC64
  uint32_t statei = (uint32_t)(GG_OFS(g.vmstate) - GG_OFS(dispatch));
#else
  uint32_t statei = u32ptr(&J2G(J)->vmstate);
#endif
  if (len > 5 && p[len-5] == XI_JMP && p+len-6 + *(int32_t *)(p+len-4) == px)
    *(int32_t *)(p+len-4) = jmprel(p+len, target);
  /* Do not patch parent exit for a stack check. Skip beyond vmstate update. */
  for (; p < pe; p += asm_x86_inslen(p)) {
    intptr_t ofs = LJ_GC64 ? (p[0] & 0xf0) == 0x40 : LJ_64;
    if (*(uint32_t *)(p+2+ofs) == statei && p[ofs+LJ_GC64-LJ_64] == XI_MOVmi)
      break;
  }
  lua_assert(p < pe);
  for (; p < pe; p += asm_x86_inslen(p))
    if ((*(uint16_t *)p & 0xf0ff) == 0x800f && p + *(int32_t *)(p+2) == px)
      *(int32_t *)(p+2) = jmprel(p+6, target);
  lj_mcode_sync(T->mcode, T->mcode + T->szmcode);
  lj_mcode_patch(J, mcarea, 1);
}