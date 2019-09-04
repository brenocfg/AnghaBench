#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vbuf ;
typedef  scalar_t__ adns_status ;
struct TYPE_3__ {int astatus; int naddrs; int /*<<< orphan*/ * addrs; int /*<<< orphan*/  host; } ;
typedef  TYPE_1__ adns_rr_hostaddr ;

/* Variables and functions */
 int /*<<< orphan*/  CSP_ADDSTR (char*) ; 
 char* adns_errabbrev (int) ; 
 char* adns_errtypeabbrev (int) ; 
 scalar_t__ adns_s_ok ; 
 char* adns_strerror (int) ; 
 scalar_t__ csp_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ csp_domain (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ csp_qstring (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static adns_status csp_hostaddr(vbuf *vb, const adns_rr_hostaddr *rrp) {
  const char *errstr;
  adns_status st;
  char buf[20];
  int i;

  st= csp_domain(vb,rrp->host);  if (st) return st;

  CSP_ADDSTR(" ");
  CSP_ADDSTR(adns_errtypeabbrev(rrp->astatus));

  sprintf(buf," %d ",rrp->astatus);
  CSP_ADDSTR(buf);

  CSP_ADDSTR(adns_errabbrev(rrp->astatus));
  CSP_ADDSTR(" ");

  errstr= adns_strerror(rrp->astatus);
  st= csp_qstring(vb,errstr,(int)strlen(errstr));  if (st) return st;

  if (rrp->naddrs >= 0) {
    CSP_ADDSTR(" (");
    for (i=0; i<rrp->naddrs; i++) {
      CSP_ADDSTR(" ");
      st= csp_addr(vb,&rrp->addrs[i]);
    }
    CSP_ADDSTR(" )");
  } else {
    CSP_ADDSTR(" ?");
  }
  return adns_s_ok;
}