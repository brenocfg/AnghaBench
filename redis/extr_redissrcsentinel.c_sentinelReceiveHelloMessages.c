#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* link; } ;
typedef  TYPE_3__ sentinelRedisInstance ;
struct TYPE_9__ {scalar_t__ type; int elements; TYPE_2__** element; } ;
typedef  TYPE_4__ redisReply ;
typedef  int /*<<< orphan*/  redisAsyncContext ;
struct TYPE_10__ {int /*<<< orphan*/  myid; } ;
struct TYPE_7__ {scalar_t__ type; int /*<<< orphan*/  len; int /*<<< orphan*/  str; } ;
struct TYPE_6__ {int /*<<< orphan*/  pc_last_activity; } ;

/* Variables and functions */
 scalar_t__ REDIS_REPLY_ARRAY ; 
 scalar_t__ REDIS_REPLY_STRING ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mstime () ; 
 TYPE_5__ sentinel ; 
 int /*<<< orphan*/  sentinelProcessHelloMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sentinelReceiveHelloMessages(redisAsyncContext *c, void *reply, void *privdata) {
    sentinelRedisInstance *ri = privdata;
    redisReply *r;
    UNUSED(c);

    if (!reply || !ri) return;
    r = reply;

    /* Update the last activity in the pubsub channel. Note that since we
     * receive our messages as well this timestamp can be used to detect
     * if the link is probably disconnected even if it seems otherwise. */
    ri->link->pc_last_activity = mstime();

    /* Sanity check in the reply we expect, so that the code that follows
     * can avoid to check for details. */
    if (r->type != REDIS_REPLY_ARRAY ||
        r->elements != 3 ||
        r->element[0]->type != REDIS_REPLY_STRING ||
        r->element[1]->type != REDIS_REPLY_STRING ||
        r->element[2]->type != REDIS_REPLY_STRING ||
        strcmp(r->element[0]->str,"message") != 0) return;

    /* We are not interested in meeting ourselves */
    if (strstr(r->element[2]->str,sentinel.myid) != NULL) return;

    sentinelProcessHelloMessage(r->element[2]->str, r->element[2]->len);
}