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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {scalar_t__ isRunning; } ;
typedef  TYPE_1__ Timer ;

/* Variables and functions */
 TYPE_1__* luaT_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static int torch_Timer___tostring__(lua_State *L)
{
  Timer *timer = luaT_checkudata(L, 1, "torch.Timer");
  lua_pushfstring(L, "torch.Timer [status: %s]", (timer->isRunning ? "running" : "stopped"));
  return 1;
}