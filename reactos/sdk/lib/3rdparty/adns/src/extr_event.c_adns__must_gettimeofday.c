#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  adns_state ;

/* Variables and functions */
 int /*<<< orphan*/  adns__diag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adns_globalsystemfailure (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int gettimeofday (struct timeval*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void adns__must_gettimeofday(adns_state ads, const struct timeval **now_io,
			     struct timeval *tv_buf) {
  const struct timeval *now;
  int r;

  now= *now_io;
  if (now) return;
  r= gettimeofday(tv_buf,0); if (!r) { *now_io= tv_buf; return; }
  adns__diag(ads,-1,0,"gettimeofday failed: %s",strerror(errno));
  adns_globalsystemfailure(ads);
  return;
}