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
typedef  int /*<<< orphan*/  adns_status ;

/* Variables and functions */
 int /*<<< orphan*/  CSP_ADDSTR (char const*) ; 
 int /*<<< orphan*/  adns_s_ok ; 

__attribute__((used)) static adns_status csp_domain(vbuf *vb, const char *domain) {
  CSP_ADDSTR(domain);
  if (!*domain) CSP_ADDSTR(".");
  return adns_s_ok;
}