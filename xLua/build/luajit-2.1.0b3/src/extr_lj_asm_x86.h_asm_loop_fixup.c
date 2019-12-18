#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int8_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_5__ {int loopinv; int /*<<< orphan*/  orignins; TYPE_1__* T; int /*<<< orphan*/  stopins; int /*<<< orphan*/  curins; scalar_t__* realign; scalar_t__* mcp; scalar_t__* mctop; } ;
struct TYPE_4__ {int /*<<< orphan*/  nins; } ;
typedef  scalar_t__ MCode ;
typedef  TYPE_2__ ASMState ;

/* Variables and functions */
 scalar_t__ XI_JMP ; 
 scalar_t__ XI_JMPs ; 
 int /*<<< orphan*/  lua_assert (int) ; 

__attribute__((used)) static void asm_loop_fixup(ASMState *as)
{
  MCode *p = as->mctop;
  MCode *target = as->mcp;
  if (as->realign) {  /* Realigned loops use short jumps. */
    as->realign = NULL;  /* Stop another retry. */
    lua_assert(((intptr_t)target & 15) == 0);
    if (as->loopinv) {  /* Inverted loop branch? */
      p -= 5;
      p[0] = XI_JMP;
      lua_assert(target - p >= -128);
      p[-1] = (MCode)(target - p);  /* Patch sjcc. */
      if (as->loopinv == 2)
	p[-3] = (MCode)(target - p + 2);  /* Patch opt. short jp. */
    } else {
      lua_assert(target - p >= -128);
      p[-1] = (MCode)(int8_t)(target - p);  /* Patch short jmp. */
      p[-2] = XI_JMPs;
    }
  } else {
    MCode *newloop;
    p[-5] = XI_JMP;
    if (as->loopinv) {  /* Inverted loop branch? */
      /* asm_guardcc already inverted the jcc and patched the jmp. */
      p -= 5;
      newloop = target+4;
      *(int32_t *)(p-4) = (int32_t)(target - p);  /* Patch jcc. */
      if (as->loopinv == 2) {
	*(int32_t *)(p-10) = (int32_t)(target - p + 6);  /* Patch opt. jp. */
	newloop = target+8;
      }
    } else {  /* Otherwise just patch jmp. */
      *(int32_t *)(p-4) = (int32_t)(target - p);
      newloop = target+3;
    }
    /* Realign small loops and shorten the loop branch. */
    if (newloop >= p - 128) {
      as->realign = newloop;  /* Force a retry and remember alignment. */
      as->curins = as->stopins;  /* Abort asm_trace now. */
      as->T->nins = as->orignins;  /* Remove any added renames. */
    }
  }
}