#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct redisMemOverhead {size_t total_allocated; size_t startup_allocated; float peak_allocated; float total_frag; float allocator_frag; float allocator_frag_bytes; float allocator_rss; float allocator_rss_bytes; float rss_extra; size_t repl_backlog; size_t clients_slaves; size_t clients_normal; size_t aof_buffer; size_t lua_caches; long long total_keys; int num_dbs; size_t overhead_total; size_t dataset; float peak_perc; float dataset_perc; size_t bytes_per_key; TYPE_4__* db; scalar_t__ rss_extra_bytes; scalar_t__ total_frag_bytes; } ;
typedef  int /*<<< orphan*/  robj ;
struct TYPE_11__ {int /*<<< orphan*/  expires; int /*<<< orphan*/  dict; } ;
typedef  TYPE_2__ redisDb ;
typedef  int /*<<< orphan*/  listNode ;
typedef  int /*<<< orphan*/  listIter ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_12__ {int flags; int /*<<< orphan*/  querybuf; } ;
typedef  TYPE_3__ client ;
struct TYPE_10__ {float zmalloc_used; float allocator_active; float allocator_allocated; float allocator_resident; scalar_t__ process_rss; } ;
struct TYPE_14__ {size_t initial_memory_usage; float stat_peak_memory; scalar_t__ aof_state; size_t lua_scripts_mem; int dbnum; TYPE_2__* db; int /*<<< orphan*/  repl_scriptcache_fifo; int /*<<< orphan*/  repl_scriptcache_dict; int /*<<< orphan*/  lua_scripts; int /*<<< orphan*/  aof_buf; int /*<<< orphan*/  clients; int /*<<< orphan*/  slaves; scalar_t__ repl_backlog; TYPE_1__ cron_malloc_stats; } ;
struct TYPE_13__ {int dbid; size_t overhead_ht_main; size_t overhead_ht_expires; } ;

/* Variables and functions */
 scalar_t__ AOF_OFF ; 
 int CLIENT_MONITOR ; 
 int CLIENT_SLAVE ; 
 scalar_t__ aofRewriteBufferSize () ; 
 int dictSize (int /*<<< orphan*/ ) ; 
 int dictSlots (int /*<<< orphan*/ ) ; 
 scalar_t__ getClientOutputBufferMemoryUsage (TYPE_3__*) ; 
 int /*<<< orphan*/ * listFirst (int /*<<< orphan*/ ) ; 
 int listLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * listNext (int /*<<< orphan*/ *) ; 
 TYPE_3__* listNodeValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sdsAllocSize (int /*<<< orphan*/ ) ; 
 int sdsZmallocSize (TYPE_3__*) ; 
 scalar_t__ sdsalloc (int /*<<< orphan*/ ) ; 
 TYPE_6__ server ; 
 struct redisMemOverhead* zcalloc (int) ; 
 scalar_t__ zmalloc_size (scalar_t__) ; 
 size_t zmalloc_used_memory () ; 
 TYPE_4__* zrealloc (TYPE_4__*,int) ; 

struct redisMemOverhead *getMemoryOverheadData(void) {
    int j;
    size_t mem_total = 0;
    size_t mem = 0;
    size_t zmalloc_used = zmalloc_used_memory();
    struct redisMemOverhead *mh = zcalloc(sizeof(*mh));

    mh->total_allocated = zmalloc_used;
    mh->startup_allocated = server.initial_memory_usage;
    mh->peak_allocated = server.stat_peak_memory;
    mh->total_frag =
        (float)server.cron_malloc_stats.process_rss / server.cron_malloc_stats.zmalloc_used;
    mh->total_frag_bytes =
        server.cron_malloc_stats.process_rss - server.cron_malloc_stats.zmalloc_used;
    mh->allocator_frag =
        (float)server.cron_malloc_stats.allocator_active / server.cron_malloc_stats.allocator_allocated;
    mh->allocator_frag_bytes =
        server.cron_malloc_stats.allocator_active - server.cron_malloc_stats.allocator_allocated;
    mh->allocator_rss =
        (float)server.cron_malloc_stats.allocator_resident / server.cron_malloc_stats.allocator_active;
    mh->allocator_rss_bytes =
        server.cron_malloc_stats.allocator_resident - server.cron_malloc_stats.allocator_active;
    mh->rss_extra =
        (float)server.cron_malloc_stats.process_rss / server.cron_malloc_stats.allocator_resident;
    mh->rss_extra_bytes =
        server.cron_malloc_stats.process_rss - server.cron_malloc_stats.allocator_resident;

