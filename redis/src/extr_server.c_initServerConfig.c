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
struct TYPE_2__ {char* runid; int arch_bits; int sofd; int active_expire_enabled; int jemalloc_bg_thread; int aof_rewrite_time_last; int aof_rewrite_time_start; int aof_fd; int aof_selected_db; int next_client_id; int loading_process_events_interval_bytes; int masterport; int master_initial_offset; int repl_transfer_fd; char* assert_failed; char* assert_file; int lua_always_replicate_commands; scalar_t__ watchdog_period; scalar_t__ bug_report_start; scalar_t__ assert_line; int /*<<< orphan*/  tracking_table_max_fill; int /*<<< orphan*/  latency_monitor_threshold; int /*<<< orphan*/  slowlog_max_len; int /*<<< orphan*/  slowlog_log_slower_than; void* xgroupCommand; void* xclaimCommand; void* pexpireCommand; void* expireCommand; void* execCommand; void* sremCommand; void* zpopmaxCommand; void* zpopminCommand; void* rpopCommand; void* lpopCommand; void* lpushCommand; void* multiCommand; void* delCommand; void* orig_commands; void* commands; int /*<<< orphan*/ * client_obuf_limits; void* repl_no_slaves_since; int /*<<< orphan*/  repl_backlog_time_limit; scalar_t__ repl_backlog_off; scalar_t__ repl_backlog_idx; scalar_t__ repl_backlog_histlen; int /*<<< orphan*/  repl_backlog_size; int /*<<< orphan*/ * repl_backlog; scalar_t__ master_repl_offset; int /*<<< orphan*/  slave_announce_port; int /*<<< orphan*/  slave_announce_ip; int /*<<< orphan*/  slave_priority; int /*<<< orphan*/  repl_min_slaves_max_lag; int /*<<< orphan*/  repl_min_slaves_to_write; int /*<<< orphan*/  repl_timeout; int /*<<< orphan*/  repl_ping_slave_period; int /*<<< orphan*/  repl_diskless_sync_delay; int /*<<< orphan*/  repl_diskless_load; int /*<<< orphan*/  repl_diskless_sync; int /*<<< orphan*/  repl_disable_tcp_nodelay; scalar_t__ repl_down_since; int /*<<< orphan*/  repl_slave_lazy_flush; int /*<<< orphan*/  repl_slave_ignore_maxmemory; int /*<<< orphan*/  repl_slave_ro; int /*<<< orphan*/  repl_serve_stale_data; int /*<<< orphan*/  repl_syncio_timeout; int /*<<< orphan*/ * repl_transfer_s; int /*<<< orphan*/ * repl_transfer_tmpfile; int /*<<< orphan*/  repl_state; int /*<<< orphan*/ * cached_master; int /*<<< orphan*/ * master; int /*<<< orphan*/ * masterhost; int /*<<< orphan*/ * masterauth; int /*<<< orphan*/  lruclock; int /*<<< orphan*/  io_threads_do_reads; int /*<<< orphan*/  io_threads_num; int /*<<< orphan*/  lua_time_limit; int /*<<< orphan*/  always_show_logo; int /*<<< orphan*/  lazyfree_lazy_server_del; int /*<<< orphan*/  lazyfree_lazy_expire; int /*<<< orphan*/  lazyfree_lazy_eviction; void* migrate_cached_sockets; int /*<<< orphan*/  cluster_module_flags; int /*<<< orphan*/  cluster_announce_bus_port; int /*<<< orphan*/  cluster_announce_port; int /*<<< orphan*/  cluster_announce_ip; void* cluster_configfile; int /*<<< orphan*/  cluster_slave_no_failover; int /*<<< orphan*/  cluster_require_full_coverage; int /*<<< orphan*/  cluster_slave_validity_factor; int /*<<< orphan*/  cluster_migration_barrier; int /*<<< orphan*/  cluster_node_timeout; scalar_t__ cluster_enabled; scalar_t__ shutdown_asap; int /*<<< orphan*/  stream_node_max_entries; int /*<<< orphan*/  stream_node_max_bytes; int /*<<< orphan*/  hll_sparse_max_bytes; int /*<<< orphan*/  zset_max_ziplist_value; int /*<<< orphan*/  zset_max_ziplist_entries; int /*<<< orphan*/  set_max_intset_entries; int /*<<< orphan*/  list_compress_depth; int /*<<< orphan*/  list_max_ziplist_size; int /*<<< orphan*/  hash_max_ziplist_value; int /*<<< orphan*/  hash_max_ziplist_entries; int /*<<< orphan*/  lfu_decay_time; int /*<<< orphan*/  lfu_log_factor; int /*<<< orphan*/  maxmemory_samples; int /*<<< orphan*/  maxmemory_policy; int /*<<< orphan*/  maxmemory; int /*<<< orphan*/  blocked_clients_by_type; scalar_t__ blocked_clients; int /*<<< orphan*/  maxclients; scalar_t__ notify_keyspace_events; scalar_t__ active_defrag_running; int /*<<< orphan*/  activerehashing; int /*<<< orphan*/  stop_writes_on_bgsave_err; int /*<<< orphan*/  rdb_checksum; int /*<<< orphan*/  rdb_compression; void* acl_filename; void* aof_filename; void* rdb_filename; int /*<<< orphan*/ * pidfile; int /*<<< orphan*/  aof_use_rdb_preamble; int /*<<< orphan*/  aof_load_truncated; int /*<<< orphan*/  key_load_delay; int /*<<< orphan*/  rdb_key_save_delay; int /*<<< orphan*/  rdb_save_incremental_fsync; int /*<<< orphan*/  aof_rewrite_incremental_fsync; scalar_t__ aof_flush_postponed_start; scalar_t__ aof_delayed_fsync; int /*<<< orphan*/  aof_lastbgrewrite_status; void* aof_last_fsync; scalar_t__ aof_flush_sleep; scalar_t__ aof_rewrite_scheduled; scalar_t__ aof_rewrite_base_size; int /*<<< orphan*/  aof_rewrite_min_size; int /*<<< orphan*/  aof_rewrite_perc; int /*<<< orphan*/  aof_no_fsync_on_rewrite; int /*<<< orphan*/  aof_fsync; int /*<<< orphan*/  aof_state; int /*<<< orphan*/  supervised_mode; scalar_t__ supervised; int /*<<< orphan*/  daemonize; int /*<<< orphan*/  syslog_facility; void* syslog_ident; int /*<<< orphan*/  syslog_enabled; void* logfile; scalar_t__ loading; int /*<<< orphan*/ * saveparams; int /*<<< orphan*/  client_max_querybuf_len; int /*<<< orphan*/  proto_max_bulk_len; int /*<<< orphan*/  active_defrag_max_scan_fields; int /*<<< orphan*/  active_defrag_cycle_max; int /*<<< orphan*/  active_defrag_cycle_min; int /*<<< orphan*/  active_defrag_threshold_upper; int /*<<< orphan*/  active_defrag_threshold_lower; int /*<<< orphan*/  active_defrag_ignore_bytes; int /*<<< orphan*/  active_defrag_enabled; int /*<<< orphan*/  tcpkeepalive; int /*<<< orphan*/  maxidletime; int /*<<< orphan*/  verbosity; int /*<<< orphan*/  dbnum; int /*<<< orphan*/  gopher_enabled; int /*<<< orphan*/  protected_mode; scalar_t__ tlsfd_count; scalar_t__ ipfd_count; int /*<<< orphan*/  unixsocketperm; int /*<<< orphan*/ * unixsocket; scalar_t__ bindaddr_count; int /*<<< orphan*/  tcp_backlog; int /*<<< orphan*/  tls_port; int /*<<< orphan*/  port; int /*<<< orphan*/  dynamic_hz; int /*<<< orphan*/  config_hz; int /*<<< orphan*/  hz; int /*<<< orphan*/ * executable; int /*<<< orphan*/ * configfile; int /*<<< orphan*/  timezone; } ;

