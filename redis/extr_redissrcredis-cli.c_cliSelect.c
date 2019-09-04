#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; } ;
typedef  TYPE_1__ redisReply ;
struct TYPE_6__ {scalar_t__ dbnum; } ;

/* Variables and functions */
 int REDIS_ERR ; 
 int REDIS_OK ; 
 scalar_t__ REDIS_REPLY_ERROR ; 
 TYPE_4__ config ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  freeReplyObject (TYPE_1__*) ; 
 TYPE_1__* redisCommand (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int cliSelect(void) {
    redisReply *reply;
    if (config.dbnum == 0) return REDIS_OK;

    reply = redisCommand(context,"SELECT %d",config.dbnum);
    if (reply != NULL) {
        int result = REDIS_OK;
        if (reply->type == REDIS_REPLY_ERROR) result = REDIS_ERR;
        freeReplyObject(reply);
        return result;
    }
    return REDIS_ERR;
}