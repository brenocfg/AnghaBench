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
typedef  int /*<<< orphan*/  RedisModuleInfoCtx ;

/* Variables and functions */
 int /*<<< orphan*/  RedisModule_InfoAddFieldCString (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  RedisModule_InfoAddFieldDouble (int /*<<< orphan*/ *,char*,double) ; 
 int /*<<< orphan*/  RedisModule_InfoAddFieldLongLong (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  RedisModule_InfoAddSection (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  RedisModule_InfoBeginDictField (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  RedisModule_InfoEndDictField (int /*<<< orphan*/ *) ; 

void InfoFunc(RedisModuleInfoCtx *ctx, int for_crash_report) {
    RedisModule_InfoAddSection(ctx, "");
    RedisModule_InfoAddFieldLongLong(ctx, "global", -2);

    RedisModule_InfoAddSection(ctx, "Spanish");
    RedisModule_InfoAddFieldCString(ctx, "uno", "one");
    RedisModule_InfoAddFieldLongLong(ctx, "dos", 2);

    RedisModule_InfoAddSection(ctx, "Italian");
    RedisModule_InfoAddFieldLongLong(ctx, "due", 2);
    RedisModule_InfoAddFieldDouble(ctx, "tre", 3.3);

    RedisModule_InfoAddSection(ctx, "keyspace");
    RedisModule_InfoBeginDictField(ctx, "db0");
    RedisModule_InfoAddFieldLongLong(ctx, "keys", 3);
    RedisModule_InfoAddFieldLongLong(ctx, "expires", 1);
    RedisModule_InfoEndDictField(ctx);

    if (for_crash_report) {
        RedisModule_InfoAddSection(ctx, "Klingon");
        RedisModule_InfoAddFieldCString(ctx, "one", "wa’");
        RedisModule_InfoAddFieldCString(ctx, "two", "cha’");
        RedisModule_InfoAddFieldCString(ctx, "three", "wej");
    }

}