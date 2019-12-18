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
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ jit_State ;
typedef  int /*<<< orphan*/  cTValue ;

/* Variables and functions */
 int JIT_F_OPT_NARROW ; 
 scalar_t__ LJ_DUALNUM ; 
 int /*<<< orphan*/  numV (int /*<<< orphan*/ *) ; 
 int numisint (int /*<<< orphan*/ ) ; 
 scalar_t__ tvisint (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int narrow_forl(jit_State *J, cTValue *o)
{
  if (tvisint(o)) return 1;
  if (LJ_DUALNUM || (J->flags & JIT_F_OPT_NARROW)) return numisint(numV(o));
  return 0;
}