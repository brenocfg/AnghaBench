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
typedef  TYPE_1__* adns_state ;
struct TYPE_3__ {int iflags; int /*<<< orphan*/  stdsigmask; int /*<<< orphan*/  stdsigpipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int adns_if_nosigpipe ; 
 int /*<<< orphan*/  assert (int) ; 
 int sigaction (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void adns__sigpipe_unprotect(adns_state ads) {
#ifndef ADNS_JGAA_WIN32
  int r;

  if (ads->iflags & adns_if_nosigpipe) return;

  r= sigaction(SIGPIPE,&ads->stdsigpipe,0); assert(!r);
  r= sigprocmask(SIG_SETMASK,&ads->stdsigmask,0); assert(!r);
#endif
}