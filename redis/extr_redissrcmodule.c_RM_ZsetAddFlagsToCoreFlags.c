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
 int REDISMODULE_ZADD_NX ; 
 int REDISMODULE_ZADD_XX ; 
 int ZADD_NX ; 
 int ZADD_XX ; 

int RM_ZsetAddFlagsToCoreFlags(int flags) {
    int retflags = 0;
    if (flags & REDISMODULE_ZADD_XX) retflags |= ZADD_XX;
    if (flags & REDISMODULE_ZADD_NX) retflags |= ZADD_NX;
    return retflags;
}