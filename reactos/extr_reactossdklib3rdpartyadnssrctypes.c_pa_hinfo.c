#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  parseinfo ;
typedef  scalar_t__ adns_status ;
struct TYPE_4__ {TYPE_1__* array; } ;
typedef  TYPE_2__ adns_rr_intstrpair ;
struct TYPE_3__ {int /*<<< orphan*/  str; int /*<<< orphan*/  i; } ;

/* Variables and functions */
 scalar_t__ adns_s_invaliddata ; 
 scalar_t__ adns_s_ok ; 
 scalar_t__ pap_qstring (int /*<<< orphan*/  const*,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static adns_status pa_hinfo(const parseinfo *pai, int cbyte, int max, void *datap) {
  adns_rr_intstrpair *rrp= datap;
  adns_status st;
  int i;

  for (i=0; i<2; i++) {
    st= pap_qstring(pai, &cbyte, max, &rrp->array[i].i, &rrp->array[i].str);
    if (st) return st;
  }

  if (cbyte != max) return adns_s_invaliddata;

  return adns_s_ok;
}