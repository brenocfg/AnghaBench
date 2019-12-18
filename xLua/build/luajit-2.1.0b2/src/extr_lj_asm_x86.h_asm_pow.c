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
 int /*<<< orphan*/  IRCALL_lj_carith_powi64 ; 
 int /*<<< orphan*/  IRCALL_lj_carith_powu64 ; 
 int /*<<< orphan*/  asm_callid (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asm_fppowi (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ irt_isi64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irt_isnum (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asm_pow(ASMState *as, IRIns *ir)
{
#if LJ_64 && LJ_HASFFI
  if (!irt_isnum(ir->t))
    asm_callid(as, ir, irt_isi64(ir->t) ? IRCALL_lj_carith_powi64 :
					  IRCALL_lj_carith_powu64);
  else
#endif
    asm_fppowi(as, ir);
}