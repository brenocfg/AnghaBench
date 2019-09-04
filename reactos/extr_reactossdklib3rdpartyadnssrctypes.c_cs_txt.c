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
typedef  int /*<<< orphan*/  vbuf ;
typedef  scalar_t__ adns_status ;
struct TYPE_2__ {scalar_t__ i; int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ adns_rr_intstr ;

/* Variables and functions */
 int /*<<< orphan*/  CSP_ADDSTR (char*) ; 
 scalar_t__ adns_s_ok ; 
 scalar_t__ csp_qstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static adns_status cs_txt(vbuf *vb, const void *datap) {
  const adns_rr_intstr *const *rrp= datap;
  const adns_rr_intstr *current;
  adns_status st;
  int spc;

  for (current= *rrp, spc=0;  current->i >= 0;  current++, spc=1) {
    if (spc) CSP_ADDSTR(" ");
    st= csp_qstring(vb,current->str,current->i); if (st) return st;
  }
  return adns_s_ok;
}