#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  hookmask; } ;
struct TYPE_7__ {int /*<<< orphan*/  J; } ;
typedef  int /*<<< orphan*/  IRIns ;
typedef  TYPE_1__ ASMState ;

/* Variables and functions */
 int /*<<< orphan*/  CC_NE ; 
 int /*<<< orphan*/  HOOK_PROFILE ; 
 TYPE_6__* J2G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XO_GROUP3b ; 
 int /*<<< orphan*/  XOg_TEST ; 
 int /*<<< orphan*/  asm_guardcc (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_i8 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_rma (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void asm_prof(ASMState *as, IRIns *ir)
{
  UNUSED(ir);
  asm_guardcc(as, CC_NE);
  emit_i8(as, HOOK_PROFILE);
  emit_rma(as, XO_GROUP3b, XOg_TEST, &J2G(as->J)->hookmask);
}