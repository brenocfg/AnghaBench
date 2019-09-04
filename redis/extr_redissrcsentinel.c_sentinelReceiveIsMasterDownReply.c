#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {long long leader_epoch; int /*<<< orphan*/  leader; int /*<<< orphan*/  name; int /*<<< orphan*/  flags; int /*<<< orphan*/  last_master_down_reply_time; } ;
typedef  TYPE_2__ sentinelRedisInstance ;
struct TYPE_9__ {scalar_t__ type; int elements; TYPE_1__** element; } ;
typedef  TYPE_3__ redisReply ;
struct TYPE_10__ {TYPE_5__* data; } ;
typedef  TYPE_4__ redisAsyncContext ;
struct TYPE_11__ {int /*<<< orphan*/  pending_commands; } ;
typedef  TYPE_5__ instanceLink ;
struct TYPE_7__ {scalar_t__ type; int integer; int /*<<< orphan*/  str; } ;

/* Variables and functions */
 int /*<<< orphan*/  LL_WARNING ; 
 scalar_t__ REDIS_REPLY_ARRAY ; 
 scalar_t__ REDIS_REPLY_INTEGER ; 
 scalar_t__ REDIS_REPLY_STRING ; 
 int /*<<< orphan*/  SRI_MASTER_DOWN ; 
 int /*<<< orphan*/  mstime () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsnew (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

void sentinelReceiveIsMasterDownReply(redisAsyncContext *c, void *reply, void *privdata) {
    sentinelRedisInstance *ri = privdata;
    instanceLink *link = c->data;
    redisReply *r;

    if (!reply || !link) return;
    link->pending_commands--;
    r = reply;

    /* Ignore every error or unexpected reply.
     * Note that if the command returns an error for any reason we'll
     * end clearing the SRI_MASTER_DOWN flag for timeout anyway. */
    if (r->type == REDIS_REPLY_ARRAY && r->elements == 3 &&
        r->element[0]->type == REDIS_REPLY_INTEGER &&
        r->element[1]->type == REDIS_REPLY_STRING &&
        r->element[2]->type == REDIS_REPLY_INTEGER)
    {
        ri->last_master_down_reply_time = mstime();
        if (r->element[0]->integer == 1) {
            ri->flags |= SRI_MASTER_DOWN;
        } else {
            ri->flags &= ~SRI_MASTER_DOWN;
        }
        if (strcmp(r->element[1]->str,"*")) {
            /* If the runid in the reply is not "*" the Sentinel actually
             * replied with a vote. */
            sdsfree(ri->leader);
            if ((long long)ri->leader_epoch != r->element[2]->integer)
                serverLog(LL_WARNING,
                    "%s voted for %s %llu", ri->name,
                    r->element[1]->str,
                    (unsigned long long) r->element[2]->integer);
            ri->leader = sdsnew(r->element[1]->str);
            ri->leader_epoch = r->element[2]->integer;
        }
    }
}