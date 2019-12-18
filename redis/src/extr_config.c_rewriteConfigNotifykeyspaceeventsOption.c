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
struct rewriteConfigState {int dummy; } ;
typedef  int /*<<< orphan*/  sds ;
struct TYPE_2__ {scalar_t__ notify_keyspace_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  keyspaceEventsFlagsToString (scalar_t__) ; 
 int /*<<< orphan*/  rewriteConfigRewriteLine (struct rewriteConfigState*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sdscatrepr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsnew (char*) ; 
 TYPE_1__ server ; 

void rewriteConfigNotifykeyspaceeventsOption(struct rewriteConfigState *state) {
    int force = server.notify_keyspace_events != 0;
    char *option = "notify-keyspace-events";
    sds line, flags;

    flags = keyspaceEventsFlagsToString(server.notify_keyspace_events);
    line = sdsnew(option);
    line = sdscatlen(line, " ", 1);
    line = sdscatrepr(line, flags, sdslen(flags));
    sdsfree(flags);
    rewriteConfigRewriteLine(state,option,line,force);
}