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
typedef  int /*<<< orphan*/  vbuf ;
struct in_addr {int dummy; } ;
typedef  int /*<<< orphan*/  adns_status ;

/* Variables and functions */
 int /*<<< orphan*/  CSP_ADDSTR (char const*) ; 
 int /*<<< orphan*/  adns_s_ok ; 
 int /*<<< orphan*/  assert (char const*) ; 
 char* inet_ntoa (struct in_addr const) ; 

__attribute__((used)) static adns_status cs_inaddr(vbuf *vb, const void *datap) {
  const struct in_addr *rrp= datap, rr= *rrp;
  const char *ia;

  ia= inet_ntoa(rr); assert(ia);
  CSP_ADDSTR(ia);
  return adns_s_ok;
}