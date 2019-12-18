#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int flags; char* auth_pass; TYPE_1__* link; TYPE_2__* master; } ;
typedef  TYPE_3__ sentinelRedisInstance ;
typedef  int /*<<< orphan*/  redisAsyncContext ;
struct TYPE_8__ {char* auth_pass; } ;
struct TYPE_7__ {int /*<<< orphan*/  pending_commands; } ;

/* Variables and functions */
 char* ACLDefaultUserFirstPassword () ; 
 scalar_t__ C_OK ; 
 int SRI_MASTER ; 
 int SRI_SENTINEL ; 
 int SRI_SLAVE ; 
 scalar_t__ redisAsyncCommand (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sentinelDiscardReplyCallback ; 
 int /*<<< orphan*/  sentinelInstanceMapCommand (TYPE_3__*,char*) ; 

void sentinelSendAuthIfNeeded(sentinelRedisInstance *ri, redisAsyncContext *c) {
    char *auth_pass = NULL;

    if (ri->flags & SRI_MASTER) {
        auth_pass = ri->auth_pass;
    } else if (ri->flags & SRI_SLAVE) {
        auth_pass = ri->master->auth_pass;
    } else if (ri->flags & SRI_SENTINEL) {
        auth_pass = ACLDefaultUserFirstPassword();
    }

    if (auth_pass) {
        if (redisAsyncCommand(c, sentinelDiscardReplyCallback, ri, "%s %s",
            sentinelInstanceMapCommand(ri,"AUTH"),
            auth_pass) == C_OK) ri->link->pending_commands++;
    }
}