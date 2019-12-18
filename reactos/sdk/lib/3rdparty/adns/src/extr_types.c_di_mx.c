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
typedef  int /*<<< orphan*/  adns_state ;
struct TYPE_2__ {scalar_t__ i; int /*<<< orphan*/  ha; } ;
typedef  TYPE_1__ adns_rr_inthostaddr ;

/* Variables and functions */
 int dip_hostaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int di_mx(adns_state ads, const void *datap_a, const void *datap_b) {
  const adns_rr_inthostaddr *ap= datap_a, *bp= datap_b;

  if (ap->i < bp->i) return 0;
  if (ap->i > bp->i) return 1;
  return dip_hostaddr(ads, &ap->ha, &bp->ha);
}