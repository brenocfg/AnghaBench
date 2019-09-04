#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  adns_state ;
struct TYPE_12__ {scalar_t__ astatus; TYPE_4__* addrs; } ;
typedef  TYPE_5__ adns_rr_hostaddr ;
struct TYPE_9__ {int /*<<< orphan*/  sin_addr; } ;
struct TYPE_8__ {scalar_t__ sa_family; } ;
struct TYPE_10__ {TYPE_2__ inet; TYPE_1__ sa; } ;
struct TYPE_11__ {TYPE_3__ addr; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  assert (int) ; 
 int dip_inaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dip_hostaddr(adns_state ads, const adns_rr_hostaddr *ap, const adns_rr_hostaddr *bp) {
  if (ap->astatus != bp->astatus) return ap->astatus;
  if (ap->astatus) return 0;

  assert(ap->addrs[0].addr.sa.sa_family == AF_INET);
  assert(bp->addrs[0].addr.sa.sa_family == AF_INET);
  return dip_inaddr(ads,
		    ap->addrs[0].addr.inet.sin_addr,
		    bp->addrs[0].addr.inet.sin_addr);
}