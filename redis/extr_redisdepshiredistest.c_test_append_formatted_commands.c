#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct config {int dummy; } ;
typedef  int /*<<< orphan*/  redisReply ;
typedef  int /*<<< orphan*/  redisContext ;

/* Variables and functions */
 scalar_t__ REDIS_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  disconnect (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * do_connect (struct config) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  freeReplyObject (int /*<<< orphan*/ *) ; 
 scalar_t__ redisAppendFormattedCommand (int /*<<< orphan*/ *,char*,int) ; 
 int redisFormatCommand (char**,char*) ; 
 scalar_t__ redisGetReply (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  test (char*) ; 
 int /*<<< orphan*/  test_cond (int) ; 

__attribute__((used)) static void test_append_formatted_commands(struct config config) {
    redisContext *c;
    redisReply *reply;
    char *cmd;
    int len;

    c = do_connect(config);

    test("Append format command: ");

    len = redisFormatCommand(&cmd, "SET foo bar");

    test_cond(redisAppendFormattedCommand(c, cmd, len) == REDIS_OK);

    assert(redisGetReply(c, (void*)&reply) == REDIS_OK);

    free(cmd);
    freeReplyObject(reply);

    disconnect(c, 0);
}