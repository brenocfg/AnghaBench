#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  t; } ;
typedef  TYPE_1__ IRIns ;
typedef  int /*<<< orphan*/  ASMState ;

/* Variables and functions */
 int /*<<< orphan*/  IRCALL_lj_carith_divi64 ; 
 int /*<<< orphan*/  IRCALL_lj_carith_divu64 ; 
 int /*<<< orphan*/  XO_DIVSD ; 
 int /*<<< orphan*/  asm_callid (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asm_fparith (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isi64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irt_isnum (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asm_div(ASMState *as, IRIns *ir)
{
#if LJ_64 && LJ_HASFFI
  if (!irt_isnum(ir->t))
    asm_callid(as, ir, irt_isi64(ir->t) ? IRCALL_lj_carith_divi64 :
					  IRCALL_lj_carith_divu64);
  else
#endif
    asm_fparith(as, ir, XO_DIVSD);
}