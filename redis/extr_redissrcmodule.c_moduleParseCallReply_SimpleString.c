#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* str; } ;
struct TYPE_5__ {char* proto; int len; int protolen; int /*<<< orphan*/  type; TYPE_1__ val; } ;
typedef  TYPE_2__ RedisModuleCallReply ;

/* Variables and functions */
 int /*<<< orphan*/  REDISMODULE_REPLY_ERROR ; 
 int /*<<< orphan*/  REDISMODULE_REPLY_STRING ; 
 char* strchr (char*,char) ; 

void moduleParseCallReply_SimpleString(RedisModuleCallReply *reply) {
    char *proto = reply->proto;
    char *p = strchr(proto+1,'\r');

    reply->val.str = proto+1;
    reply->len = p-proto-1;
    reply->protolen = p-proto+2;
    reply->type = proto[0] == '+' ? REDISMODULE_REPLY_STRING :
                                    REDISMODULE_REPLY_ERROR;
}