#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ used; scalar_t__ avail; } ;
typedef  TYPE_1__ vbuf ;
typedef  int /*<<< orphan*/  byte ;
typedef  int /*<<< orphan*/  adns_status ;
typedef  int adns_rrtype ;

/* Variables and functions */
 int DNS_CLASS_IN ; 
 int /*<<< orphan*/  MKQUERY_ADDW (int) ; 
 int /*<<< orphan*/  MKQUERY_START (TYPE_1__*) ; 
 int /*<<< orphan*/  MKQUERY_STOP (TYPE_1__*) ; 
 int adns__rrt_typemask ; 
 int /*<<< orphan*/  adns_s_ok ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static adns_status mkquery_footer(vbuf *vb, adns_rrtype type) {
  byte *rqp;

  MKQUERY_START(vb);
  MKQUERY_ADDW(type & adns__rrt_typemask); /* QTYPE */
  MKQUERY_ADDW(DNS_CLASS_IN); /* QCLASS=IN */
  MKQUERY_STOP(vb);
  assert(vb->used <= vb->avail);

  return adns_s_ok;
}