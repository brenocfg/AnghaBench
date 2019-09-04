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
typedef  int /*<<< orphan*/  RedisModuleCtx ;

/* Variables and functions */
 int replyWithStatus (int /*<<< orphan*/ *,char const*,char*) ; 

int RM_ReplyWithSimpleString(RedisModuleCtx *ctx, const char *msg) {
    return replyWithStatus(ctx,msg,"+");
}