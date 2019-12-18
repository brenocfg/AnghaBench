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
 int /*<<< orphan*/  adns__timeouts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval**,struct timeval*,struct timeval) ; 
 int /*<<< orphan*/  cc_entex ; 

void adns_firsttimeout(adns_state ads,
		       struct timeval **tv_io, struct timeval *tvbuf,
		       struct timeval now) {
  adns__consistency(ads,0,cc_entex);
  adns__timeouts(ads, 0, tv_io,tvbuf, now);
  adns__consistency(ads,0,cc_entex);
}