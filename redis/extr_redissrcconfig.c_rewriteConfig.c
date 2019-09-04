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
struct TYPE_2__ {int daemonize; int syslog_enabled; int stop_writes_on_bgsave_err; int rdb_compression; int rdb_checksum; int repl_serve_stale_data; int repl_slave_ro; int repl_slave_ignore_maxmemory; int repl_disable_tcp_nodelay; int repl_diskless_sync; scalar_t__ aof_state; int aof_no_fsync_on_rewrite; int cluster_enabled; int cluster_require_full_coverage; int cluster_slave_no_failover; int activerehashing; int active_defrag_enabled; int protected_mode; int gopher_enabled; int aof_rewrite_incremental_fsync; int rdb_save_incremental_fsync; int aof_load_truncated; int aof_use_rdb_preamble; int lazyfree_lazy_eviction; int lazyfree_lazy_expire; int lazyfree_lazy_server_del; int repl_slave_lazy_flush; int dynamic_hz; int /*<<< orphan*/  configfile; scalar_t__ sentinel_mode; int /*<<< orphan*/  supervised_mode; int /*<<< orphan*/  config_hz; int /*<<< orphan*/  hll_sparse_max_bytes; int /*<<< orphan*/  zset_max_ziplist_value; int /*<<< orphan*/  zset_max_ziplist_entries; int /*<<< orphan*/  set_max_intset_entries; int /*<<< orphan*/  list_compress_depth; int /*<<< orphan*/  list_max_ziplist_size; int /*<<< orphan*/  stream_node_max_entries; int /*<<< orphan*/  stream_node_max_bytes; int /*<<< orphan*/  hash_max_ziplist_value; int /*<<< orphan*/  hash_max_ziplist_entries; int /*<<< orphan*/  slowlog_max_len; int /*<<< orphan*/  latency_monitor_threshold; int /*<<< orphan*/  slowlog_log_slower_than; int /*<<< orphan*/  cluster_slave_validity_factor; int /*<<< orphan*/  cluster_migration_barrier; int /*<<< orphan*/  cluster_node_timeout; int /*<<< orphan*/  cluster_configfile; int /*<<< orphan*/  lua_time_limit; int /*<<< orphan*/  aof_rewrite_min_size; int /*<<< orphan*/  aof_rewrite_perc; int /*<<< orphan*/  aof_fsync; int /*<<< orphan*/  aof_filename; int /*<<< orphan*/  active_defrag_max_scan_fields; int /*<<< orphan*/  active_defrag_cycle_max; int /*<<< orphan*/  active_defrag_cycle_min; int /*<<< orphan*/  active_defrag_ignore_bytes; int /*<<< orphan*/  active_defrag_threshold_upper; int /*<<< orphan*/  active_defrag_threshold_lower; int /*<<< orphan*/  lfu_decay_time; int /*<<< orphan*/  lfu_log_factor; int /*<<< orphan*/  maxmemory_samples; int /*<<< orphan*/  maxmemory_policy; int /*<<< orphan*/  client_max_querybuf_len; int /*<<< orphan*/  proto_max_bulk_len; int /*<<< orphan*/  maxmemory; int /*<<< orphan*/  maxclients; int /*<<< orphan*/  repl_min_slaves_max_lag; int /*<<< orphan*/  repl_min_slaves_to_write; int /*<<< orphan*/  slave_priority; int /*<<< orphan*/  repl_diskless_sync_delay; int /*<<< orphan*/  repl_backlog_time_limit; int /*<<< orphan*/  repl_backlog_size; int /*<<< orphan*/  repl_timeout; int /*<<< orphan*/  repl_ping_slave_period; int /*<<< orphan*/  cluster_announce_ip; int /*<<< orphan*/  masterauth; int /*<<< orphan*/  masteruser; int /*<<< orphan*/  slave_announce_ip; int /*<<< orphan*/  rdb_filename; int /*<<< orphan*/  dbnum; int /*<<< orphan*/  syslog_ident; int /*<<< orphan*/  acl_filename; int /*<<< orphan*/  logfile; int /*<<< orphan*/  verbosity; int /*<<< orphan*/  slave_announce_port; int /*<<< orphan*/  tcpkeepalive; int /*<<< orphan*/  maxidletime; int /*<<< orphan*/  unixsocketperm; int /*<<< orphan*/  unixsocket; int /*<<< orphan*/  tcp_backlog; int /*<<< orphan*/  cluster_announce_bus_port; int /*<<< orphan*/  cluster_announce_port; int /*<<< orphan*/  port; int /*<<< orphan*/  pidfile; } ;

