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
typedef  scalar_t__ BCPos ;

/* Variables and functions */
 scalar_t__ NO_JMP ; 
 int /*<<< orphan*/  NO_REG ; 
 scalar_t__ jmp_next (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  jmp_patchtestreg (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jmp_dropval(FuncState *fs, BCPos list)
{
  for (; list != NO_JMP; list = jmp_next(fs, list))
    jmp_patchtestreg(fs, list, NO_REG);
}