#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * dgram; } ;
typedef  TYPE_1__ parseinfo ;
typedef  int /*<<< orphan*/  byte ;
typedef  scalar_t__ adns_status ;
struct TYPE_6__ {int i; int /*<<< orphan*/  ha; } ;
typedef  TYPE_2__ adns_rr_inthostaddr ;

/* Variables and functions */
 int /*<<< orphan*/  GET_W (int,int) ; 
 scalar_t__ adns_s_invaliddata ; 
 scalar_t__ adns_s_ok ; 
 scalar_t__ pap_hostaddr (TYPE_1__ const*,int*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static adns_status pa_mx(const parseinfo *pai, int cbyte, int max, void *datap) {
  const byte *dgram= pai->dgram;
  adns_rr_inthostaddr *rrp= datap;
  adns_status st;
  int pref;

  if (cbyte+2 > max) return adns_s_invaliddata;
  GET_W(cbyte,pref);
  rrp->i= pref;
  st= pap_hostaddr(pai, &cbyte, max, &rrp->ha);
  if (st) return st;

  if (cbyte != max) return adns_s_invaliddata;
  return adns_s_ok;
}