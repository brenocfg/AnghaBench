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
struct TYPE_6__ {TYPE_1__* qu; } ;
typedef  TYPE_2__ parseinfo ;
typedef  scalar_t__ adns_status ;
struct TYPE_5__ {int flags; } ;

/* Variables and functions */
 int adns_qf_quoteok_anshost ; 
 scalar_t__ adns_s_invaliddata ; 
 scalar_t__ adns_s_ok ; 
 scalar_t__ pap_domain (TYPE_2__ const*,int*,int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_quoteok ; 

__attribute__((used)) static adns_status pa_host_raw(const parseinfo *pai, int cbyte, int max, void *datap) {
  char **rrp= datap;
  adns_status st;

  st= pap_domain(pai, &cbyte, max, rrp,
		 pai->qu->flags & adns_qf_quoteok_anshost ? pdf_quoteok : 0);
  if (st) return st;

  if (cbyte != max) return adns_s_invaliddata;
  return adns_s_ok;
}