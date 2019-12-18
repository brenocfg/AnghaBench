#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  adns_state ;
struct TYPE_6__ {int /*<<< orphan*/  sin_addr; } ;
struct TYPE_5__ {scalar_t__ sa_family; } ;
struct TYPE_7__ {TYPE_2__ inet; TYPE_1__ sa; } ;
struct TYPE_8__ {TYPE_3__ addr; } ;
typedef  TYPE_4__ adns_rr_addr ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  assert (int) ; 
 int dip_inaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int di_addr(adns_state ads, const void *datap_a, const void *datap_b) {
  const adns_rr_addr *ap= datap_a, *bp= datap_b;

  assert(ap->addr.sa.sa_family == AF_INET);
  return dip_inaddr(ads, ap->addr.inet.sin_addr, bp->addr.inet.sin_addr);
}