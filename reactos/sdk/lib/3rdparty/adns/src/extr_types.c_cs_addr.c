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
typedef  int /*<<< orphan*/  adns_rr_addr ;

/* Variables and functions */
 int /*<<< orphan*/  csp_addr (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static adns_status cs_addr(vbuf *vb, const void *datap) {
  const adns_rr_addr *rrp= datap;

  return csp_addr(vb,rrp);
}