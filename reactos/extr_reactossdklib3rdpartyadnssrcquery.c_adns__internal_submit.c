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
typedef  int /*<<< orphan*/  vbuf ;
typedef  int /*<<< orphan*/  typeinfo ;
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  qcontext ;
typedef  int /*<<< orphan*/  adns_status ;
typedef  int /*<<< orphan*/  adns_state ;
typedef  int /*<<< orphan*/  adns_queryflags ;
typedef  TYPE_1__* adns_query ;
struct TYPE_5__ {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  adns__vbuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adns_s_nomemory ; 
 int /*<<< orphan*/  adns_s_ok ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 TYPE_1__* query_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,struct timeval) ; 
 int /*<<< orphan*/  query_submit (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct timeval) ; 

adns_status adns__internal_submit(adns_state ads, adns_query *query_r,
				  const typeinfo *typei, vbuf *qumsg_vb, int id,
				  adns_queryflags flags, struct timeval now,
				  const qcontext *ctx) {
  adns_query qu;

  qu= query_alloc(ads,typei,flags,now);
  if (!qu) { adns__vbuf_free(qumsg_vb); return adns_s_nomemory; }
  *query_r= qu;

  memcpy(&qu->ctx,ctx,(size_t) sizeof(qu->ctx));
  query_submit(ads,qu, typei,qumsg_vb,id,flags,now);

  return adns_s_ok;
}