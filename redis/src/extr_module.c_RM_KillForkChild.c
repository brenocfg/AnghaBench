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
 scalar_t__ C_OK ; 
 int REDISMODULE_ERR ; 
 int REDISMODULE_OK ; 
 scalar_t__ TerminateModuleForkChild (int,int) ; 

int RM_KillForkChild(int child_pid) {
    /* Kill module child, wait for child exit. */
    if (TerminateModuleForkChild(child_pid,1) == C_OK)
        return REDISMODULE_OK;
    else
        return REDISMODULE_ERR;
}