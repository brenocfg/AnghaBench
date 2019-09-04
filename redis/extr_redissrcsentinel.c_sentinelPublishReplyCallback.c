#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  last_pub_time; } ;
typedef  TYPE_1__ sentinelRedisInstance ;
struct TYPE_7__ {scalar_t__ type; } ;
typedef  TYPE_2__ redisReply ;
struct TYPE_8__ {TYPE_4__* data; } ;
typedef  TYPE_3__ redisAsyncContext ;
struct TYPE_9__ {int /*<<< orphan*/  pending_commands; } ;
typedef  TYPE_4__ instanceLink ;

/* Variables and functions */
 scalar_t__ REDIS_REPLY_ERROR ; 
 int /*<<< orphan*/  mstime () ; 

void sentinelPublishReplyCallback(redisAsyncContext *c, void *reply, void *privdata) {
    sentinelRedisInstance *ri = privdata;
    instanceLink *link = c->data;
    redisReply *r;

    if (!reply || !link) return;
    link->pending_commands--;
    r = reply;

    /* Only update pub_time if we actually published our message. Otherwise
     * we'll retry again in 100 milliseconds. */
    if (r->type != REDIS_REPLY_ERROR)
        ri->last_pub_time = mstime();
}