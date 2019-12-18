#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int type; } ;
typedef  TYPE_1__ RedisModuleCallReply ;

/* Variables and functions */
 int REDISMODULE_REPLY_UNKNOWN ; 

int RM_CallReplyType(RedisModuleCallReply *reply) {
    if (!reply) return REDISMODULE_REPLY_UNKNOWN;
    return reply->type;
}