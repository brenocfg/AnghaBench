#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  FuncState ;
typedef  int /*<<< orphan*/  BCReg ;
typedef  scalar_t__ BCPos ;

/* Variables and functions */
 scalar_t__ NO_JMP ; 
 scalar_t__ jmp_next (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  jmp_patchins (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ jmp_patchtestreg (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jmp_patchval(FuncState *fs, BCPos list, BCPos vtarget,
			 BCReg reg, BCPos dtarget)
{
  while (list != NO_JMP) {
    BCPos next = jmp_next(fs, list);
    if (jmp_patchtestreg(fs, list, reg))
      jmp_patchins(fs, list, vtarget);  /* Jump to target with value. */
    else
      jmp_patchins(fs, list, dtarget);  /* Jump to default target. */
    list = next;
  }
}