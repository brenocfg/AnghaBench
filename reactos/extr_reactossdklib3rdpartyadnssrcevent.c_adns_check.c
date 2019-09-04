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
typedef  int /*<<< orphan*/  adns_query ;
typedef  int /*<<< orphan*/  adns_answer ;

/* Variables and functions */
 int /*<<< orphan*/  adns__autosys (int /*<<< orphan*/ ,struct timeval) ; 
 int /*<<< orphan*/  adns__consistency (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int adns__internal_check (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,void**) ; 
 int /*<<< orphan*/  cc_entex ; 
 int gettimeofday (struct timeval*,int /*<<< orphan*/ ) ; 

int adns_check(adns_state ads,
	       adns_query *query_io,
	       adns_answer **answer_r,
	       void **context_r) {
  struct timeval now;
  int r;

  adns__consistency(ads,*query_io,cc_entex);
  r= gettimeofday(&now,0);
  if (!r) adns__autosys(ads,now);

  r= adns__internal_check(ads,query_io,answer_r,context_r);
  adns__consistency(ads,0,cc_entex);
  return r;
}