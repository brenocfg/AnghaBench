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
typedef  int MountState ;

/* Variables and functions */
 int KILL_KILL ; 
 int KILL_RESTART ; 
 int KILL_TERMINATE ; 
#define  MOUNT_REMOUNTING_SIGKILL 131 
#define  MOUNT_REMOUNTING_SIGTERM 130 
#define  MOUNT_UNMOUNTING_SIGKILL 129 
#define  MOUNT_UNMOUNTING_SIGTERM 128 
 int _KILL_OPERATION_INVALID ; 

__attribute__((used)) static int state_to_kill_operation(MountState state) {
        switch (state) {

        case MOUNT_REMOUNTING_SIGTERM:
                return KILL_RESTART;

        case MOUNT_UNMOUNTING_SIGTERM:
                return KILL_TERMINATE;

        case MOUNT_REMOUNTING_SIGKILL:
        case MOUNT_UNMOUNTING_SIGKILL:
                return KILL_KILL;

        default:
                return _KILL_OPERATION_INVALID;
        }
}