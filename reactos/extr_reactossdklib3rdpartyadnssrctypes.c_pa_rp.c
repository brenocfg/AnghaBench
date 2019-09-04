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
typedef  int /*<<< orphan*/  parseinfo ;
typedef  scalar_t__ adns_status ;
struct TYPE_2__ {int /*<<< orphan*/ * array; } ;
typedef  TYPE_1__ adns_rr_strpair ;

/* Variables and functions */
 scalar_t__ adns_s_invaliddata ; 
 scalar_t__ adns_s_ok ; 
 scalar_t__ pap_domain (int /*<<< orphan*/  const*,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pap_mailbox (int /*<<< orphan*/  const*,int*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_quoteok ; 

__attribute__((used)) static adns_status pa_rp(const parseinfo *pai, int cbyte, int max, void *datap) {
  adns_rr_strpair *rrp= datap;
  adns_status st;

  st= pap_mailbox(pai, &cbyte, max, &rrp->array[0]);
  if (st) return st;

  st= pap_domain(pai, &cbyte, max, &rrp->array[1], pdf_quoteok);
  if (st) return st;

  if (cbyte != max) return adns_s_invaliddata;
  return adns_s_ok;
}