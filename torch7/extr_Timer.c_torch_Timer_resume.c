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
struct TYPE_3__ {int isRunning; int /*<<< orphan*/  startsystime; int /*<<< orphan*/  startusertime; int /*<<< orphan*/  startrealtime; } ;
typedef  TYPE_1__ Timer ;

/* Variables and functions */
 TYPE_1__* luaT_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  torch_Timer_realtime () ; 
 int /*<<< orphan*/  torch_Timer_systime () ; 
 int /*<<< orphan*/  torch_Timer_usertime () ; 

__attribute__((used)) static int torch_Timer_resume(lua_State *L)
{
  Timer *timer = luaT_checkudata(L, 1, "torch.Timer");
  if(!timer->isRunning)
  {
    timer->isRunning = 1;
    timer->startrealtime = torch_Timer_realtime();
    timer->startusertime = torch_Timer_usertime();
    timer->startsystime = torch_Timer_systime();
  }
  lua_settop(L, 1);
  return 1;  
}