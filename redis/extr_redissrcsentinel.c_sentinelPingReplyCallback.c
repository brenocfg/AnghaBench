#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int flags; TYPE_1__* link; } ;
typedef  TYPE_2__ sentinelRedisInstance ;
struct TYPE_11__ {scalar_t__ type; int /*<<< orphan*/  str; } ;
typedef  TYPE_3__ redisReply ;
struct TYPE_12__ {TYPE_5__* data; } ;
typedef  TYPE_4__ redisAsyncContext ;
struct TYPE_13__ {void* last_pong_time; scalar_t__ act_ping_time; void* last_avail_time; int /*<<< orphan*/  pending_commands; } ;
typedef  TYPE_5__ instanceLink ;
struct TYPE_9__ {int /*<<< orphan*/  pending_commands; int /*<<< orphan*/  cc; } ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 scalar_t__ REDIS_REPLY_ERROR ; 
 scalar_t__ REDIS_REPLY_STATUS ; 
 int SRI_SCRIPT_KILL_SENT ; 
 int SRI_S_DOWN ; 
 void* mstime () ; 
 scalar_t__ redisAsyncCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sentinelDiscardReplyCallback ; 
 int /*<<< orphan*/  sentinelInstanceMapCommand (TYPE_2__*,char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

void sentinelPingReplyCallback(redisAsyncContext *c, void *reply, void *privdata) {
    sentinelRedisInstance *ri = privdata;
    instanceLink *link = c->data;
    redisReply *r;

    if (!reply || !link) return;
    link->pending_commands--;
    r = reply;

    if (r->type == REDIS_REPLY_STATUS ||
        r->type == REDIS_REPLY_ERROR) {
        /* Update the "instance available" field only if this is an
         * acceptable reply. */
        if (strncmp(r->str,"PONG",4) == 0 ||
            strncmp(r->str,"LOADING",7) == 0 ||
            strncmp(r->str,"MASTERDOWN",10) == 0)
        {
            link->last_avail_time = mstime();
            link->act_ping_time = 0; /* Flag the pong as received. */
        } else {
            /* Send a SCRIPT KILL command if the instance appears to be
             * down because of a busy script. */
            if (strncmp(r->str,"BUSY",4) == 0 &&
                (ri->flags & SRI_S_DOWN) &&
                !(ri->flags & SRI_SCRIPT_KILL_SENT))
            {
                if (redisAsyncCommand(ri->link->cc,
                        sentinelDiscardReplyCallback, ri,
                        "%s KILL",
                        sentinelInstanceMapCommand(ri,"SCRIPT")) == C_OK)
                {
                    ri->link->pending_commands++;
                }
                ri->flags |= SRI_SCRIPT_KILL_SENT;
            }
        }
    }
    link->last_pong_time = mstime();
}