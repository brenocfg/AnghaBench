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
typedef  int /*<<< orphan*/  IRRef ;
typedef  int /*<<< orphan*/  IRIns ;
typedef  int /*<<< orphan*/  CCallInfo ;
typedef  int /*<<< orphan*/  ASMState ;

/* Variables and functions */
 size_t IRCALL_pow ; 
 int /*<<< orphan*/  asm_gencall (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asm_setupresult (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * lj_ir_callinfo ; 

__attribute__((used)) static void asm_fppow(ASMState *as, IRIns *ir, IRRef lref, IRRef rref)
{
  const CCallInfo *ci = &lj_ir_callinfo[IRCALL_pow];
  IRRef args[2];
  args[0] = lref;
  args[1] = rref;
  asm_setupresult(as, ir, ci);
  asm_gencall(as, ci, args);
}