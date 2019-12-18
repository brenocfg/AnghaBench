#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sigaction {int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; int /*<<< orphan*/  sa_flags; } ;
struct TYPE_6__ {int tv_sec; int tv_usec; } ;
struct TYPE_5__ {int tv_sec; int tv_usec; } ;
struct itimerval {TYPE_2__ it_interval; TYPE_1__ it_value; } ;
struct TYPE_7__ {int interval; int /*<<< orphan*/  oldsa; } ;
typedef  TYPE_3__ ProfileState ;

/* Variables and functions */
 int /*<<< orphan*/  ITIMER_PROF ; 
 int /*<<< orphan*/  SA_RESTART ; 
 int /*<<< orphan*/  SIGPROF ; 
 int /*<<< orphan*/  profile_signal ; 
 int /*<<< orphan*/  setitimer (int /*<<< orphan*/ ,struct itimerval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void profile_timer_start(ProfileState *ps)
{
  int interval = ps->interval;
  struct itimerval tm;
  struct sigaction sa;
  tm.it_value.tv_sec = tm.it_interval.tv_sec = interval / 1000;
  tm.it_value.tv_usec = tm.it_interval.tv_usec = (interval % 1000) * 1000;
  setitimer(ITIMER_PROF, &tm, NULL);
  sa.sa_flags = SA_RESTART;
  sa.sa_handler = profile_signal;
  sigemptyset(&sa.sa_mask);
  sigaction(SIGPROF, &sa, &ps->oldsa);
}