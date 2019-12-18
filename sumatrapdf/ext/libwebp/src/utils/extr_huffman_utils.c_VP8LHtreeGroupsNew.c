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
typedef  int /*<<< orphan*/  HTreeGroup ;

/* Variables and functions */
 int MAX_HTREE_GROUPS ; 
 scalar_t__ WebPSafeMalloc (int,int) ; 
 int /*<<< orphan*/  assert (int) ; 

HTreeGroup* VP8LHtreeGroupsNew(int num_htree_groups) {
  HTreeGroup* const htree_groups =
      (HTreeGroup*)WebPSafeMalloc(num_htree_groups, sizeof(*htree_groups));
  if (htree_groups == NULL) {
    return NULL;
  }
  assert(num_htree_groups <= MAX_HTREE_GROUPS);
  return htree_groups;
}