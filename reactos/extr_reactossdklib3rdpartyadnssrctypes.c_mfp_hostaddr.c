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
struct TYPE_3__ {int naddrs; void* addrs; int /*<<< orphan*/  host; } ;
typedef  TYPE_1__ adns_rr_hostaddr ;
typedef  int /*<<< orphan*/  adns_query ;

/* Variables and functions */
 int /*<<< orphan*/  adns__makefinal_block (int /*<<< orphan*/ ,void**,int) ; 
 int /*<<< orphan*/  adns__makefinal_str (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mfp_hostaddr(adns_query qu, adns_rr_hostaddr *rrp) {
  void *tablev;

  adns__makefinal_str(qu,&rrp->host);
  tablev= rrp->addrs;
  adns__makefinal_block(qu, &tablev, rrp->naddrs*sizeof(*rrp->addrs));
  rrp->addrs= tablev;
}