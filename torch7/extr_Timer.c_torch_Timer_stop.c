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
struct TYPE_3__ {scalar_t__ isRunning; int /*<<< orphan*/  totalsystime; int /*<<< orphan*/  totalusertime; int /*<<< orphan*/  totalrealtime; scalar_t__ startsystime; scalar_t__ startusertime; scalar_t__ startrealtime; } ;
typedef  TYPE_1__ Timer ;
typedef  scalar_t__ TimeType ;

/* Variables and functions */
 TYPE_1__* luaT_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 scalar_t__ torch_Timer_realtime () ; 
 scalar_t__ torch_Timer_systime () ; 
 scalar_t__ torch_Timer_usertime () ; 

__attribute__((used)) static int torch_Timer_stop(lua_State *L)
{
  Timer *timer = luaT_checkudata(L, 1, "torch.Timer");
  if(timer->isRunning)  
  {
    TimeType realtime = torch_Timer_realtime() - timer->startrealtime;
    TimeType usertime = torch_Timer_usertime() - timer->startusertime;
    TimeType systime = torch_Timer_systime() - timer->startsystime;
    timer->totalrealtime += realtime;
    timer->totalusertime += usertime;
    timer->totalsystime += systime;
    timer->isRunning = 0;
  }
  lua_settop(L, 1);
  return 1;  
}