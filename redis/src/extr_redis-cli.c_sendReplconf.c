#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; char* str; } ;
typedef  TYPE_1__ redisReply ;

/* Variables and functions */
 scalar_t__ REDIS_REPLY_ERROR ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  freeReplyObject (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*) ; 
 TYPE_1__* redisCommand (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

void sendReplconf(const char* arg1, const char* arg2) {
    printf("sending REPLCONF %s %s\n", arg1, arg2);
    redisReply *reply = redisCommand(context, "REPLCONF %s %s", arg1, arg2);

    /* Handle any error conditions */
    if(reply == NULL) {
        fprintf(stderr, "\nI/O error\n");
        exit(1);
    } else if(reply->type == REDIS_REPLY_ERROR) {
        fprintf(stderr, "REPLCONF %s error: %s\n", arg1, reply->str);
        /* non fatal, old versions may not support it */
    }
    freeReplyObject(reply);
}