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
typedef  int /*<<< orphan*/  adns_query ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_ROUND (size_t) ; 
 void* alloc_common (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void *adns__alloc_mine(adns_query qu, size_t sz) {
  return alloc_common(qu,MEM_ROUND(sz));
}