#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int type; size_t len; } ;
typedef  TYPE_1__ RedisModuleCallReply ;

/* Variables and functions */
#define  REDISMODULE_REPLY_ARRAY 130 
#define  REDISMODULE_REPLY_ERROR 129 
#define  REDISMODULE_REPLY_STRING 128 
 int /*<<< orphan*/  moduleParseCallReply (TYPE_1__*) ; 

size_t RM_CallReplyLength(RedisModuleCallReply *reply) {
    moduleParseCallReply(reply);
    switch(reply->type) {
    case REDISMODULE_REPLY_STRING:
    case REDISMODULE_REPLY_ERROR:
    case REDISMODULE_REPLY_ARRAY:
        return reply->len;
    default:
        return 0;
    }
}