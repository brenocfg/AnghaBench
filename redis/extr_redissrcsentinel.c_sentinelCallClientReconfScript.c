#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  toport ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/ * client_reconfig_script; } ;
typedef  TYPE_1__ sentinelRedisInstance ;
struct TYPE_7__ {int /*<<< orphan*/  ip; int /*<<< orphan*/  port; } ;
typedef  TYPE_2__ sentinelAddr ;
typedef  int /*<<< orphan*/  fromport ;

/* Variables and functions */
 int SENTINEL_LEADER ; 
 int /*<<< orphan*/  ll2string (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sentinelScheduleScriptExecution (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

void sentinelCallClientReconfScript(sentinelRedisInstance *master, int role, char *state, sentinelAddr *from, sentinelAddr *to) {
    char fromport[32], toport[32];

    if (master->client_reconfig_script == NULL) return;
    ll2string(fromport,sizeof(fromport),from->port);
    ll2string(toport,sizeof(toport),to->port);
    sentinelScheduleScriptExecution(master->client_reconfig_script,
        master->name,
        (role == SENTINEL_LEADER) ? "leader" : "observer",
        state, from->ip, fromport, to->ip, toport, NULL);
}