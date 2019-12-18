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
typedef  int /*<<< orphan*/  RedisModuleString ;

/* Variables and functions */
 int C_OK ; 
 int REDISMODULE_ERR ; 
 int REDISMODULE_OK ; 
 int getDoubleFromObject (int /*<<< orphan*/  const*,double*) ; 

int RM_StringToDouble(const RedisModuleString *str, double *d) {
    int retval = getDoubleFromObject(str,d);
    return (retval == C_OK) ? REDISMODULE_OK : REDISMODULE_ERR;
}