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
typedef  int /*<<< orphan*/  parseinfo ;
typedef  scalar_t__ adns_status ;
typedef  int /*<<< orphan*/  adns_rr_hostaddr ;

/* Variables and functions */
 scalar_t__ adns_s_invaliddata ; 
 scalar_t__ adns_s_ok ; 
 scalar_t__ pap_hostaddr (int /*<<< orphan*/  const*,int*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static adns_status pa_hostaddr(const parseinfo *pai, int cbyte, int max, void *datap) {
  adns_rr_hostaddr *rrp= datap;
  adns_status st;

  st= pap_hostaddr(pai, &cbyte, max, rrp);
  if (st) return st;
  if (cbyte != max) return adns_s_invaliddata;

  return adns_s_ok;
}