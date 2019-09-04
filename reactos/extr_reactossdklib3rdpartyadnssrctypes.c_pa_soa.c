#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* qu; int /*<<< orphan*/ * dgram; } ;
typedef  TYPE_2__ parseinfo ;
typedef  int /*<<< orphan*/  byte ;
typedef  scalar_t__ adns_status ;
struct TYPE_9__ {int serial; int /*<<< orphan*/  rname; int /*<<< orphan*/  mname; } ;
typedef  TYPE_3__ adns_rr_soa ;
struct TYPE_7__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_W (int,int) ; 
 int adns_qf_quoteok_anshost ; 
 scalar_t__ adns_s_invaliddata ; 
 scalar_t__ adns_s_ok ; 
 scalar_t__ pap_domain (TYPE_2__ const*,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pap_mailbox (TYPE_2__ const*,int*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_quoteok ; 

__attribute__((used)) static adns_status pa_soa(const parseinfo *pai, int cbyte, int max, void *datap) {
  adns_rr_soa *rrp= datap;
  const byte *dgram= pai->dgram;
  adns_status st;
  int msw, lsw, i;

  st= pap_domain(pai, &cbyte, max, &rrp->mname,
		 pai->qu->flags & adns_qf_quoteok_anshost ? pdf_quoteok : 0);
  if (st) return st;

  st= pap_mailbox(pai, &cbyte, max, &rrp->rname);
  if (st) return st;

  if (cbyte+20 != max) return adns_s_invaliddata;

  for (i=0; i<5; i++) {
    GET_W(cbyte,msw);
    GET_W(cbyte,lsw);
    (&rrp->serial)[i]= (msw<<16) | lsw;
  }

  return adns_s_ok;
}