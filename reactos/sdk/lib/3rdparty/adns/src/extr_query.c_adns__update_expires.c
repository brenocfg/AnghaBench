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
typedef  scalar_t__ time_t ;
struct timeval {scalar_t__ tv_sec; } ;
typedef  TYPE_1__* adns_query ;
struct TYPE_3__ {scalar_t__ expires; } ;

/* Variables and functions */
 unsigned long MAXTTLBELIEVE ; 
 int /*<<< orphan*/  assert (int) ; 

void adns__update_expires(adns_query qu, unsigned long ttl, struct timeval now) {
  time_t max;

  assert(ttl <= MAXTTLBELIEVE);
  max= now.tv_sec + ttl;
  if (qu->expires < max) return;
  qu->expires= max;
}