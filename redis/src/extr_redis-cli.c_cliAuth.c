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
struct TYPE_6__ {int /*<<< orphan*/ * auth; int /*<<< orphan*/ * user; } ;

/* Variables and functions */
 int REDIS_ERR ; 
 int REDIS_OK ; 
 scalar_t__ REDIS_REPLY_ERROR ; 
 TYPE_4__ config ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  freeReplyObject (TYPE_1__*) ; 
 TYPE_1__* redisCommand (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int cliAuth(void) {
    redisReply *reply;
    if (config.auth == NULL) return REDIS_OK;

    if (config.user == NULL)
        reply = redisCommand(context,"AUTH %s",config.auth);
    else
        reply = redisCommand(context,"AUTH %s %s",config.user,config.auth);
    if (reply != NULL) {
        if (reply->type == REDIS_REPLY_ERROR)
            fprintf(stderr,"Warning: AUTH failed\n");
        freeReplyObject(reply);
        return REDIS_OK;
    }
    return REDIS_ERR;
}