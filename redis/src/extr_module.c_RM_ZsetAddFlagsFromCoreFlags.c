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
 int REDISMODULE_ZADD_ADDED ; 
 int REDISMODULE_ZADD_NOP ; 
 int REDISMODULE_ZADD_UPDATED ; 
 int ZADD_ADDED ; 
 int ZADD_NOP ; 
 int ZADD_UPDATED ; 

int RM_ZsetAddFlagsFromCoreFlags(int flags) {
    int retflags = 0;
    if (flags & ZADD_ADDED) retflags |= REDISMODULE_ZADD_ADDED;
    if (flags & ZADD_UPDATED) retflags |= REDISMODULE_ZADD_UPDATED;
    if (flags & ZADD_NOP) retflags |= REDISMODULE_ZADD_NOP;
    return retflags;
}