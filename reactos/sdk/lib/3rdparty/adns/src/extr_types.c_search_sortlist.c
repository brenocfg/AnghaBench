#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int s_addr; } ;
struct TYPE_5__ {int s_addr; } ;
struct sortlist {TYPE_2__ base; TYPE_1__ mask; } ;
struct in_addr {int s_addr; } ;
typedef  TYPE_3__* adns_state ;
struct TYPE_7__ {int nsortlist; struct sortlist* sortlist; } ;

/* Variables and functions */

__attribute__((used)) static int search_sortlist(adns_state ads, struct in_addr ad) {
  const struct sortlist *slp;
  int i;

  for (i=0, slp=ads->sortlist;
       i<ads->nsortlist && !((ad.s_addr & slp->mask.s_addr) == slp->base.s_addr);
       i++, slp++);
  return i;
}