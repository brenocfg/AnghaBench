#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ type; char* str; int elements; TYPE_1__** element; } ;
typedef  TYPE_2__ redisReply ;
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/  str; } ;

/* Variables and functions */
 scalar_t__ REDIS_REPLY_ARRAY ; 
 scalar_t__ REDIS_REPLY_ERROR ; 
 scalar_t__ REDIS_REPLY_STRING ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* redisCommand (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  stderr ; 
 unsigned long long strtoull (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static redisReply *sendScan(unsigned long long *it) {
    redisReply *reply = redisCommand(context, "SCAN %llu", *it);

    /* Handle any error conditions */
    if(reply == NULL) {
        fprintf(stderr, "\nI/O error\n");
        exit(1);
    } else if(reply->type == REDIS_REPLY_ERROR) {
        fprintf(stderr, "SCAN error: %s\n", reply->str);
        exit(1);
    } else if(reply->type != REDIS_REPLY_ARRAY) {
        fprintf(stderr, "Non ARRAY response from SCAN!\n");
        exit(1);
    } else if(reply->elements != 2) {
        fprintf(stderr, "Invalid element count from SCAN!\n");
        exit(1);
    }

    /* Validate our types are correct */
    assert(reply->element[0]->type == REDIS_REPLY_STRING);
    assert(reply->element[1]->type == REDIS_REPLY_ARRAY);

    /* Update iterator */
    *it = strtoull(reply->element[0]->str, NULL, 10);

    return reply;
}