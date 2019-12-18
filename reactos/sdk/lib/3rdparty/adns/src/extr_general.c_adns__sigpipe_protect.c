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
struct sigaction {scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  TYPE_1__* adns_state ;
struct TYPE_3__ {int iflags; int /*<<< orphan*/  stdsigpipe; int /*<<< orphan*/  stdsigmask; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int adns_if_nosigpipe ; 
 int /*<<< orphan*/  assert (int) ; 
 int sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigdelset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 int sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void adns__sigpipe_protect(adns_state ads) {
#ifndef ADNS_JGAA_WIN32
  sigset_t toblock;
  struct sigaction sa;
  int r;

  if (ads->iflags & adns_if_nosigpipe) return;

  sigfillset(&toblock);
  sigdelset(&toblock,SIGPIPE);

  sa.sa_handler= SIG_IGN;
  sigfillset(&sa.sa_mask);
  sa.sa_flags= 0;

  r= sigprocmask(SIG_SETMASK,&toblock,&ads->stdsigmask); assert(!r);
  r= sigaction(SIGPIPE,&sa,&ads->stdsigpipe); assert(!r);
#endif
}