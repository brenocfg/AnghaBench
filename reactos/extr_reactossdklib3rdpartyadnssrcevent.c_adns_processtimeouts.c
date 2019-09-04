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
 int /*<<< orphan*/  adns__consistency (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adns__must_gettimeofday (int /*<<< orphan*/ ,struct timeval const**,struct timeval*) ; 
 int /*<<< orphan*/  adns__timeouts (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval const) ; 
 int /*<<< orphan*/  cc_entex ; 

void adns_processtimeouts(adns_state ads, const struct timeval *now) {
  struct timeval tv_buf;

  adns__consistency(ads,0,cc_entex);
  adns__must_gettimeofday(ads,&now,&tv_buf);
  if (now) adns__timeouts(ads, 1, 0,0, *now);
  adns__consistency(ads,0,cc_entex);
}