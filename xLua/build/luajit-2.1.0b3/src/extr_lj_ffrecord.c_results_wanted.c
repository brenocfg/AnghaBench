#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ptrdiff_t ;
struct TYPE_5__ {TYPE_1__* L; } ;
typedef  TYPE_2__ jit_State ;
struct TYPE_4__ {int /*<<< orphan*/ * base; } ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
 scalar_t__ bc_b (int /*<<< orphan*/ ) ; 
 scalar_t__ frame_islua (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * frame_pc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ptrdiff_t results_wanted(jit_State *J)
{
  TValue *frame = J->L->base-1;
  if (frame_islua(frame))
    return (ptrdiff_t)bc_b(frame_pc(frame)[-1]) - 1;
  else
    return -1;
}