/* Variables and functions */
 int /*<<< orphan*/  AOF_OFF ; 
 int /*<<< orphan*/  AOF_REWRITE_MIN_SIZE ; 
 int /*<<< orphan*/  AOF_REWRITE_PERC ; 
 int CLIENT_TYPE_OBUF_COUNT ; 
 int /*<<< orphan*/  CLUSTER_DEFAULT_MIGRATION_BARRIER ; 
 int /*<<< orphan*/  CLUSTER_DEFAULT_NODE_TIMEOUT ; 
 int /*<<< orphan*/  CLUSTER_DEFAULT_REQUIRE_FULL_COVERAGE ; 
 int /*<<< orphan*/  CLUSTER_DEFAULT_SLAVE_NO_FAILOVER ; 
 int /*<<< orphan*/  CLUSTER_DEFAULT_SLAVE_VALIDITY ; 
 int /*<<< orphan*/  CLUSTER_MODULE_FLAG_NONE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_ACL_FILENAME ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_ACTIVE_DEFRAG ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_ACTIVE_REHASHING ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_ALWAYS_SHOW_LOGO ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_AOF_FILENAME ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_AOF_FSYNC ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_AOF_LOAD_TRUNCATED ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_AOF_NO_FSYNC_ON_REWRITE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_AOF_REWRITE_INCREMENTAL_FSYNC ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_AOF_USE_RDB_PREAMBLE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_CLIENT_TIMEOUT ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_CLUSTER_ANNOUNCE_BUS_PORT ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_CLUSTER_ANNOUNCE_IP ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_CLUSTER_ANNOUNCE_PORT ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_CLUSTER_CONFIG_FILE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_DAEMONIZE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_DBNUM ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_DEFRAG_CYCLE_MAX ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_DEFRAG_CYCLE_MIN ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_DEFRAG_IGNORE_BYTES ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_DEFRAG_MAX_SCAN_FIELDS ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_DEFRAG_THRESHOLD_LOWER ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_DEFRAG_THRESHOLD_UPPER ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_DYNAMIC_HZ ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_GOPHER_ENABLED ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_HLL_SPARSE_MAX_BYTES ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_HZ ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_IO_THREADS_DO_READS ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_IO_THREADS_NUM ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_KEY_LOAD_DELAY ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_LATENCY_MONITOR_THRESHOLD ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_LAZYFREE_LAZY_EVICTION ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_LAZYFREE_LAZY_EXPIRE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_LAZYFREE_LAZY_SERVER_DEL ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_LFU_DECAY_TIME ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_LFU_LOG_FACTOR ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_LOGFILE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_MAXMEMORY ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_MAXMEMORY_POLICY ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_MAXMEMORY_SAMPLES ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_MAX_CLIENTS ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_MIN_SLAVES_MAX_LAG ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_MIN_SLAVES_TO_WRITE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_PROTECTED_MODE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_PROTO_MAX_BULK_LEN ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_RDB_CHECKSUM ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_RDB_COMPRESSION ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_RDB_FILENAME ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_RDB_KEY_SAVE_DELAY ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_RDB_SAVE_INCREMENTAL_FSYNC ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_REPL_BACKLOG_SIZE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_REPL_BACKLOG_TIME_LIMIT ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_REPL_DISABLE_TCP_NODELAY ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_REPL_DISKLESS_LOAD ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_REPL_DISKLESS_SYNC ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_REPL_DISKLESS_SYNC_DELAY ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_REPL_PING_SLAVE_PERIOD ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_REPL_TIMEOUT ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_SERVER_PORT ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_SERVER_TLS_PORT ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_SLAVE_ANNOUNCE_IP ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_SLAVE_ANNOUNCE_PORT ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_SLAVE_IGNORE_MAXMEMORY ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_SLAVE_LAZY_FLUSH ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_SLAVE_PRIORITY ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_SLAVE_READ_ONLY ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_SLAVE_SERVE_STALE_DATA ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_SLOWLOG_LOG_SLOWER_THAN ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_SLOWLOG_MAX_LEN ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_STOP_WRITES_ON_BGSAVE_ERROR ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_SYSLOG_ENABLED ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_SYSLOG_IDENT ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_TCP_BACKLOG ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_TCP_KEEPALIVE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_TRACKING_TABLE_MAX_FILL ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_UNIX_SOCKET_PERM ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_VERBOSITY ; 
 int /*<<< orphan*/  CONFIG_REPL_SYNCIO_TIMEOUT ; 
 size_t CONFIG_RUN_ID_SIZE ; 
 int /*<<< orphan*/  C_OK ; 
 int /*<<< orphan*/  LOG_LOCAL0 ; 
 int /*<<< orphan*/  LUA_SCRIPT_TIME_LIMIT ; 
 int /*<<< orphan*/  OBJ_HASH_MAX_ZIPLIST_ENTRIES ; 
 int /*<<< orphan*/  OBJ_HASH_MAX_ZIPLIST_VALUE ; 
 int /*<<< orphan*/  OBJ_LIST_COMPRESS_DEPTH ; 
 int /*<<< orphan*/  OBJ_LIST_MAX_ZIPLIST_SIZE ; 
 int /*<<< orphan*/  OBJ_SET_MAX_INTSET_ENTRIES ; 
 int /*<<< orphan*/  OBJ_STREAM_NODE_MAX_BYTES ; 
 int /*<<< orphan*/  OBJ_STREAM_NODE_MAX_ENTRIES ; 
 int /*<<< orphan*/  OBJ_ZSET_MAX_ZIPLIST_ENTRIES ; 
 int /*<<< orphan*/  OBJ_ZSET_MAX_ZIPLIST_VALUE ; 
 int /*<<< orphan*/  PROTO_MAX_QUERYBUF_LEN ; 
 int /*<<< orphan*/  REPL_STATE_NONE ; 
 double R_Nan ; 
 double R_NegInf ; 
 double R_PosInf ; 
 double R_Zero ; 
 int /*<<< orphan*/  SUPERVISED_NONE ; 
 int /*<<< orphan*/  appendServerSaveParams (int,int) ; 
 int /*<<< orphan*/  changeReplicationId () ; 
 int /*<<< orphan*/  clearReplicationId2 () ; 
 int /*<<< orphan*/ * clientBufferLimitsDefaults ; 
 int /*<<< orphan*/  commandTableDictType ; 
 void* dictCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getLRUClock () ; 
 int /*<<< orphan*/  getRandomHexChars (char*,size_t) ; 
 int /*<<< orphan*/  getTimeZone () ; 
 void* lookupCommandByCString (char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  migrateCacheDictType ; 
 int /*<<< orphan*/  populateCommandTable () ; 
 int /*<<< orphan*/  resetServerSaveParams () ; 
 TYPE_1__ server ; 
 void* time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  updateCachedTime (int) ; 
 void* zstrdup (int /*<<< orphan*/ ) ; 

void initServerConfig(void) {
    int j;

    updateCachedTime(1);
    getRandomHexChars(server.runid,CONFIG_RUN_ID_SIZE);
    server.runid[CONFIG_RUN_ID_SIZE] = '\0';
    changeReplicationId();
    clearReplicationId2();
    server.timezone = getTimeZone(); /* Initialized by tzset(). */
    server.configfile = NULL;
    server.executable = NULL;
    server.hz = server.config_hz = CONFIG_DEFAULT_HZ;
    server.dynamic_hz = CONFIG_DEFAULT_DYNAMIC_HZ;
    server.arch_bits = (sizeof(long) == 8) ? 64 : 32;
    server.port = CONFIG_DEFAULT_SERVER_PORT;
    server.tls_port = CONFIG_DEFAULT_SERVER_TLS_PORT;
    server.tcp_backlog = CONFIG_DEFAULT_TCP_BACKLOG;
    server.bindaddr_count = 0;
    server.unixsocket = NULL;
    server.unixsocketperm = CONFIG_DEFAULT_UNIX_SOCKET_PERM;
    server.ipfd_count = 0;
    server.tlsfd_count = 0;
    server.sofd = -1;
    server.protected_mode = CONFIG_DEFAULT_PROTECTED_MODE;
    server.gopher_enabled = CONFIG_DEFAULT_GOPHER_ENABLED;
    server.dbnum = CONFIG_DEFAULT_DBNUM;
    server.verbosity = CONFIG_DEFAULT_VERBOSITY;
    server.maxidletime = CONFIG_DEFAULT_CLIENT_TIMEOUT;
    server.tcpkeepalive = CONFIG_DEFAULT_TCP_KEEPALIVE;
    server.active_expire_enabled = 1;
    server.jemalloc_bg_thread = 1;
    server.active_defrag_enabled = CONFIG_DEFAULT_ACTIVE_DEFRAG;
    server.active_defrag_ignore_bytes = CONFIG_DEFAULT_DEFRAG_IGNORE_BYTES;
    server.active_defrag_threshold_lower = CONFIG_DEFAULT_DEFRAG_THRESHOLD_LOWER;
    server.active_defrag_threshold_upper = CONFIG_DEFAULT_DEFRAG_THRESHOLD_UPPER;
    server.active_defrag_cycle_min = CONFIG_DEFAULT_DEFRAG_CYCLE_MIN;
    server.active_defrag_cycle_max = CONFIG_DEFAULT_DEFRAG_CYCLE_MAX;
    server.active_defrag_max_scan_fields = CONFIG_DEFAULT_DEFRAG_MAX_SCAN_FIELDS;
    server.proto_max_bulk_len = CONFIG_DEFAULT_PROTO_MAX_BULK_LEN;
    server.client_max_querybuf_len = PROTO_MAX_QUERYBUF_LEN;
    server.saveparams = NULL;
    server.loading = 0;
    server.logfile = zstrdup(CONFIG_DEFAULT_LOGFILE);
    server.syslog_enabled = CONFIG_DEFAULT_SYSLOG_ENABLED;
    server.syslog_ident = zstrdup(CONFIG_DEFAULT_SYSLOG_IDENT);
    server.syslog_facility = LOG_LOCAL0;
    server.daemonize = CONFIG_DEFAULT_DAEMONIZE;
    server.supervised = 0;
    server.supervised_mode = SUPERVISED_NONE;
    server.aof_state = AOF_OFF;
    server.aof_fsync = CONFIG_DEFAULT_AOF_FSYNC;
    server.aof_no_fsync_on_rewrite = CONFIG_DEFAULT_AOF_NO_FSYNC_ON_REWRITE;
    server.aof_rewrite_perc = AOF_REWRITE_PERC;
    server.aof_rewrite_min_size = AOF_REWRITE_MIN_SIZE;
    server.aof_rewrite_base_size = 0;
    server.aof_rewrite_scheduled = 0;
    server.aof_flush_sleep = 0;
    server.aof_last_fsync = time(NULL);
    server.aof_rewrite_time_last = -1;
    server.aof_rewrite_time_start = -1;
    server.aof_lastbgrewrite_status = C_OK;
    server.aof_delayed_fsync = 0;
    server.aof_fd = -1;
    server.aof_selected_db = -1; /* Make sure the first time will not match */
    server.aof_flush_postponed_start = 0;
    server.aof_rewrite_incremental_fsync = CONFIG_DEFAULT_AOF_REWRITE_INCREMENTAL_FSYNC;
    server.rdb_save_incremental_fsync = CONFIG_DEFAULT_RDB_SAVE_INCREMENTAL_FSYNC;
    server.rdb_key_save_delay = CONFIG_DEFAULT_RDB_KEY_SAVE_DELAY;
    server.key_load_delay = CONFIG_DEFAULT_KEY_LOAD_DELAY;
    server.aof_load_truncated = CONFIG_DEFAULT_AOF_LOAD_TRUNCATED;
    server.aof_use_rdb_preamble = CONFIG_DEFAULT_AOF_USE_RDB_PREAMBLE;
    server.pidfile = NULL;
    server.rdb_filename = zstrdup(CONFIG_DEFAULT_RDB_FILENAME);
    server.aof_filename = zstrdup(CONFIG_DEFAULT_AOF_FILENAME);
    server.acl_filename = zstrdup(CONFIG_DEFAULT_ACL_FILENAME);
    server.rdb_compression = CONFIG_DEFAULT_RDB_COMPRESSION;
    server.rdb_checksum = CONFIG_DEFAULT_RDB_CHECKSUM;
    server.stop_writes_on_bgsave_err = CONFIG_DEFAULT_STOP_WRITES_ON_BGSAVE_ERROR;
    server.activerehashing = CONFIG_DEFAULT_ACTIVE_REHASHING;
    server.active_defrag_running = 0;
    server.notify_keyspace_events = 0;
    server.maxclients = CONFIG_DEFAULT_MAX_CLIENTS;
    server.blocked_clients = 0;
    memset(server.blocked_clients_by_type,0,
           sizeof(server.blocked_clients_by_type));
    server.maxmemory = CONFIG_DEFAULT_MAXMEMORY;
    server.maxmemory_policy = CONFIG_DEFAULT_MAXMEMORY_POLICY;
    server.maxmemory_samples = CONFIG_DEFAULT_MAXMEMORY_SAMPLES;
    server.lfu_log_factor = CONFIG_DEFAULT_LFU_LOG_FACTOR;
    server.lfu_decay_time = CONFIG_DEFAULT_LFU_DECAY_TIME;
    server.hash_max_ziplist_entries = OBJ_HASH_MAX_ZIPLIST_ENTRIES;
    server.hash_max_ziplist_value = OBJ_HASH_MAX_ZIPLIST_VALUE;
    server.list_max_ziplist_size = OBJ_LIST_MAX_ZIPLIST_SIZE;
    server.list_compress_depth = OBJ_LIST_COMPRESS_DEPTH;
    server.set_max_intset_entries = OBJ_SET_MAX_INTSET_ENTRIES;
    server.zset_max_ziplist_entries = OBJ_ZSET_MAX_ZIPLIST_ENTRIES;
    server.zset_max_ziplist_value = OBJ_ZSET_MAX_ZIPLIST_VALUE;
    server.hll_sparse_max_bytes = CONFIG_DEFAULT_HLL_SPARSE_MAX_BYTES;
    server.stream_node_max_bytes = OBJ_STREAM_NODE_MAX_BYTES;
    server.stream_node_max_entries = OBJ_STREAM_NODE_MAX_ENTRIES;
    server.shutdown_asap = 0;
    server.cluster_enabled = 0;
    server.cluster_node_timeout = CLUSTER_DEFAULT_NODE_TIMEOUT;
    server.cluster_migration_barrier = CLUSTER_DEFAULT_MIGRATION_BARRIER;
    server.cluster_slave_validity_factor = CLUSTER_DEFAULT_SLAVE_VALIDITY;
    server.cluster_require_full_coverage = CLUSTER_DEFAULT_REQUIRE_FULL_COVERAGE;
    server.cluster_slave_no_failover = CLUSTER_DEFAULT_SLAVE_NO_FAILOVER;
    server.cluster_configfile = zstrdup(CONFIG_DEFAULT_CLUSTER_CONFIG_FILE);
    server.cluster_announce_ip = CONFIG_DEFAULT_CLUSTER_ANNOUNCE_IP;
    server.cluster_announce_port = CONFIG_DEFAULT_CLUSTER_ANNOUNCE_PORT;
    server.cluster_announce_bus_port = CONFIG_DEFAULT_CLUSTER_ANNOUNCE_BUS_PORT;
    server.cluster_module_flags = CLUSTER_MODULE_FLAG_NONE;
    server.migrate_cached_sockets = dictCreate(&migrateCacheDictType,NULL);
    server.next_client_id = 1; /* Client IDs, start from 1 .*/
    server.loading_process_events_interval_bytes = (1024*1024*2);
    server.lazyfree_lazy_eviction = CONFIG_DEFAULT_LAZYFREE_LAZY_EVICTION;
    server.lazyfree_lazy_expire = CONFIG_DEFAULT_LAZYFREE_LAZY_EXPIRE;
    server.lazyfree_lazy_server_del = CONFIG_DEFAULT_LAZYFREE_LAZY_SERVER_DEL;
    server.always_show_logo = CONFIG_DEFAULT_ALWAYS_SHOW_LOGO;
    server.lua_time_limit = LUA_SCRIPT_TIME_LIMIT;
    server.io_threads_num = CONFIG_DEFAULT_IO_THREADS_NUM;
    server.io_threads_do_reads = CONFIG_DEFAULT_IO_THREADS_DO_READS;

    server.lruclock = getLRUClock();
    resetServerSaveParams();

    appendServerSaveParams(60*60,1);  /* save after 1 hour and 1 change */
    appendServerSaveParams(300,100);  /* save after 5 minutes and 100 changes */
    appendServerSaveParams(60,10000); /* save after 1 minute and 10000 changes */

    /* Replication related */
    server.masterauth = NULL;
    server.masterhost = NULL;
    server.masterport = 6379;
    server.master = NULL;
    server.cached_master = NULL;
    server.master_initial_offset = -1;
    server.repl_state = REPL_STATE_NONE;
    server.repl_transfer_tmpfile = NULL;
    server.repl_transfer_fd = -1;
    server.repl_transfer_s = NULL;
    server.repl_syncio_timeout = CONFIG_REPL_SYNCIO_TIMEOUT;
    server.repl_serve_stale_data = CONFIG_DEFAULT_SLAVE_SERVE_STALE_DATA;
    server.repl_slave_ro = CONFIG_DEFAULT_SLAVE_READ_ONLY;
    server.repl_slave_ignore_maxmemory = CONFIG_DEFAULT_SLAVE_IGNORE_MAXMEMORY;
    server.repl_slave_lazy_flush = CONFIG_DEFAULT_SLAVE_LAZY_FLUSH;
    server.repl_down_since = 0; /* Never connected, repl is down since EVER. */
    server.repl_disable_tcp_nodelay = CONFIG_DEFAULT_REPL_DISABLE_TCP_NODELAY;
    server.repl_diskless_sync = CONFIG_DEFAULT_REPL_DISKLESS_SYNC;
    server.repl_diskless_load = CONFIG_DEFAULT_REPL_DISKLESS_LOAD;
    server.repl_diskless_sync_delay = CONFIG_DEFAULT_REPL_DISKLESS_SYNC_DELAY;
    server.repl_ping_slave_period = CONFIG_DEFAULT_REPL_PING_SLAVE_PERIOD;
    server.repl_timeout = CONFIG_DEFAULT_REPL_TIMEOUT;
    server.repl_min_slaves_to_write = CONFIG_DEFAULT_MIN_SLAVES_TO_WRITE;
    server.repl_min_slaves_max_lag = CONFIG_DEFAULT_MIN_SLAVES_MAX_LAG;
    server.slave_priority = CONFIG_DEFAULT_SLAVE_PRIORITY;
    server.slave_announce_ip = CONFIG_DEFAULT_SLAVE_ANNOUNCE_IP;
    server.slave_announce_port = CONFIG_DEFAULT_SLAVE_ANNOUNCE_PORT;
    server.master_repl_offset = 0;

    /* Replication partial resync backlog */
    server.repl_backlog = NULL;
    server.repl_backlog_size = CONFIG_DEFAULT_REPL_BACKLOG_SIZE;
    server.repl_backlog_histlen = 0;
    server.repl_backlog_idx = 0;
    server.repl_backlog_off = 0;
    server.repl_backlog_time_limit = CONFIG_DEFAULT_REPL_BACKLOG_TIME_LIMIT;
    server.repl_no_slaves_since = time(NULL);

    /* Client output buffer limits */
    for (j = 0; j < CLIENT_TYPE_OBUF_COUNT; j++)
        server.client_obuf_limits[j] = clientBufferLimitsDefaults[j];

    /* Double constants initialization */
    R_Zero = 0.0;
    R_PosInf = 1.0/R_Zero;
    R_NegInf = -1.0/R_Zero;
    R_Nan = R_Zero/R_Zero;

    /* Command table -- we initiialize it here as it is part of the
     * initial configuration, since command names may be changed via
     * redis.conf using the rename-command directive. */
    server.commands = dictCreate(&commandTableDictType,NULL);
    server.orig_commands = dictCreate(&commandTableDictType,NULL);
    populateCommandTable();
    server.delCommand = lookupCommandByCString("del");
    server.multiCommand = lookupCommandByCString("multi");
    server.lpushCommand = lookupCommandByCString("lpush");
    server.lpopCommand = lookupCommandByCString("lpop");
    server.rpopCommand = lookupCommandByCString("rpop");
    server.zpopminCommand = lookupCommandByCString("zpopmin");
    server.zpopmaxCommand = lookupCommandByCString("zpopmax");
    server.sremCommand = lookupCommandByCString("srem");
    server.execCommand = lookupCommandByCString("exec");
    server.expireCommand = lookupCommandByCString("expire");
    server.pexpireCommand = lookupCommandByCString("pexpire");
    server.xclaimCommand = lookupCommandByCString("xclaim");
    server.xgroupCommand = lookupCommandByCString("xgroup");

    /* Slow log */
    server.slowlog_log_slower_than = CONFIG_DEFAULT_SLOWLOG_LOG_SLOWER_THAN;
    server.slowlog_max_len = CONFIG_DEFAULT_SLOWLOG_MAX_LEN;

    /* Latency monitor */
    server.latency_monitor_threshold = CONFIG_DEFAULT_LATENCY_MONITOR_THRESHOLD;

    /* Tracking. */
    server.tracking_table_max_fill = CONFIG_DEFAULT_TRACKING_TABLE_MAX_FILL;

    /* Debugging */
    server.assert_failed = "<no assertion failed>";
    server.assert_file = "<no file>";
    server.assert_line = 0;
    server.bug_report_start = 0;
    server.watchdog_period = 0;

    /* By default we want scripts to be always replicated by effects
     * (single commands executed by the script), and not by sending the
     * script to the slave / AOF. This is the new way starting from
     * Redis 5. However it is possible to revert it via redis.conf. */
    server.lua_always_replicate_commands = 1;
}