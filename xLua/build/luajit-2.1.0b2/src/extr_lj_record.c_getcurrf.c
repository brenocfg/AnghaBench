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
struct TYPE_4__ {int baseslot; scalar_t__* base; } ;
typedef  TYPE_1__ jit_State ;
typedef  scalar_t__ TRef ;

/* Variables and functions */
 int /*<<< orphan*/  IRSLOAD_READONLY ; 
 int /*<<< orphan*/  IRT_FUNC ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 scalar_t__ sloadt (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static TRef getcurrf(jit_State *J)
{
  if (J->base[-1])
    return J->base[-1];
  lua_assert(J->baseslot == 1);
  return sloadt(J, -1, IRT_FUNC, IRSLOAD_READONLY);
}