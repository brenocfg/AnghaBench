#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* array; } ;
struct TYPE_7__ {scalar_t__ type; size_t len; TYPE_1__ val; } ;
typedef  TYPE_2__ RedisModuleCallReply ;

/* Variables and functions */
 scalar_t__ REDISMODULE_REPLY_ARRAY ; 
 int /*<<< orphan*/  moduleParseCallReply (TYPE_2__*) ; 

RedisModuleCallReply *RM_CallReplyArrayElement(RedisModuleCallReply *reply, size_t idx) {
    moduleParseCallReply(reply);
    if (reply->type != REDISMODULE_REPLY_ARRAY) return NULL;
    if (idx >= reply->len) return NULL;
    return reply->val.array+idx;
}