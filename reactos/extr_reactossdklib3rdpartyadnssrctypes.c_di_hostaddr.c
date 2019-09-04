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
typedef  int /*<<< orphan*/  adns_rr_hostaddr ;

/* Variables and functions */
 int dip_hostaddr (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int di_hostaddr(adns_state ads, const void *datap_a, const void *datap_b) {
  const adns_rr_hostaddr *ap= datap_a, *bp= datap_b;

  return dip_hostaddr(ads, ap,bp);
}