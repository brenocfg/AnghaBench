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
typedef  int /*<<< orphan*/  adns_state ;
typedef  int /*<<< orphan*/  adns_rrtype ;
typedef  int /*<<< orphan*/  adns_queryflags ;
typedef  int /*<<< orphan*/  adns_query ;
typedef  int /*<<< orphan*/  adns_answer ;

/* Variables and functions */
 int /*<<< orphan*/  adns_cancel (int /*<<< orphan*/ ) ; 
 int adns_submit (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int adns_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

int adns_synchronous(adns_state ads,
		     const char *owner,
		     adns_rrtype type,
		     adns_queryflags flags,
		     adns_answer **answer_r) {
  adns_query qu;
  int r;

  r= adns_submit(ads,owner,type,flags,0,&qu);
  if (r) return r;

  r= adns_wait(ads,&qu,answer_r,0);
  if (r) adns_cancel(qu);

  return r;
}