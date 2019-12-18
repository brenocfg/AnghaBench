#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  renamed_commands; struct TYPE_3__* master; } ;
typedef  TYPE_1__ sentinelRedisInstance ;
typedef  int /*<<< orphan*/  sds ;

/* Variables and functions */
 char* dictFetchValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsnew (char*) ; 

char *sentinelInstanceMapCommand(sentinelRedisInstance *ri, char *command) {
    sds sc = sdsnew(command);
    if (ri->master) ri = ri->master;
    char *retval = dictFetchValue(ri->renamed_commands, sc);
    sdsfree(sc);
    return retval ? retval : command;
}