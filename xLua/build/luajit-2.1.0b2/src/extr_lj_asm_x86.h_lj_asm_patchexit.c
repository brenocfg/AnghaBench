#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  jit_State ;
typedef  int int32_t ;
struct TYPE_5__ {int /*<<< orphan*/  vmstate; } ;
struct TYPE_4__ {int szmcode; scalar_t__* mcode; } ;
typedef  int MSize ;
typedef  scalar_t__ MCode ;
typedef  TYPE_1__ GCtrace ;
typedef  int /*<<< orphan*/  ExitNo ;

/* Variables and functions */
 TYPE_3__* J2G (int /*<<< orphan*/ *) ; 
 scalar_t__ LJ_64 ; 
 scalar_t__ XI_JMP ; 
 scalar_t__ XI_MOVmi ; 
 scalar_t__* exitstub_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int jmprel (scalar_t__*,scalar_t__*) ; 
 scalar_t__* lj_mcode_patch (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int /*<<< orphan*/  lj_mcode_sync (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 scalar_t__ u32ptr (int /*<<< orphan*/ *) ; 

void lj_asm_patchexit(jit_State *J, GCtrace *T, ExitNo exitno, MCode *target)
{
  MCode *p = T->mcode;
  MCode *mcarea = lj_mcode_patch(J, p, 0);
  MSize len = T->szmcode;
  MCode *px = exitstub_addr(J, exitno) - 6;
  MCode *pe = p+len-6;
  uint32_t stateaddr = u32ptr(&J2G(J)->vmstate);
  if (len > 5 && p[len-5] == XI_JMP && p+len-6 + *(int32_t *)(p+len-4) == px)
    *(int32_t *)(p+len-4) = jmprel(p+len, target);
  /* Do not patch parent exit for a stack check. Skip beyond vmstate update. */
  for (; p < pe; p++)
    if (*(uint32_t *)(p+(LJ_64 ? 3 : 2)) == stateaddr && p[0] == XI_MOVmi) {
      p += LJ_64 ? 11 : 10;
      break;
    }
  lua_assert(p < pe);
  for (; p < pe; p++) {
    if ((*(uint16_t *)p & 0xf0ff) == 0x800f && p + *(int32_t *)(p+2) == px) {
      *(int32_t *)(p+2) = jmprel(p+6, target);
      p += 5;
    }
  }
  lj_mcode_sync(T->mcode, T->mcode + T->szmcode);
  lj_mcode_patch(J, mcarea, 1);
}