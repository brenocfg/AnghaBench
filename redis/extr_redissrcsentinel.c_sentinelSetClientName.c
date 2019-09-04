#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* link; } ;
typedef  TYPE_2__ sentinelRedisInstance ;
typedef  int /*<<< orphan*/  redisAsyncContext ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_9__ {char* myid; } ;
struct TYPE_7__ {int /*<<< orphan*/  pending_commands; } ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 scalar_t__ redisAsyncCommand (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,char*,int /*<<< orphan*/ ,char*) ; 
 TYPE_5__ sentinel ; 
 int /*<<< orphan*/  sentinelDiscardReplyCallback ; 
 int /*<<< orphan*/  sentinelInstanceMapCommand (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 

void sentinelSetClientName(sentinelRedisInstance *ri, redisAsyncContext *c, char *type) {
    char name[64];

    snprintf(name,sizeof(name),"sentinel-%.8s-%s",sentinel.myid,type);
    if (redisAsyncCommand(c, sentinelDiscardReplyCallback, ri,
        "%s SETNAME %s",
        sentinelInstanceMapCommand(ri,"CLIENT"),
        name) == C_OK)
    {
        ri->link->pending_commands++;
    }
}