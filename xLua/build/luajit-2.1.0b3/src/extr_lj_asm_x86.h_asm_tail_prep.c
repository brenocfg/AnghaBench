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
struct TYPE_3__ {int flags; int /*<<< orphan*/ * invmcp; int /*<<< orphan*/ * mcp; scalar_t__ loopref; scalar_t__ loopinv; int /*<<< orphan*/ * mctop; scalar_t__ realign; } ;
typedef  int /*<<< orphan*/  MCode ;
typedef  TYPE_1__ ASMState ;

/* Variables and functions */
 int JIT_F_LEA_AGU ; 
 scalar_t__ LJ_64 ; 
 int /*<<< orphan*/  XI_NOP ; 

__attribute__((used)) static void asm_tail_prep(ASMState *as)
{
  MCode *p = as->mctop;
  /* Realign and leave room for backwards loop branch or exit branch. */
  if (as->realign) {
    int i = ((int)(intptr_t)as->realign) & 15;
    /* Fill unused mcode tail with NOPs to make the prefetcher happy. */
    while (i-- > 0)
      *--p = XI_NOP;
    as->mctop = p;
    p -= (as->loopinv ? 5 : 2);  /* Space for short/near jmp. */
  } else {
    p -= 5;  /* Space for exit branch (near jmp). */
  }
  if (as->loopref) {
    as->invmcp = as->mcp = p;
  } else {
    /* Leave room for ESP adjustment: add esp, imm or lea esp, [esp+imm] */
    as->mcp = p - (((as->flags & JIT_F_LEA_AGU) ? 7 : 6)  + (LJ_64 ? 1 : 0));
    as->invmcp = NULL;
  }
}