/* Variables and functions */
 scalar_t__ AOF_OFF ; 
 int /*<<< orphan*/  AOF_REWRITE_MIN_SIZE ; 
 int /*<<< orphan*/  AOF_REWRITE_PERC ; 
 int /*<<< orphan*/  CLUSTER_DEFAULT_MIGRATION_BARRIER ; 
 int /*<<< orphan*/  CLUSTER_DEFAULT_NODE_TIMEOUT ; 
 int /*<<< orphan*/  CLUSTER_DEFAULT_REQUIRE_FULL_COVERAGE ; 
 int /*<<< orphan*/  CLUSTER_DEFAULT_SLAVE_NO_FAILOVER ; 
 int /*<<< orphan*/  CLUSTER_DEFAULT_SLAVE_VALIDITY ; 
 int /*<<< orphan*/ * CONFIG_DEFAULT_ACL_FILENAME ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_ACTIVE_DEFRAG ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_ACTIVE_REHASHING ; 
 int /*<<< orphan*/ * CONFIG_DEFAULT_AOF_FILENAME ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_AOF_FSYNC ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_AOF_LOAD_TRUNCATED ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_AOF_NO_FSYNC_ON_REWRITE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_AOF_REWRITE_INCREMENTAL_FSYNC ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_AOF_USE_RDB_PREAMBLE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_CLIENT_TIMEOUT ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_CLUSTER_ANNOUNCE_BUS_PORT ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_CLUSTER_ANNOUNCE_PORT ; 
 int /*<<< orphan*/ * CONFIG_DEFAULT_CLUSTER_CONFIG_FILE ; 
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
 int /*<<< orphan*/  CONFIG_DEFAULT_LATENCY_MONITOR_THRESHOLD ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_LAZYFREE_LAZY_EVICTION ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_LAZYFREE_LAZY_EXPIRE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_LAZYFREE_LAZY_SERVER_DEL ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_LFU_DECAY_TIME ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_LFU_LOG_FACTOR ; 
 int /*<<< orphan*/ * CONFIG_DEFAULT_LOGFILE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_MAXMEMORY ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_MAXMEMORY_POLICY ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_MAXMEMORY_SAMPLES ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_MAX_CLIENTS ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_MIN_SLAVES_MAX_LAG ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_MIN_SLAVES_TO_WRITE ; 
 int /*<<< orphan*/ * CONFIG_DEFAULT_PID_FILE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_PROTECTED_MODE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_PROTO_MAX_BULK_LEN ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_RDB_CHECKSUM ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_RDB_COMPRESSION ; 
 int /*<<< orphan*/ * CONFIG_DEFAULT_RDB_FILENAME ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_RDB_SAVE_INCREMENTAL_FSYNC ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_REPL_BACKLOG_SIZE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_REPL_BACKLOG_TIME_LIMIT ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_REPL_DISABLE_TCP_NODELAY ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_REPL_DISKLESS_SYNC ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_REPL_DISKLESS_SYNC_DELAY ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_REPL_PING_SLAVE_PERIOD ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_REPL_TIMEOUT ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_SERVER_PORT ; 
 int /*<<< orphan*/ * CONFIG_DEFAULT_SLAVE_ANNOUNCE_IP ; 
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
 int /*<<< orphan*/ * CONFIG_DEFAULT_SYSLOG_IDENT ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_TCP_BACKLOG ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_TCP_KEEPALIVE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_UNIX_SOCKET_PERM ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_VERBOSITY ; 
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
 int /*<<< orphan*/  SUPERVISED_NONE ; 
 int /*<<< orphan*/  aof_fsync_enum ; 
 int /*<<< orphan*/  loglevel_enum ; 
 int /*<<< orphan*/  maxmemory_policy_enum ; 
 int /*<<< orphan*/  rewriteConfigBindOption (struct rewriteConfigState*) ; 
 int /*<<< orphan*/  rewriteConfigBytesOption (struct rewriteConfigState*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rewriteConfigClientoutputbufferlimitOption (struct rewriteConfigState*) ; 
 int /*<<< orphan*/  rewriteConfigDirOption (struct rewriteConfigState*) ; 
 int /*<<< orphan*/  rewriteConfigEnumOption (struct rewriteConfigState*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rewriteConfigGetContentFromState (struct rewriteConfigState*) ; 
 int /*<<< orphan*/  rewriteConfigNotifykeyspaceeventsOption (struct rewriteConfigState*) ; 
 int /*<<< orphan*/  rewriteConfigNumericalOption (struct rewriteConfigState*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rewriteConfigOctalOption (struct rewriteConfigState*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rewriteConfigOverwriteFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rewriteConfigState* rewriteConfigReadOldFile (char*) ; 
 int /*<<< orphan*/  rewriteConfigReleaseState (struct rewriteConfigState*) ; 
 int /*<<< orphan*/  rewriteConfigRemoveOrphaned (struct rewriteConfigState*) ; 
 int /*<<< orphan*/  rewriteConfigRequirepassOption (struct rewriteConfigState*,char*) ; 
 int /*<<< orphan*/  rewriteConfigSaveOption (struct rewriteConfigState*) ; 
 int /*<<< orphan*/  rewriteConfigSentinelOption (struct rewriteConfigState*) ; 
 int /*<<< orphan*/  rewriteConfigSlaveofOption (struct rewriteConfigState*,char*) ; 
 int /*<<< orphan*/  rewriteConfigStringOption (struct rewriteConfigState*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewriteConfigSyslogfacilityOption (struct rewriteConfigState*) ; 
 int /*<<< orphan*/  rewriteConfigUserOption (struct rewriteConfigState*) ; 
 int /*<<< orphan*/  rewriteConfigYesNoOption (struct rewriteConfigState*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  supervised_mode_enum ; 

int rewriteConfig(char *path) {
    struct rewriteConfigState *state;
    sds newcontent;
    int retval;

    /* Step 1: read the old config into our rewrite state. */
    if ((state = rewriteConfigReadOldFile(path)) == NULL) return -1;

    /* Step 2: rewrite every single option, replacing or appending it inside
     * the rewrite state. */

    rewriteConfigYesNoOption(state,"daemonize",server.daemonize,0);
    rewriteConfigStringOption(state,"pidfile",server.pidfile,CONFIG_DEFAULT_PID_FILE);
    rewriteConfigNumericalOption(state,"port",server.port,CONFIG_DEFAULT_SERVER_PORT);
    rewriteConfigNumericalOption(state,"cluster-announce-port",server.cluster_announce_port,CONFIG_DEFAULT_CLUSTER_ANNOUNCE_PORT);
    rewriteConfigNumericalOption(state,"cluster-announce-bus-port",server.cluster_announce_bus_port,CONFIG_DEFAULT_CLUSTER_ANNOUNCE_BUS_PORT);
    rewriteConfigNumericalOption(state,"tcp-backlog",server.tcp_backlog,CONFIG_DEFAULT_TCP_BACKLOG);
    rewriteConfigBindOption(state);
    rewriteConfigStringOption(state,"unixsocket",server.unixsocket,NULL);
    rewriteConfigOctalOption(state,"unixsocketperm",server.unixsocketperm,CONFIG_DEFAULT_UNIX_SOCKET_PERM);
    rewriteConfigNumericalOption(state,"timeout",server.maxidletime,CONFIG_DEFAULT_CLIENT_TIMEOUT);
    rewriteConfigNumericalOption(state,"tcp-keepalive",server.tcpkeepalive,CONFIG_DEFAULT_TCP_KEEPALIVE);
    rewriteConfigNumericalOption(state,"replica-announce-port",server.slave_announce_port,CONFIG_DEFAULT_SLAVE_ANNOUNCE_PORT);
    rewriteConfigEnumOption(state,"loglevel",server.verbosity,loglevel_enum,CONFIG_DEFAULT_VERBOSITY);
    rewriteConfigStringOption(state,"logfile",server.logfile,CONFIG_DEFAULT_LOGFILE);
    rewriteConfigStringOption(state,"aclfile",server.acl_filename,CONFIG_DEFAULT_ACL_FILENAME);
    rewriteConfigYesNoOption(state,"syslog-enabled",server.syslog_enabled,CONFIG_DEFAULT_SYSLOG_ENABLED);
    rewriteConfigStringOption(state,"syslog-ident",server.syslog_ident,CONFIG_DEFAULT_SYSLOG_IDENT);
    rewriteConfigSyslogfacilityOption(state);
    rewriteConfigSaveOption(state);
    rewriteConfigUserOption(state);
    rewriteConfigNumericalOption(state,"databases",server.dbnum,CONFIG_DEFAULT_DBNUM);
    rewriteConfigYesNoOption(state,"stop-writes-on-bgsave-error",server.stop_writes_on_bgsave_err,CONFIG_DEFAULT_STOP_WRITES_ON_BGSAVE_ERROR);
    rewriteConfigYesNoOption(state,"rdbcompression",server.rdb_compression,CONFIG_DEFAULT_RDB_COMPRESSION);
    rewriteConfigYesNoOption(state,"rdbchecksum",server.rdb_checksum,CONFIG_DEFAULT_RDB_CHECKSUM);
    rewriteConfigStringOption(state,"dbfilename",server.rdb_filename,CONFIG_DEFAULT_RDB_FILENAME);
    rewriteConfigDirOption(state);
    rewriteConfigSlaveofOption(state,"replicaof");
    rewriteConfigStringOption(state,"replica-announce-ip",server.slave_announce_ip,CONFIG_DEFAULT_SLAVE_ANNOUNCE_IP);
    rewriteConfigStringOption(state,"masteruser",server.masteruser,NULL);
    rewriteConfigStringOption(state,"masterauth",server.masterauth,NULL);
    rewriteConfigStringOption(state,"cluster-announce-ip",server.cluster_announce_ip,NULL);
    rewriteConfigYesNoOption(state,"replica-serve-stale-data",server.repl_serve_stale_data,CONFIG_DEFAULT_SLAVE_SERVE_STALE_DATA);
    rewriteConfigYesNoOption(state,"replica-read-only",server.repl_slave_ro,CONFIG_DEFAULT_SLAVE_READ_ONLY);
    rewriteConfigYesNoOption(state,"replica-ignore-maxmemory",server.repl_slave_ignore_maxmemory,CONFIG_DEFAULT_SLAVE_IGNORE_MAXMEMORY);
    rewriteConfigNumericalOption(state,"repl-ping-replica-period",server.repl_ping_slave_period,CONFIG_DEFAULT_REPL_PING_SLAVE_PERIOD);
    rewriteConfigNumericalOption(state,"repl-timeout",server.repl_timeout,CONFIG_DEFAULT_REPL_TIMEOUT);
    rewriteConfigBytesOption(state,"repl-backlog-size",server.repl_backlog_size,CONFIG_DEFAULT_REPL_BACKLOG_SIZE);
    rewriteConfigBytesOption(state,"repl-backlog-ttl",server.repl_backlog_time_limit,CONFIG_DEFAULT_REPL_BACKLOG_TIME_LIMIT);
    rewriteConfigYesNoOption(state,"repl-disable-tcp-nodelay",server.repl_disable_tcp_nodelay,CONFIG_DEFAULT_REPL_DISABLE_TCP_NODELAY);
    rewriteConfigYesNoOption(state,"repl-diskless-sync",server.repl_diskless_sync,CONFIG_DEFAULT_REPL_DISKLESS_SYNC);
    rewriteConfigNumericalOption(state,"repl-diskless-sync-delay",server.repl_diskless_sync_delay,CONFIG_DEFAULT_REPL_DISKLESS_SYNC_DELAY);
    rewriteConfigNumericalOption(state,"replica-priority",server.slave_priority,CONFIG_DEFAULT_SLAVE_PRIORITY);
    rewriteConfigNumericalOption(state,"min-replicas-to-write",server.repl_min_slaves_to_write,CONFIG_DEFAULT_MIN_SLAVES_TO_WRITE);
    rewriteConfigNumericalOption(state,"min-replicas-max-lag",server.repl_min_slaves_max_lag,CONFIG_DEFAULT_MIN_SLAVES_MAX_LAG);
    rewriteConfigRequirepassOption(state,"requirepass");
    rewriteConfigNumericalOption(state,"maxclients",server.maxclients,CONFIG_DEFAULT_MAX_CLIENTS);
    rewriteConfigBytesOption(state,"maxmemory",server.maxmemory,CONFIG_DEFAULT_MAXMEMORY);
    rewriteConfigBytesOption(state,"proto-max-bulk-len",server.proto_max_bulk_len,CONFIG_DEFAULT_PROTO_MAX_BULK_LEN);
    rewriteConfigBytesOption(state,"client-query-buffer-limit",server.client_max_querybuf_len,PROTO_MAX_QUERYBUF_LEN);
    rewriteConfigEnumOption(state,"maxmemory-policy",server.maxmemory_policy,maxmemory_policy_enum,CONFIG_DEFAULT_MAXMEMORY_POLICY);
    rewriteConfigNumericalOption(state,"maxmemory-samples",server.maxmemory_samples,CONFIG_DEFAULT_MAXMEMORY_SAMPLES);
    rewriteConfigNumericalOption(state,"lfu-log-factor",server.lfu_log_factor,CONFIG_DEFAULT_LFU_LOG_FACTOR);
    rewriteConfigNumericalOption(state,"lfu-decay-time",server.lfu_decay_time,CONFIG_DEFAULT_LFU_DECAY_TIME);
    rewriteConfigNumericalOption(state,"active-defrag-threshold-lower",server.active_defrag_threshold_lower,CONFIG_DEFAULT_DEFRAG_THRESHOLD_LOWER);
    rewriteConfigNumericalOption(state,"active-defrag-threshold-upper",server.active_defrag_threshold_upper,CONFIG_DEFAULT_DEFRAG_THRESHOLD_UPPER);
    rewriteConfigBytesOption(state,"active-defrag-ignore-bytes",server.active_defrag_ignore_bytes,CONFIG_DEFAULT_DEFRAG_IGNORE_BYTES);
    rewriteConfigNumericalOption(state,"active-defrag-cycle-min",server.active_defrag_cycle_min,CONFIG_DEFAULT_DEFRAG_CYCLE_MIN);
    rewriteConfigNumericalOption(state,"active-defrag-cycle-max",server.active_defrag_cycle_max,CONFIG_DEFAULT_DEFRAG_CYCLE_MAX);
    rewriteConfigNumericalOption(state,"active-defrag-max-scan-fields",server.active_defrag_max_scan_fields,CONFIG_DEFAULT_DEFRAG_MAX_SCAN_FIELDS);
    rewriteConfigYesNoOption(state,"appendonly",server.aof_state != AOF_OFF,0);
    rewriteConfigStringOption(state,"appendfilename",server.aof_filename,CONFIG_DEFAULT_AOF_FILENAME);
    rewriteConfigEnumOption(state,"appendfsync",server.aof_fsync,aof_fsync_enum,CONFIG_DEFAULT_AOF_FSYNC);
    rewriteConfigYesNoOption(state,"no-appendfsync-on-rewrite",server.aof_no_fsync_on_rewrite,CONFIG_DEFAULT_AOF_NO_FSYNC_ON_REWRITE);
    rewriteConfigNumericalOption(state,"auto-aof-rewrite-percentage",server.aof_rewrite_perc,AOF_REWRITE_PERC);
    rewriteConfigBytesOption(state,"auto-aof-rewrite-min-size",server.aof_rewrite_min_size,AOF_REWRITE_MIN_SIZE);
    rewriteConfigNumericalOption(state,"lua-time-limit",server.lua_time_limit,LUA_SCRIPT_TIME_LIMIT);
    rewriteConfigYesNoOption(state,"cluster-enabled",server.cluster_enabled,0);
    rewriteConfigStringOption(state,"cluster-config-file",server.cluster_configfile,CONFIG_DEFAULT_CLUSTER_CONFIG_FILE);
    rewriteConfigYesNoOption(state,"cluster-require-full-coverage",server.cluster_require_full_coverage,CLUSTER_DEFAULT_REQUIRE_FULL_COVERAGE);
    rewriteConfigYesNoOption(state,"cluster-replica-no-failover",server.cluster_slave_no_failover,CLUSTER_DEFAULT_SLAVE_NO_FAILOVER);
    rewriteConfigNumericalOption(state,"cluster-node-timeout",server.cluster_node_timeout,CLUSTER_DEFAULT_NODE_TIMEOUT);
    rewriteConfigNumericalOption(state,"cluster-migration-barrier",server.cluster_migration_barrier,CLUSTER_DEFAULT_MIGRATION_BARRIER);
    rewriteConfigNumericalOption(state,"cluster-replica-validity-factor",server.cluster_slave_validity_factor,CLUSTER_DEFAULT_SLAVE_VALIDITY);
    rewriteConfigNumericalOption(state,"slowlog-log-slower-than",server.slowlog_log_slower_than,CONFIG_DEFAULT_SLOWLOG_LOG_SLOWER_THAN);
    rewriteConfigNumericalOption(state,"latency-monitor-threshold",server.latency_monitor_threshold,CONFIG_DEFAULT_LATENCY_MONITOR_THRESHOLD);
    rewriteConfigNumericalOption(state,"slowlog-max-len",server.slowlog_max_len,CONFIG_DEFAULT_SLOWLOG_MAX_LEN);
    rewriteConfigNotifykeyspaceeventsOption(state);
    rewriteConfigNumericalOption(state,"hash-max-ziplist-entries",server.hash_max_ziplist_entries,OBJ_HASH_MAX_ZIPLIST_ENTRIES);
    rewriteConfigNumericalOption(state,"hash-max-ziplist-value",server.hash_max_ziplist_value,OBJ_HASH_MAX_ZIPLIST_VALUE);
    rewriteConfigNumericalOption(state,"stream-node-max-bytes",server.stream_node_max_bytes,OBJ_STREAM_NODE_MAX_BYTES);
    rewriteConfigNumericalOption(state,"stream-node-max-entries",server.stream_node_max_entries,OBJ_STREAM_NODE_MAX_ENTRIES);
    rewriteConfigNumericalOption(state,"list-max-ziplist-size",server.list_max_ziplist_size,OBJ_LIST_MAX_ZIPLIST_SIZE);
    rewriteConfigNumericalOption(state,"list-compress-depth",server.list_compress_depth,OBJ_LIST_COMPRESS_DEPTH);
    rewriteConfigNumericalOption(state,"set-max-intset-entries",server.set_max_intset_entries,OBJ_SET_MAX_INTSET_ENTRIES);
    rewriteConfigNumericalOption(state,"zset-max-ziplist-entries",server.zset_max_ziplist_entries,OBJ_ZSET_MAX_ZIPLIST_ENTRIES);
    rewriteConfigNumericalOption(state,"zset-max-ziplist-value",server.zset_max_ziplist_value,OBJ_ZSET_MAX_ZIPLIST_VALUE);
    rewriteConfigNumericalOption(state,"hll-sparse-max-bytes",server.hll_sparse_max_bytes,CONFIG_DEFAULT_HLL_SPARSE_MAX_BYTES);
    rewriteConfigYesNoOption(state,"activerehashing",server.activerehashing,CONFIG_DEFAULT_ACTIVE_REHASHING);
    rewriteConfigYesNoOption(state,"activedefrag",server.active_defrag_enabled,CONFIG_DEFAULT_ACTIVE_DEFRAG);
    rewriteConfigYesNoOption(state,"protected-mode",server.protected_mode,CONFIG_DEFAULT_PROTECTED_MODE);
    rewriteConfigYesNoOption(state,"gopher-enabled",server.gopher_enabled,CONFIG_DEFAULT_GOPHER_ENABLED);
    rewriteConfigClientoutputbufferlimitOption(state);
    rewriteConfigNumericalOption(state,"hz",server.config_hz,CONFIG_DEFAULT_HZ);
    rewriteConfigYesNoOption(state,"aof-rewrite-incremental-fsync",server.aof_rewrite_incremental_fsync,CONFIG_DEFAULT_AOF_REWRITE_INCREMENTAL_FSYNC);
    rewriteConfigYesNoOption(state,"rdb-save-incremental-fsync",server.rdb_save_incremental_fsync,CONFIG_DEFAULT_RDB_SAVE_INCREMENTAL_FSYNC);
    rewriteConfigYesNoOption(state,"aof-load-truncated",server.aof_load_truncated,CONFIG_DEFAULT_AOF_LOAD_TRUNCATED);
    rewriteConfigYesNoOption(state,"aof-use-rdb-preamble",server.aof_use_rdb_preamble,CONFIG_DEFAULT_AOF_USE_RDB_PREAMBLE);
    rewriteConfigEnumOption(state,"supervised",server.supervised_mode,supervised_mode_enum,SUPERVISED_NONE);
    rewriteConfigYesNoOption(state,"lazyfree-lazy-eviction",server.lazyfree_lazy_eviction,CONFIG_DEFAULT_LAZYFREE_LAZY_EVICTION);
    rewriteConfigYesNoOption(state,"lazyfree-lazy-expire",server.lazyfree_lazy_expire,CONFIG_DEFAULT_LAZYFREE_LAZY_EXPIRE);
    rewriteConfigYesNoOption(state,"lazyfree-lazy-server-del",server.lazyfree_lazy_server_del,CONFIG_DEFAULT_LAZYFREE_LAZY_SERVER_DEL);
    rewriteConfigYesNoOption(state,"replica-lazy-flush",server.repl_slave_lazy_flush,CONFIG_DEFAULT_SLAVE_LAZY_FLUSH);
    rewriteConfigYesNoOption(state,"dynamic-hz",server.dynamic_hz,CONFIG_DEFAULT_DYNAMIC_HZ);

    /* Rewrite Sentinel config if in Sentinel mode. */
    if (server.sentinel_mode) rewriteConfigSentinelOption(state);

    /* Step 3: remove all the orphaned lines in the old file, that is, lines
     * that were used by a config option and are no longer used, like in case
     * of multiple "save" options or duplicated options. */
    rewriteConfigRemoveOrphaned(state);

    /* Step 4: generate a new configuration file from the modified state
     * and write it into the original file. */
    newcontent = rewriteConfigGetContentFromState(state);
    retval = rewriteConfigOverwriteFile(server.configfile,newcontent);

    sdsfree(newcontent);
    rewriteConfigReleaseState(state);
    return retval;
}