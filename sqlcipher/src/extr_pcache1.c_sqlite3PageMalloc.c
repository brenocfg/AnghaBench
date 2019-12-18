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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 void* pcache1Alloc (int) ; 

void *sqlite3PageMalloc(int sz){
  assert( sz<=65536+8 ); /* These allocations are never very large */
  return pcache1Alloc(sz);
}