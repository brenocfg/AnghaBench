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
struct TYPE_4__ {int /*<<< orphan*/  ll; } ;
struct TYPE_5__ {char* proto; int protolen; int /*<<< orphan*/  type; TYPE_1__ val; } ;
typedef  TYPE_2__ RedisModuleCallReply ;

/* Variables and functions */
 int /*<<< orphan*/  REDISMODULE_REPLY_INTEGER ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  string2ll (char*,int,int /*<<< orphan*/ *) ; 

void moduleParseCallReply_Int(RedisModuleCallReply *reply) {
    char *proto = reply->proto;
    char *p = strchr(proto+1,'\r');

    string2ll(proto+1,p-proto-1,&reply->val.ll);
    reply->protolen = p-proto+2;
    reply->type = REDISMODULE_REPLY_INTEGER;
}