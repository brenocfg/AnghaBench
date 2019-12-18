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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  __int64 ;
struct TYPE_4__ {int isRunning; int /*<<< orphan*/  startsystime; int /*<<< orphan*/  startusertime; int /*<<< orphan*/  startrealtime; scalar_t__ totalsystime; scalar_t__ totalusertime; scalar_t__ totalrealtime; } ;
typedef  TYPE_1__ Timer ;
typedef  int /*<<< orphan*/  LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  QueryPerformanceFrequency (scalar_t__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* luaT_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaT_pushudata (int /*<<< orphan*/ *,TYPE_1__*,char*) ; 
 scalar_t__ ticksPerSecond ; 
 int /*<<< orphan*/  torch_Timer_realtime () ; 
 int /*<<< orphan*/  torch_Timer_systime () ; 
 int /*<<< orphan*/  torch_Timer_usertime () ; 

__attribute__((used)) static int torch_Timer_new(lua_State *L)
{
#ifdef _WIN32
  if (ticksPerSecond == 0)
  {
    assert(sizeof(LARGE_INTEGER) == sizeof(__int64));
    QueryPerformanceFrequency(&ticksPerSecond);
  }
#endif
  Timer *timer = luaT_alloc(L, sizeof(Timer));
  timer->isRunning = 1;
  timer->totalrealtime = 0;
  timer->totalusertime = 0;
  timer->totalsystime = 0;
  timer->startrealtime = torch_Timer_realtime();
  timer->startusertime = torch_Timer_usertime();
  timer->startsystime = torch_Timer_systime();
  luaT_pushudata(L, timer, "torch.Timer");
  return 1;
}