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
typedef  int /*<<< orphan*/  adns_status ;
struct TYPE_2__ {int i; int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ adns_rr_intstr ;

/* Variables and functions */
 int /*<<< orphan*/  CSP_ADDSTR (char*) ; 
 int /*<<< orphan*/  csp_domain (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static adns_status cs_inthost(vbuf *vb, const void *datap) {
  const adns_rr_intstr *rrp= datap;
  char buf[10];

  sprintf(buf,"%u ",rrp->i);
  CSP_ADDSTR(buf);
  return csp_domain(vb,rrp->str);
}