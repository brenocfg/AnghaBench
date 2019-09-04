#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {long long ll; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__ val; } ;
typedef  TYPE_2__ RedisModuleCallReply ;

/* Variables and functions */
 long long LLONG_MIN ; 
 scalar_t__ REDISMODULE_REPLY_INTEGER ; 
 int /*<<< orphan*/  moduleParseCallReply (TYPE_2__*) ; 

long long RM_CallReplyInteger(RedisModuleCallReply *reply) {
    moduleParseCallReply(reply);
    if (reply->type != REDISMODULE_REPLY_INTEGER) return LLONG_MIN;
    return reply->val.ll;
}