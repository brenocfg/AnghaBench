#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  rname; int /*<<< orphan*/  mname; } ;
typedef  TYPE_1__ adns_rr_soa ;
typedef  int /*<<< orphan*/  adns_query ;

/* Variables and functions */
 int /*<<< orphan*/  adns__makefinal_str (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mf_soa(adns_query qu, void *datap) {
  adns_rr_soa *rrp= datap;

  adns__makefinal_str(qu,&rrp->mname);
  adns__makefinal_str(qu,&rrp->rname);
}