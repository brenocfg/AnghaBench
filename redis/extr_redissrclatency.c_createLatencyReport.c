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
struct latencyTimeSeries {scalar_t__ max; } ;
struct latencyStats {double samples; scalar_t__ period; scalar_t__ mad; scalar_t__ avg; } ;
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_2__ {int latency_monitor_threshold; int stat_fork_rate; int slowlog_log_slower_than; scalar_t__ aof_fsync; int hz; int /*<<< orphan*/  latency_events; } ;

/* Variables and functions */
 scalar_t__ AOF_FSYNC_ALWAYS ; 
 scalar_t__ THPGetAnonHugePagesSize () ; 
 int /*<<< orphan*/  analyzeLatencyForEvent (char*,struct latencyStats*) ; 
 char* dictGetKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictGetSafeIterator (int /*<<< orphan*/ ) ; 
 struct latencyTimeSeries* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 scalar_t__ dictSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdscat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sdscatprintf (int /*<<< orphan*/ ,char*,unsigned long long,...) ; 
 int /*<<< orphan*/  sdsempty () ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 

sds createLatencyReport(void) {
    sds report = sdsempty();
    int advise_better_vm = 0;       /* Better virtual machines. */
    int advise_slowlog_enabled = 0; /* Enable slowlog. */
    int advise_slowlog_tuning = 0;  /* Reconfigure slowlog. */
    int advise_slowlog_inspect = 0; /* Check your slowlog. */
    int advise_disk_contention = 0; /* Try to lower disk contention. */
    int advise_scheduler = 0;       /* Intrinsic latency. */
    int advise_data_writeback = 0;  /* data=writeback. */
    int advise_no_appendfsync = 0;  /* don't fsync during rewrites. */
    int advise_local_disk = 0;      /* Avoid remote disks. */
    int advise_ssd = 0;             /* Use an SSD drive. */
    int advise_write_load_info = 0; /* Print info about AOF and write load. */
    int advise_hz = 0;              /* Use higher HZ. */
    int advise_large_objects = 0;   /* Deletion of large objects. */
    int advise_mass_eviction = 0;   /* Avoid mass eviction of keys. */
    int advise_relax_fsync_policy = 0; /* appendfsync always is slow. */
    int advise_disable_thp = 0;     /* AnonHugePages detected. */
    int advices = 0;

    /* Return ASAP if the latency engine is disabled and it looks like it
     * was never enabled so far. */
    if (dictSize(server.latency_events) == 0 &&
        server.latency_monitor_threshold == 0)
    {
        report = sdscat(report,"I'm sorry, Dave, I can't do that. Latency monitoring is disabled in this Redis instance. You may use \"CONFIG SET latency-monitor-threshold <milliseconds>.\" in order to enable it. If we weren't in a deep space mission I'd suggest to take a look at http://redis.io/topics/latency-monitor.\n");
        return report;
    }

    /* Show all the events stats and add for each event some event-related
     * comment depending on the values. */
    dictIterator *di;
    dictEntry *de;
    int eventnum = 0;

    di = dictGetSafeIterator(server.latency_events);
    while((de = dictNext(di)) != NULL) {
        char *event = dictGetKey(de);
        struct latencyTimeSeries *ts = dictGetVal(de);
        struct latencyStats ls;

        if (ts == NULL) continue;
        eventnum++;
        if (eventnum == 1) {
            report = sdscat(report,"Dave, I have observed latency spikes in this Redis instance. You don't mind talking about it, do you Dave?\n\n");
        }
        analyzeLatencyForEvent(event,&ls);

        report = sdscatprintf(report,
            "%d. %s: %d latency spikes (average %lums, mean deviation %lums, period %.2f sec). Worst all time event %lums.",
            eventnum, event,
            ls.samples,
            (unsigned long) ls.avg,
            (unsigned long) ls.mad,
            (double) ls.period/ls.samples,
            (unsigned long) ts->max);

        /* Fork */
        if (!strcasecmp(event,"fork")) {
            char *fork_quality;
            if (server.stat_fork_rate < 10) {
                fork_quality = "terrible";
                advise_better_vm = 1;
                advices++;
            } else if (server.stat_fork_rate < 25) {
                fork_quality = "poor";
                advise_better_vm = 1;
                advices++;
            } else if (server.stat_fork_rate < 100) {
                fork_quality = "good";
            } else {
                fork_quality = "excellent";
            }
            report = sdscatprintf(report,
                " Fork rate is %.2f GB/sec (%s).", server.stat_fork_rate,
                fork_quality);
        }

        /* Potentially commands. */
        if (!strcasecmp(event,"command")) {
            if (server.slowlog_log_slower_than < 0) {
                advise_slowlog_enabled = 1;
                advices++;
            } else if (server.slowlog_log_slower_than/1000 >
                       server.latency_monitor_threshold)
            {
                advise_slowlog_tuning = 1;
                advices++;
            }
            advise_slowlog_inspect = 1;
            advise_large_objects = 1;
            advices += 2;
        }

        /* fast-command. */
        if (!strcasecmp(event,"fast-command")) {
            advise_scheduler = 1;
            advices++;
        }

        /* AOF and I/O. */
        if (!strcasecmp(event,"aof-write-pending-fsync")) {
            advise_local_disk = 1;
            advise_disk_contention = 1;
            advise_ssd = 1;
            advise_data_writeback = 1;
            advices += 4;
        }

        if (!strcasecmp(event,"aof-write-active-child")) {
            advise_no_appendfsync = 1;
            advise_data_writeback = 1;
            advise_ssd = 1;
            advices += 3;
        }

        if (!strcasecmp(event,"aof-write-alone")) {
            advise_local_disk = 1;
            advise_data_writeback = 1;
            advise_ssd = 1;
            advices += 3;
        }

        if (!strcasecmp(event,"aof-fsync-always")) {
            advise_relax_fsync_policy = 1;
            advices++;
        }

        if (!strcasecmp(event,"aof-fstat") ||
            !strcasecmp(event,"rdb-unlik-temp-file")) {
            advise_disk_contention = 1;
            advise_local_disk = 1;
            advices += 2;
        }

        if (!strcasecmp(event,"aof-rewrite-diff-write") ||
            !strcasecmp(event,"aof-rename")) {
            advise_write_load_info = 1;
            advise_data_writeback = 1;
            advise_ssd = 1;
            advise_local_disk = 1;
            advices += 4;
        }

        /* Expire cycle. */
        if (!strcasecmp(event,"expire-cycle")) {
            advise_hz = 1;
            advise_large_objects = 1;
            advices += 2;
        }

        /* Eviction cycle. */
        if (!strcasecmp(event,"eviction-del")) {
            advise_large_objects = 1;
            advices++;
        }

        if (!strcasecmp(event,"eviction-cycle")) {
            advise_mass_eviction = 1;
            advices++;
        }

        report = sdscatlen(report,"\n",1);
    }
    dictReleaseIterator(di);

    /* Add non event based advices. */
    if (THPGetAnonHugePagesSize() > 0) {
        advise_disable_thp = 1;
        advices++;
    }

    if (eventnum == 0 && advices == 0) {
        report = sdscat(report,"Dave, no latency spike was observed during the lifetime of this Redis instance, not in the slightest bit. I honestly think you ought to sit down calmly, take a stress pill, and think things over.\n");
    } else if (eventnum > 0 && advices == 0) {
        report = sdscat(report,"\nWhile there are latency events logged, I'm not able to suggest any easy fix. Please use the Redis community to get some help, providing this report in your help request.\n");
    } else {
        /* Add all the suggestions accumulated so far. */

        /* Better VM. */
        report = sdscat(report,"\nI have a few advices for you:\n\n");
        if (advise_better_vm) {
            report = sdscat(report,"- If you are using a virtual machine, consider upgrading it with a faster one using an hypervisior that provides less latency during fork() calls. Xen is known to have poor fork() performance. Even in the context of the same VM provider, certain kinds of instances can execute fork faster than others.\n");
        }

        /* Slow log. */
        if (advise_slowlog_enabled) {
            report = sdscatprintf(report,"- There are latency issues with potentially slow commands you are using. Try to enable the Slow Log Redis feature using the command 'CONFIG SET slowlog-log-slower-than %llu'. If the Slow log is disabled Redis is not able to log slow commands execution for you.\n", (unsigned long long)server.latency_monitor_threshold*1000);
        }

        if (advise_slowlog_tuning) {
            report = sdscatprintf(report,"- Your current Slow Log configuration only logs events that are slower than your configured latency monitor threshold. Please use 'CONFIG SET slowlog-log-slower-than %llu'.\n", (unsigned long long)server.latency_monitor_threshold*1000);
        }

        if (advise_slowlog_inspect) {
            report = sdscat(report,"- Check your Slow Log to understand what are the commands you are running which are too slow to execute. Please check http://redis.io/commands/slowlog for more information.\n");
        }

        /* Intrinsic latency. */
        if (advise_scheduler) {
            report = sdscat(report,"- The system is slow to execute Redis code paths not containing system calls. This usually means the system does not provide Redis CPU time to run for long periods. You should try to:\n"
            "  1) Lower the system load.\n"
            "  2) Use a computer / VM just for Redis if you are running other softawre in the same system.\n"
            "  3) Check if you have a \"noisy neighbour\" problem.\n"
            "  4) Check with 'redis-cli --intrinsic-latency 100' what is the intrinsic latency in your system.\n"
            "  5) Check if the problem is allocator-related by recompiling Redis with MALLOC=libc, if you are using Jemalloc. However this may create fragmentation problems.\n");
        }

        /* AOF / Disk latency. */
        if (advise_local_disk) {
            report = sdscat(report,"- It is strongly advised to use local disks for persistence, especially if you are using AOF. Remote disks provided by platform-as-a-service providers are known to be slow.\n");
        }

        if (advise_ssd) {
            report = sdscat(report,"- SSD disks are able to reduce fsync latency, and total time needed for snapshotting and AOF log rewriting (resulting in smaller memory usage and smaller final AOF rewrite buffer flushes). With extremely high write load SSD disks can be a good option. However Redis should perform reasonably with high load using normal disks. Use this advice as a last resort.\n");
        }

        if (advise_data_writeback) {
            report = sdscat(report,"- Mounting ext3/4 filesystems with data=writeback can provide a performance boost compared to data=ordered, however this mode of operation provides less guarantees, and sometimes it can happen that after a hard crash the AOF file will have an half-written command at the end and will require to be repaired before Redis restarts.\n");
        }

        if (advise_disk_contention) {
            report = sdscat(report,"- Try to lower the disk contention. This is often caused by other disk intensive processes running in the same computer (including other Redis instances).\n");
        }

        if (advise_no_appendfsync) {
            report = sdscat(report,"- Assuming from the point of view of data safety this is viable in your environment, you could try to enable the 'no-appendfsync-on-rewrite' option, so that fsync will not be performed while there is a child rewriting the AOF file or producing an RDB file (the moment where there is high disk contention).\n");
        }

        if (advise_relax_fsync_policy && server.aof_fsync == AOF_FSYNC_ALWAYS) {
            report = sdscat(report,"- Your fsync policy is set to 'always'. It is very hard to get good performances with such a setup, if possible try to relax the fsync policy to 'onesec'.\n");
        }

        if (advise_write_load_info) {
            report = sdscat(report,"- Latency during the AOF atomic rename operation or when the final difference is flushed to the AOF file at the end of the rewrite, sometimes is caused by very high write load, causing the AOF buffer to get very large. If possible try to send less commands to accomplish the same work, or use Lua scripts to group multiple operations into a single EVALSHA call.\n");
        }

        if (advise_hz && server.hz < 100) {
            report = sdscat(report,"- In order to make the Redis keys expiring process more incremental, try to set the 'hz' configuration parameter to 100 using 'CONFIG SET hz 100'.\n");
        }

        if (advise_large_objects) {
            report = sdscat(report,"- Deleting, expiring or evicting (because of maxmemory policy) large objects is a blocking operation. If you have very large objects that are often deleted, expired, or evicted, try to fragment those objects into multiple smaller objects.\n");
        }

        if (advise_mass_eviction) {
            report = sdscat(report,"- Sudden changes to the 'maxmemory' setting via 'CONFIG SET', or allocation of large objects via sets or sorted sets intersections, STORE option of SORT, Redis Cluster large keys migrations (RESTORE command), may create sudden memory pressure forcing the server to block trying to evict keys. \n");
        }

        if (advise_disable_thp) {
            report = sdscat(report,"- I detected a non zero amount of anonymous huge pages used by your process. This creates very serious latency events in different conditions, especially when Redis is persisting on disk. To disable THP support use the command 'echo never > /sys/kernel/mm/transparent_hugepage/enabled', make sure to also add it into /etc/rc.local so that the command will be executed again after a reboot. Note that even if you have already disabled THP, you still need to restart the Redis process to get rid of the huge pages already created.\n");
        }
    }

    return report;
}