    mem_total += server.initial_memory_usage;

    mem = 0;
    if (server.repl_backlog)
        mem += zmalloc_size(server.repl_backlog);
    mh->repl_backlog = mem;
    mem_total += mem;

    mem = 0;
    if (listLength(server.slaves)) {
        listIter li;
        listNode *ln;

        listRewind(server.slaves,&li);
        while((ln = listNext(&li))) {
            client *c = listNodeValue(ln);
            mem += getClientOutputBufferMemoryUsage(c);
            mem += sdsAllocSize(c->querybuf);
            mem += sizeof(client);
        }
    }
    mh->clients_slaves = mem;
    mem_total+=mem;

    mem = 0;
    if (listLength(server.clients)) {
        listIter li;
        listNode *ln;

        listRewind(server.clients,&li);
        while((ln = listNext(&li))) {
            client *c = listNodeValue(ln);
            if (c->flags & CLIENT_SLAVE && !(c->flags & CLIENT_MONITOR))
                continue;
            mem += getClientOutputBufferMemoryUsage(c);
            mem += sdsAllocSize(c->querybuf);
            mem += sizeof(client);
        }
    }
    mh->clients_normal = mem;
    mem_total+=mem;

    mem = 0;
    if (server.aof_state != AOF_OFF) {
        mem += sdsalloc(server.aof_buf);
        mem += aofRewriteBufferSize();
    }
    mh->aof_buffer = mem;
    mem_total+=mem;

    mem = server.lua_scripts_mem;
    mem += dictSize(server.lua_scripts) * sizeof(dictEntry) +
        dictSlots(server.lua_scripts) * sizeof(dictEntry*);
    mem += dictSize(server.repl_scriptcache_dict) * sizeof(dictEntry) +
        dictSlots(server.repl_scriptcache_dict) * sizeof(dictEntry*);
    if (listLength(server.repl_scriptcache_fifo) > 0) {
        mem += listLength(server.repl_scriptcache_fifo) * (sizeof(listNode) + 
            sdsZmallocSize(listNodeValue(listFirst(server.repl_scriptcache_fifo))));
    }
    mh->lua_caches = mem;
    mem_total+=mem;

    for (j = 0; j < server.dbnum; j++) {
        redisDb *db = server.db+j;
        long long keyscount = dictSize(db->dict);
        if (keyscount==0) continue;

        mh->total_keys += keyscount;
        mh->db = zrealloc(mh->db,sizeof(mh->db[0])*(mh->num_dbs+1));
        mh->db[mh->num_dbs].dbid = j;

        mem = dictSize(db->dict) * sizeof(dictEntry) +
              dictSlots(db->dict) * sizeof(dictEntry*) +
              dictSize(db->dict) * sizeof(robj);
        mh->db[mh->num_dbs].overhead_ht_main = mem;
        mem_total+=mem;

        mem = dictSize(db->expires) * sizeof(dictEntry) +
              dictSlots(db->expires) * sizeof(dictEntry*);
        mh->db[mh->num_dbs].overhead_ht_expires = mem;
        mem_total+=mem;

        mh->num_dbs++;
    }

    mh->overhead_total = mem_total;
    mh->dataset = zmalloc_used - mem_total;
    mh->peak_perc = (float)zmalloc_used*100/mh->peak_allocated;

    /* Metrics computed after subtracting the startup memory from
     * the total memory. */
    size_t net_usage = 1;
    if (zmalloc_used > mh->startup_allocated)
        net_usage = zmalloc_used - mh->startup_allocated;
    mh->dataset_perc = (float)mh->dataset*100/net_usage;
    mh->bytes_per_key = mh->total_keys ? (net_usage / mh->total_keys) : 0;

    return mh;
}