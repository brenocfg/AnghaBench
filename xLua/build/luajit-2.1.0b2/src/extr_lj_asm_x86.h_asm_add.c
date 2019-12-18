#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int flags; scalar_t__ flagmcp; scalar_t__ mcp; } ;
struct TYPE_11__ {int /*<<< orphan*/  t; } ;
typedef  TYPE_1__ IRIns ;
typedef  TYPE_2__ ASMState ;

/* Variables and functions */
 int JIT_F_LEA_AGU ; 
 int /*<<< orphan*/  XO_ADDSD ; 
 int /*<<< orphan*/  XOg_ADD ; 
 int /*<<< orphan*/  asm_fparith (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asm_intarith (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asm_lea (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ irt_is64 (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isnum (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asm_add(ASMState *as, IRIns *ir)
{
  if (irt_isnum(ir->t))
    asm_fparith(as, ir, XO_ADDSD);
  else if ((as->flags & JIT_F_LEA_AGU) || as->flagmcp == as->mcp ||
	   irt_is64(ir->t) || !asm_lea(as, ir))
    asm_intarith(as, ir, XOg_ADD);
}