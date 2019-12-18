#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* L; } ;
typedef  TYPE_2__ jit_State ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_5__ {int /*<<< orphan*/ * base; } ;
typedef  int /*<<< orphan*/  TRef ;
typedef  scalar_t__ IRType ;
typedef  size_t BCReg ;

/* Variables and functions */
 int IRSLOAD_CONVERT ; 
 int IRSLOAD_TYPECHECK ; 
 int /*<<< orphan*/  IRT_GUARD ; 
 scalar_t__ IRT_INT ; 
 int /*<<< orphan*/  sloadt (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int tvisint (int /*<<< orphan*/ *) ; 

__attribute__((used)) static TRef fori_load(jit_State *J, BCReg slot, IRType t, int mode)
{
  int conv = (tvisint(&J->L->base[slot]) != (t==IRT_INT)) ? IRSLOAD_CONVERT : 0;
  return sloadt(J, (int32_t)slot,
		t + (((mode & IRSLOAD_TYPECHECK) ||
		      (conv && t == IRT_INT && !(mode >> 16))) ?
		     IRT_GUARD : 0),
		mode + conv);
}