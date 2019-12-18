#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mcprot; int /*<<< orphan*/  szmcarea; int /*<<< orphan*/  mcarea; } ;
typedef  TYPE_1__ jit_State ;

/* Variables and functions */
 scalar_t__ LJ_UNLIKELY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcode_protfail (TYPE_1__*) ; 
 int /*<<< orphan*/  mcode_setprot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mcode_protect(jit_State *J, int prot)
{
  if (J->mcprot != prot) {
    if (LJ_UNLIKELY(mcode_setprot(J->mcarea, J->szmcarea, prot)))
      mcode_protfail(J);
    J->mcprot = prot;
  }
}