#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vbuf ;
typedef  int /*<<< orphan*/  typeinfo ;
struct timeval {int dummy; } ;
typedef  scalar_t__ adns_status ;
typedef  int /*<<< orphan*/  adns_state ;
typedef  int adns_queryflags ;
typedef  TYPE_1__* adns_query ;
struct TYPE_6__ {int /*<<< orphan*/  vb; } ;

/* Variables and functions */
 scalar_t__ adns__mkquery (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,char const*,int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  adns__query_fail (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  adns__search_next (int /*<<< orphan*/ ,TYPE_1__*,struct timeval) ; 
 int /*<<< orphan*/  adns__vbuf_init (int /*<<< orphan*/ *) ; 
 int adns_qf_search ; 
 scalar_t__ adns_s_querydomaintoolong ; 
 int /*<<< orphan*/  query_submit (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int,struct timeval) ; 

__attribute__((used)) static void query_simple(adns_state ads, adns_query qu,
			 const char *owner, int ol,
			 const typeinfo *typei, adns_queryflags flags,
			 struct timeval now) {
  vbuf vb_new;
  int id;
  adns_status stat;

  stat= adns__mkquery(ads,&qu->vb,&id, owner,ol, typei,flags);
  if (stat) {
    if (stat == adns_s_querydomaintoolong && (flags & adns_qf_search)) {
      adns__search_next(ads,qu,now);
      return;
    } else {
      adns__query_fail(qu,stat);
      return;
    }
  }

  vb_new= qu->vb;
  adns__vbuf_init(&qu->vb);
  query_submit(ads,qu, typei,&vb_new,id, flags,now);
}