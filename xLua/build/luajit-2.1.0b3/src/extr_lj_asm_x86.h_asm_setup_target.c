#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ base; } ;
struct TYPE_8__ {TYPE_2__ mrm; TYPE_1__* T; } ;
struct TYPE_6__ {int /*<<< orphan*/  nsnap; } ;
typedef  TYPE_3__ ASMState ;

/* Variables and functions */
 int /*<<< orphan*/  asm_exitstub_setup (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asm_setup_target(ASMState *as)
{
  asm_exitstub_setup(as, as->T->nsnap);
  as->mrm.base = 0;
}