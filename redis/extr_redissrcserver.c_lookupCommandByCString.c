#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct redisCommand {int dummy; } ;
typedef  int /*<<< orphan*/  sds ;
struct TYPE_2__ {int /*<<< orphan*/  commands; } ;

/* Variables and functions */
 struct redisCommand* dictFetchValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsnew (char*) ; 
 TYPE_1__ server ; 

struct redisCommand *lookupCommandByCString(char *s) {
    struct redisCommand *cmd;
    sds name = sdsnew(s);

    cmd = dictFetchValue(server.commands, name);
    sdsfree(name);
    return cmd;
}