#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_5__* adns_state ;
struct TYPE_19__ {scalar_t__ len; int /*<<< orphan*/  addr; } ;
typedef  TYPE_6__ adns_rr_addr ;
typedef  TYPE_7__* adns_query ;
struct TYPE_16__ {TYPE_6__* addr; } ;
struct TYPE_21__ {scalar_t__ status; int nrrs; TYPE_3__ rrs; } ;
typedef  TYPE_8__ adns_answer ;
struct TYPE_17__ {int /*<<< orphan*/  head; } ;
struct TYPE_14__ {TYPE_6__ ptr_parent_addr; } ;
struct TYPE_15__ {TYPE_1__ info; } ;
struct TYPE_20__ {TYPE_4__ children; TYPE_2__ ctx; TYPE_5__* ads; TYPE_8__* answer; } ;
struct TYPE_18__ {int /*<<< orphan*/  childw; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_LINK_TAIL (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  adns__query_done (TYPE_7__*) ; 
 int /*<<< orphan*/  adns__query_fail (TYPE_7__*,scalar_t__) ; 
 scalar_t__ adns_s_inconsistent ; 
 scalar_t__ adns_s_nodata ; 
 scalar_t__ adns_s_nxdomain ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void icb_ptr(adns_query parent, adns_query child) {
  adns_answer *cans= child->answer;
  const adns_rr_addr *queried, *found;
  adns_state ads= parent->ads;
  int i;

  if (cans->status == adns_s_nxdomain || cans->status == adns_s_nodata) {
    adns__query_fail(parent,adns_s_inconsistent);
    return;
  } else if (cans->status) {
    adns__query_fail(parent,cans->status);
    return;
  }

  queried= &parent->ctx.info.ptr_parent_addr;
  for (i=0, found=cans->rrs.addr; i<cans->nrrs; i++, found++) {
    if (queried->len == found->len &&
	!memcmp(&queried->addr,&found->addr,(size_t) queried->len)) {
      if (!parent->children.head) {
	adns__query_done(parent);
	return;
      } else {
	LIST_LINK_TAIL(ads->childw,parent);
	return;
      }
    }
  }

  adns__query_fail(parent,adns_s_inconsistent);
}