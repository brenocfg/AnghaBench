#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct redisMemOverhead {int num_dbs; size_t peak_allocated; size_t total_allocated; size_t startup_allocated; size_t repl_backlog; size_t clients_slaves; size_t clients_normal; size_t aof_buffer; size_t lua_caches; size_t overhead_total; size_t total_keys; size_t bytes_per_key; size_t dataset; size_t allocator_frag_bytes; size_t allocator_rss_bytes; size_t rss_extra_bytes; size_t total_frag_bytes; int /*<<< orphan*/  total_frag; int /*<<< orphan*/  rss_extra; int /*<<< orphan*/  allocator_rss; int /*<<< orphan*/  allocator_frag; int /*<<< orphan*/  peak_perc; int /*<<< orphan*/  dataset_perc; TYPE_2__* db; } ;
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  dictEntry ;
typedef  int /*<<< orphan*/  dbname ;
struct TYPE_23__ {int argc; TYPE_9__** argv; TYPE_1__* db; } ;
typedef  TYPE_4__ client ;
struct TYPE_26__ {scalar_t__ ptr; } ;
struct TYPE_22__ {size_t allocator_allocated; size_t allocator_active; size_t allocator_resident; } ;
struct TYPE_25__ {TYPE_3__ cron_malloc_stats; } ;
struct TYPE_24__ {int /*<<< orphan*/  ok; int /*<<< orphan*/  syntaxerr; } ;
struct TYPE_21__ {size_t overhead_ht_main; size_t overhead_ht_expires; int /*<<< orphan*/  dbid; } ;
struct TYPE_20__ {int /*<<< orphan*/  dict; } ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 long long LLONG_MAX ; 
 long long OBJ_COMPUTE_SIZE_DEF_SAMPLES ; 
 int /*<<< orphan*/  addReply (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyBulkCString (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  addReplyDouble (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyError (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  addReplyErrorFormat (TYPE_4__*,char*,char*) ; 
 int /*<<< orphan*/  addReplyHelp (TYPE_4__*,char const**) ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_4__*,size_t) ; 
 int /*<<< orphan*/  addReplyMapLen (TYPE_4__*,int) ; 
 int /*<<< orphan*/  addReplyNull (TYPE_4__*) ; 
 int /*<<< orphan*/  addReplyVerbatim (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * dictFind (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dictGetKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freeMemoryOverheadData (struct redisMemOverhead*) ; 
 scalar_t__ getLongLongFromObjectOrReply (TYPE_4__*,TYPE_9__*,long long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getMemoryDoctorReport () ; 
 struct redisMemOverhead* getMemoryOverheadData () ; 
 int /*<<< orphan*/  inputCatSds ; 
 int /*<<< orphan*/  je_malloc_stats_print (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ jemalloc_purge () ; 
 size_t objectComputeSize (int /*<<< orphan*/ ,long long) ; 
 scalar_t__ sdsAllocSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 
 TYPE_6__ server ; 
 TYPE_5__ shared ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcasecmp (scalar_t__,char*) ; 

void memoryCommand(client *c) {
    if (!strcasecmp(c->argv[1]->ptr,"help") && c->argc == 2) {
        const char *help[] = {
"DOCTOR - Return memory problems reports.",
"MALLOC-STATS -- Return internal statistics report from the memory allocator.",
"PURGE -- Attempt to purge dirty pages for reclamation by the allocator.",
"STATS -- Return information about the memory usage of the server.",
"USAGE <key> [SAMPLES <count>] -- Return memory in bytes used by <key> and its value. Nested values are sampled up to <count> times (default: 5).",
NULL
        };
        addReplyHelp(c, help);
    } else if (!strcasecmp(c->argv[1]->ptr,"usage") && c->argc >= 3) {
        dictEntry *de;
        long long samples = OBJ_COMPUTE_SIZE_DEF_SAMPLES;
        for (int j = 3; j < c->argc; j++) {
            if (!strcasecmp(c->argv[j]->ptr,"samples") &&
                j+1 < c->argc)
            {
                if (getLongLongFromObjectOrReply(c,c->argv[j+1],&samples,NULL)
                     == C_ERR) return;
                if (samples < 0) {
                    addReply(c,shared.syntaxerr);
                    return;
                }
                if (samples == 0) samples = LLONG_MAX;;
                j++; /* skip option argument. */
            } else {
                addReply(c,shared.syntaxerr);
                return;
            }
        }
        if ((de = dictFind(c->db->dict,c->argv[2]->ptr)) == NULL) {
            addReplyNull(c);
            return;
        }
        size_t usage = objectComputeSize(dictGetVal(de),samples);
        usage += sdsAllocSize(dictGetKey(de));
        usage += sizeof(dictEntry);
        addReplyLongLong(c,usage);
    } else if (!strcasecmp(c->argv[1]->ptr,"stats") && c->argc == 2) {
        struct redisMemOverhead *mh = getMemoryOverheadData();

        addReplyMapLen(c,25+mh->num_dbs);

        addReplyBulkCString(c,"peak.allocated");
        addReplyLongLong(c,mh->peak_allocated);

        addReplyBulkCString(c,"total.allocated");
        addReplyLongLong(c,mh->total_allocated);

        addReplyBulkCString(c,"startup.allocated");
        addReplyLongLong(c,mh->startup_allocated);

        addReplyBulkCString(c,"replication.backlog");
        addReplyLongLong(c,mh->repl_backlog);

        addReplyBulkCString(c,"clients.slaves");
        addReplyLongLong(c,mh->clients_slaves);

        addReplyBulkCString(c,"clients.normal");
        addReplyLongLong(c,mh->clients_normal);

        addReplyBulkCString(c,"aof.buffer");
        addReplyLongLong(c,mh->aof_buffer);

        addReplyBulkCString(c,"lua.caches");
        addReplyLongLong(c,mh->lua_caches);

        for (size_t j = 0; j < mh->num_dbs; j++) {
            char dbname[32];
            snprintf(dbname,sizeof(dbname),"db.%zd",mh->db[j].dbid);
            addReplyBulkCString(c,dbname);
            addReplyMapLen(c,2);

            addReplyBulkCString(c,"overhead.hashtable.main");
            addReplyLongLong(c,mh->db[j].overhead_ht_main);

            addReplyBulkCString(c,"overhead.hashtable.expires");
            addReplyLongLong(c,mh->db[j].overhead_ht_expires);
        }

        addReplyBulkCString(c,"overhead.total");
        addReplyLongLong(c,mh->overhead_total);

        addReplyBulkCString(c,"keys.count");
        addReplyLongLong(c,mh->total_keys);

        addReplyBulkCString(c,"keys.bytes-per-key");
        addReplyLongLong(c,mh->bytes_per_key);

        addReplyBulkCString(c,"dataset.bytes");
        addReplyLongLong(c,mh->dataset);

        addReplyBulkCString(c,"dataset.percentage");
        addReplyDouble(c,mh->dataset_perc);

        addReplyBulkCString(c,"peak.percentage");
        addReplyDouble(c,mh->peak_perc);

        addReplyBulkCString(c,"allocator.allocated");
        addReplyLongLong(c,server.cron_malloc_stats.allocator_allocated);

        addReplyBulkCString(c,"allocator.active");
        addReplyLongLong(c,server.cron_malloc_stats.allocator_active);

        addReplyBulkCString(c,"allocator.resident");
        addReplyLongLong(c,server.cron_malloc_stats.allocator_resident);

        addReplyBulkCString(c,"allocator-fragmentation.ratio");
        addReplyDouble(c,mh->allocator_frag);

        addReplyBulkCString(c,"allocator-fragmentation.bytes");
        addReplyLongLong(c,mh->allocator_frag_bytes);

        addReplyBulkCString(c,"allocator-rss.ratio");
        addReplyDouble(c,mh->allocator_rss);

        addReplyBulkCString(c,"allocator-rss.bytes");
        addReplyLongLong(c,mh->allocator_rss_bytes);

        addReplyBulkCString(c,"rss-overhead.ratio");
        addReplyDouble(c,mh->rss_extra);

        addReplyBulkCString(c,"rss-overhead.bytes");
        addReplyLongLong(c,mh->rss_extra_bytes);

        addReplyBulkCString(c,"fragmentation"); /* this is the total RSS overhead, including fragmentation */
        addReplyDouble(c,mh->total_frag); /* it is kept here for backwards compatibility */

        addReplyBulkCString(c,"fragmentation.bytes");
        addReplyLongLong(c,mh->total_frag_bytes);

        freeMemoryOverheadData(mh);
    } else if (!strcasecmp(c->argv[1]->ptr,"malloc-stats") && c->argc == 2) {
#if defined(USE_JEMALLOC)
        sds info = sdsempty();
        je_malloc_stats_print(inputCatSds, &info, NULL);
        addReplyVerbatim(c,info,sdslen(info),"txt");
        sdsfree(info);
#else
        addReplyBulkCString(c,"Stats not supported for the current allocator");
#endif
    } else if (!strcasecmp(c->argv[1]->ptr,"doctor") && c->argc == 2) {
        sds report = getMemoryDoctorReport();
        addReplyVerbatim(c,report,sdslen(report),"txt");
        sdsfree(report);
    } else if (!strcasecmp(c->argv[1]->ptr,"purge") && c->argc == 2) {
        if (jemalloc_purge() == 0)
            addReply(c, shared.ok);
        else
            addReplyError(c, "Error purging dirty pages");
    } else {
        addReplyErrorFormat(c, "Unknown subcommand or wrong number of arguments for '%s'. Try MEMORY HELP", (char*)c->argv[1]->ptr);
    }
}