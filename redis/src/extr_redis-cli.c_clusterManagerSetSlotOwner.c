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
typedef  int /*<<< orphan*/  clusterManagerNode ;

/* Variables and functions */
 int /*<<< orphan*/  clusterManagerAddSlot (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  clusterManagerBumpEpoch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clusterManagerClearSlotStatus (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  clusterManagerDelSlot (int /*<<< orphan*/ *,int,int) ; 
 int clusterManagerExecTransaction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterManagerOnSetOwnerErr ; 
 int clusterManagerStartTransaction (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int clusterManagerSetSlotOwner(clusterManagerNode *owner,
                                      int slot,
                                      int do_clear)
{
    int success = clusterManagerStartTransaction(owner);
    if (!success) return 0;
    /* Ensure the slot is not already assigned. */
    clusterManagerDelSlot(owner, slot, 1);
    /* Add the slot and bump epoch. */
    clusterManagerAddSlot(owner, slot);
    if (do_clear) clusterManagerClearSlotStatus(owner, slot);
    clusterManagerBumpEpoch(owner);
    success = clusterManagerExecTransaction(owner, clusterManagerOnSetOwnerErr);
    return success;
}