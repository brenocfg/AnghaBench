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
typedef  int /*<<< orphan*/  MountState ;

/* Variables and functions */
 int IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MOUNT_CLEANING ; 
 int /*<<< orphan*/  MOUNT_MOUNTING ; 
 int /*<<< orphan*/  MOUNT_MOUNTING_DONE ; 
 int /*<<< orphan*/  MOUNT_REMOUNTING ; 
 int /*<<< orphan*/  MOUNT_REMOUNTING_SIGKILL ; 
 int /*<<< orphan*/  MOUNT_REMOUNTING_SIGTERM ; 
 int /*<<< orphan*/  MOUNT_UNMOUNTING ; 
 int /*<<< orphan*/  MOUNT_UNMOUNTING_SIGKILL ; 
 int /*<<< orphan*/  MOUNT_UNMOUNTING_SIGTERM ; 

__attribute__((used)) static bool MOUNT_STATE_WITH_PROCESS(MountState state) {
        return IN_SET(state,
                      MOUNT_MOUNTING,
                      MOUNT_MOUNTING_DONE,
                      MOUNT_REMOUNTING,
                      MOUNT_REMOUNTING_SIGTERM,
                      MOUNT_REMOUNTING_SIGKILL,
                      MOUNT_UNMOUNTING,
                      MOUNT_UNMOUNTING_SIGTERM,
                      MOUNT_UNMOUNTING_SIGKILL,
                      MOUNT_CLEANING);
}