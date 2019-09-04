#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; int failover_timeout; int failover_start_time; int failover_state_change_time; int /*<<< orphan*/  failover_state; int /*<<< orphan*/  failover_epoch; } ;
typedef  TYPE_1__ sentinelRedisInstance ;
struct TYPE_8__ {int simfailure_flags; int /*<<< orphan*/  myid; } ;

/* Variables and functions */
 int /*<<< orphan*/  LL_WARNING ; 
 int SENTINEL_ELECTION_TIMEOUT ; 
 int /*<<< orphan*/  SENTINEL_FAILOVER_STATE_SELECT_SLAVE ; 
 int SENTINEL_SIMFAILURE_CRASH_AFTER_ELECTION ; 
 int SRI_FORCE_FAILOVER ; 
 int mstime () ; 
 int /*<<< orphan*/  sdsfree (char*) ; 
 TYPE_6__ sentinel ; 
 int /*<<< orphan*/  sentinelAbortFailover (TYPE_1__*) ; 
 int /*<<< orphan*/  sentinelEvent (int /*<<< orphan*/ ,char*,TYPE_1__*,char*) ; 
 char* sentinelGetLeader (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sentinelSimFailureCrash () ; 
 scalar_t__ strcasecmp (char*,int /*<<< orphan*/ ) ; 

void sentinelFailoverWaitStart(sentinelRedisInstance *ri) {
    char *leader;
    int isleader;

    /* Check if we are the leader for the failover epoch. */
    leader = sentinelGetLeader(ri, ri->failover_epoch);
    isleader = leader && strcasecmp(leader,sentinel.myid) == 0;
    sdsfree(leader);

    /* If I'm not the leader, and it is not a forced failover via
     * SENTINEL FAILOVER, then I can't continue with the failover. */
    if (!isleader && !(ri->flags & SRI_FORCE_FAILOVER)) {
        int election_timeout = SENTINEL_ELECTION_TIMEOUT;

        /* The election timeout is the MIN between SENTINEL_ELECTION_TIMEOUT
         * and the configured failover timeout. */
        if (election_timeout > ri->failover_timeout)
            election_timeout = ri->failover_timeout;
        /* Abort the failover if I'm not the leader after some time. */
        if (mstime() - ri->failover_start_time > election_timeout) {
            sentinelEvent(LL_WARNING,"-failover-abort-not-elected",ri,"%@");
            sentinelAbortFailover(ri);
        }
        return;
    }
    sentinelEvent(LL_WARNING,"+elected-leader",ri,"%@");
    if (sentinel.simfailure_flags & SENTINEL_SIMFAILURE_CRASH_AFTER_ELECTION)
        sentinelSimFailureCrash();
    ri->failover_state = SENTINEL_FAILOVER_STATE_SELECT_SLAVE;
    ri->failover_state_change_time = mstime();
    sentinelEvent(LL_WARNING,"+failover-state-select-slave",ri,"%@");
}