#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; int* proto; } ;
typedef  TYPE_1__ RedisModuleCallReply ;

/* Variables and functions */
 int REDISMODULE_REPLYFLAG_TOPARSE ; 
 int /*<<< orphan*/  moduleParseCallReply_Array (TYPE_1__*) ; 
 int /*<<< orphan*/  moduleParseCallReply_BulkString (TYPE_1__*) ; 
 int /*<<< orphan*/  moduleParseCallReply_Int (TYPE_1__*) ; 
 int /*<<< orphan*/  moduleParseCallReply_SimpleString (TYPE_1__*) ; 

void moduleParseCallReply(RedisModuleCallReply *reply) {
    if (!(reply->flags & REDISMODULE_REPLYFLAG_TOPARSE)) return;
    reply->flags &= ~REDISMODULE_REPLYFLAG_TOPARSE;

    switch(reply->proto[0]) {
    case ':': moduleParseCallReply_Int(reply); break;
    case '$': moduleParseCallReply_BulkString(reply); break;
    case '-': /* handled by next item. */
    case '+': moduleParseCallReply_SimpleString(reply); break;
    case '*': moduleParseCallReply_Array(reply); break;
    }
}