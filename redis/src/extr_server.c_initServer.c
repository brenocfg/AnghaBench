#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  redisDb ;
struct TYPE_6__ {scalar_t__ allocator_resident; scalar_t__ allocator_active; scalar_t__ allocator_allocated; scalar_t__ process_rss; scalar_t__ zmalloc_used; } ;
struct TYPE_5__ {scalar_t__ magic; } ;
struct TYPE_8__ {int slaveseldb; scalar_t__ tls_port; int dbnum; scalar_t__ port; scalar_t__* ipfd; int ipfd_count; scalar_t__* tlsfd; int tlsfd_count; scalar_t__ sofd; int rdb_child_pid; int aof_child_pid; int module_child_pid; int* child_info_pipe; int rdb_save_time_last; int rdb_save_time_start; scalar_t__* module_blocked_pipe; scalar_t__ aof_state; int aof_fd; int arch_bits; long long maxmemory; scalar_t__ cluster_enabled; int /*<<< orphan*/  maxmemory_policy; int /*<<< orphan*/  aof_filename; int /*<<< orphan*/ * el; scalar_t__ repl_good_slaves_count; scalar_t__ aof_last_write_errno; void* aof_last_write_status; void* lastbgsave_status; TYPE_2__ cron_malloc_stats; scalar_t__ stat_module_cow_bytes; scalar_t__ stat_aof_cow_bytes; scalar_t__ stat_rdb_cow_bytes; scalar_t__ stat_peak_memory; void* stat_starttime; scalar_t__ dirty; scalar_t__ lastbgsave_try; void* lastsave; int /*<<< orphan*/  aof_buf; TYPE_1__ child_info_data; scalar_t__ rdb_bgsave_scheduled; scalar_t__ rdb_pipe_bufflen; int /*<<< orphan*/ * rdb_pipe_buff; scalar_t__ rdb_pipe_numconns_writing; scalar_t__ rdb_pipe_numconns; int /*<<< orphan*/ * rdb_pipe_conns; int /*<<< orphan*/  rdb_child_type; scalar_t__ cronloops; void* pubsub_patterns; void* pubsub_channels; TYPE_3__* db; int /*<<< orphan*/  neterr; int /*<<< orphan*/  tcp_backlog; int /*<<< orphan*/  unixsocketperm; int /*<<< orphan*/ * unixsocket; scalar_t__ maxclients; int /*<<< orphan*/  tls_ctx_config; int /*<<< orphan*/  system_memory_size; scalar_t__ clients_paused; scalar_t__ get_ack_from_slaves; void* clients_waiting_acks; void* ready_keys; void* unblocked_clients; void* clients_pending_read; void* clients_pending_write; void* monitors; void* slaves; void* clients_to_close; int /*<<< orphan*/  clients_index; void* clients; scalar_t__ call_depth; int /*<<< orphan*/ * current_client; int /*<<< orphan*/  pid; int /*<<< orphan*/  config_hz; int /*<<< orphan*/  hz; int /*<<< orphan*/  syslog_facility; int /*<<< orphan*/  syslog_ident; scalar_t__ syslog_enabled; } ;
struct TYPE_7__ {int id; void* defrag_later; scalar_t__ avg_ttl; void* watched_keys; void* ready_keys; void* blocking_keys; void* expires; void* dict; } ;

/* Variables and functions */
 scalar_t__ AE_ERR ; 
 int /*<<< orphan*/  AE_READABLE ; 
 scalar_t__ ANET_ERR ; 
 scalar_t__ AOF_ON ; 
 scalar_t__ CONFIG_FDSET_INCR ; 
 scalar_t__ C_ERR ; 
 void* C_OK ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int LOG_NDELAY ; 
 int LOG_NOWAIT ; 
 int LOG_PID ; 
 int /*<<< orphan*/  MAXMEMORY_NO_EVICTION ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  RDB_CHILD_TYPE_NONE ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  acceptTLSHandler ; 
 int /*<<< orphan*/  acceptTcpHandler ; 
 int /*<<< orphan*/  acceptUnixHandler ; 
 int /*<<< orphan*/  adjustOpenFilesLimit () ; 
 int /*<<< orphan*/ * aeCreateEventLoop (scalar_t__) ; 
 scalar_t__ aeCreateFileEvent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ aeCreateTimeEvent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  anetNonBlock (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ anetUnixServer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aofRewriteBufferReset () ; 
 int /*<<< orphan*/  clusterInit () ; 
 int /*<<< orphan*/  createSharedObjects () ; 
 int /*<<< orphan*/  dbDictType ; 
 void* dictCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  evictionPoolAlloc () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  freePubsubPattern ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  keylistDictType ; 
 int /*<<< orphan*/  keyptrDictType ; 
 int /*<<< orphan*/  latencyMonitorInit () ; 
 void* listCreate () ; 
 int /*<<< orphan*/  listMatchPubsubPattern ; 
 int /*<<< orphan*/  listSetFreeMethod (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listSetMatchMethod (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ listenToPort (scalar_t__,scalar_t__*,int*) ; 
 int /*<<< orphan*/  moduleBlockedClientPipeReadable ; 
 int /*<<< orphan*/  objectKeyPointerValueDictType ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  openlog (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raxNew () ; 
 int /*<<< orphan*/  replicationScriptCacheInit () ; 
 int /*<<< orphan*/  resetServerStats () ; 
 int /*<<< orphan*/  scriptingInit (int) ; 
 int /*<<< orphan*/  sdsempty () ; 
 TYPE_4__ server ; 
 int /*<<< orphan*/  serverCron ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 
 int /*<<< orphan*/  setupSignalHandlers () ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slowlogInit () ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 void* time (int /*<<< orphan*/ *) ; 
 scalar_t__ tlsConfigure (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ *) ; 
 TYPE_3__* zmalloc (int) ; 
 int /*<<< orphan*/  zmalloc_get_memory_size () ; 

void initServer(void) {
    int j;

    signal(SIGHUP, SIG_IGN);
    signal(SIGPIPE, SIG_IGN);
    setupSignalHandlers();

    if (server.syslog_enabled) {
        openlog(server.syslog_ident, LOG_PID | LOG_NDELAY | LOG_NOWAIT,
            server.syslog_facility);
    }

    server.hz = server.config_hz;
    server.pid = getpid();
    server.current_client = NULL;
    server.call_depth = 0;
    server.clients = listCreate();
    server.clients_index = raxNew();
    server.clients_to_close = listCreate();
    server.slaves = listCreate();
    server.monitors = listCreate();
    server.clients_pending_write = listCreate();
    server.clients_pending_read = listCreate();
    server.slaveseldb = -1; /* Force to emit the first SELECT command. */
    server.unblocked_clients = listCreate();
    server.ready_keys = listCreate();
    server.clients_waiting_acks = listCreate();
    server.get_ack_from_slaves = 0;
    server.clients_paused = 0;
    server.system_memory_size = zmalloc_get_memory_size();

    if (server.tls_port && tlsConfigure(&server.tls_ctx_config) == C_ERR) {
        serverLog(LL_WARNING, "Failed to configure TLS. Check logs for more info.");
        exit(1);
    }

    createSharedObjects();
    adjustOpenFilesLimit();
    server.el = aeCreateEventLoop(server.maxclients+CONFIG_FDSET_INCR);
    if (server.el == NULL) {
        serverLog(LL_WARNING,
            "Failed creating the event loop. Error message: '%s'",
            strerror(errno));
        exit(1);
    }
    server.db = zmalloc(sizeof(redisDb)*server.dbnum);

    /* Open the TCP listening socket for the user commands. */
    if (server.port != 0 &&
        listenToPort(server.port,server.ipfd,&server.ipfd_count) == C_ERR)
        exit(1);
    if (server.tls_port != 0 &&
        listenToPort(server.tls_port,server.tlsfd,&server.tlsfd_count) == C_ERR)
        exit(1);

    /* Open the listening Unix domain socket. */
    if (server.unixsocket != NULL) {
        unlink(server.unixsocket); /* don't care if this fails */
        server.sofd = anetUnixServer(server.neterr,server.unixsocket,
            server.unixsocketperm, server.tcp_backlog);
        if (server.sofd == ANET_ERR) {
            serverLog(LL_WARNING, "Opening Unix socket: %s", server.neterr);
            exit(1);
        }
        anetNonBlock(NULL,server.sofd);
    }

    /* Abort if there are no listening sockets at all. */
    if (server.ipfd_count == 0 && server.tlsfd_count == 0 && server.sofd < 0) {
        serverLog(LL_WARNING, "Configured to not listen anywhere, exiting.");
        exit(1);
    }

    /* Create the Redis databases, and initialize other internal state. */
    for (j = 0; j < server.dbnum; j++) {
        server.db[j].dict = dictCreate(&dbDictType,NULL);
        server.db[j].expires = dictCreate(&keyptrDictType,NULL);
        server.db[j].blocking_keys = dictCreate(&keylistDictType,NULL);
        server.db[j].ready_keys = dictCreate(&objectKeyPointerValueDictType,NULL);
        server.db[j].watched_keys = dictCreate(&keylistDictType,NULL);
        server.db[j].id = j;
        server.db[j].avg_ttl = 0;
        server.db[j].defrag_later = listCreate();
    }
    evictionPoolAlloc(); /* Initialize the LRU keys pool. */
    server.pubsub_channels = dictCreate(&keylistDictType,NULL);
    server.pubsub_patterns = listCreate();
    listSetFreeMethod(server.pubsub_patterns,freePubsubPattern);
    listSetMatchMethod(server.pubsub_patterns,listMatchPubsubPattern);
    server.cronloops = 0;
    server.rdb_child_pid = -1;
    server.aof_child_pid = -1;
    server.module_child_pid = -1;
    server.rdb_child_type = RDB_CHILD_TYPE_NONE;
    server.rdb_pipe_conns = NULL;
    server.rdb_pipe_numconns = 0;
    server.rdb_pipe_numconns_writing = 0;
    server.rdb_pipe_buff = NULL;
    server.rdb_pipe_bufflen = 0;
    server.rdb_bgsave_scheduled = 0;
    server.child_info_pipe[0] = -1;
    server.child_info_pipe[1] = -1;
    server.child_info_data.magic = 0;
    aofRewriteBufferReset();
    server.aof_buf = sdsempty();
    server.lastsave = time(NULL); /* At startup we consider the DB saved. */
    server.lastbgsave_try = 0;    /* At startup we never tried to BGSAVE. */
    server.rdb_save_time_last = -1;
    server.rdb_save_time_start = -1;
    server.dirty = 0;
    resetServerStats();
    /* A few stats we don't want to reset: server startup time, and peak mem. */
    server.stat_starttime = time(NULL);
    server.stat_peak_memory = 0;
    server.stat_rdb_cow_bytes = 0;
    server.stat_aof_cow_bytes = 0;
    server.stat_module_cow_bytes = 0;
    server.cron_malloc_stats.zmalloc_used = 0;
    server.cron_malloc_stats.process_rss = 0;
    server.cron_malloc_stats.allocator_allocated = 0;
    server.cron_malloc_stats.allocator_active = 0;
    server.cron_malloc_stats.allocator_resident = 0;
    server.lastbgsave_status = C_OK;
    server.aof_last_write_status = C_OK;
    server.aof_last_write_errno = 0;
    server.repl_good_slaves_count = 0;

    /* Create the timer callback, this is our way to process many background
     * operations incrementally, like clients timeout, eviction of unaccessed
     * expired keys and so forth. */
    if (aeCreateTimeEvent(server.el, 1, serverCron, NULL, NULL) == AE_ERR) {
        serverPanic("Can't create event loop timers.");
        exit(1);
    }

    /* Create an event handler for accepting new connections in TCP and Unix
     * domain sockets. */
    for (j = 0; j < server.ipfd_count; j++) {
        if (aeCreateFileEvent(server.el, server.ipfd[j], AE_READABLE,
            acceptTcpHandler,NULL) == AE_ERR)
            {
                serverPanic(
                    "Unrecoverable error creating server.ipfd file event.");
            }
    }
    for (j = 0; j < server.tlsfd_count; j++) {
        if (aeCreateFileEvent(server.el, server.tlsfd[j], AE_READABLE,
            acceptTLSHandler,NULL) == AE_ERR)
            {
                serverPanic(
                    "Unrecoverable error creating server.tlsfd file event.");
            }
    }
    if (server.sofd > 0 && aeCreateFileEvent(server.el,server.sofd,AE_READABLE,
        acceptUnixHandler,NULL) == AE_ERR) serverPanic("Unrecoverable error creating server.sofd file event.");


    /* Register a readable event for the pipe used to awake the event loop
     * when a blocked client in a module needs attention. */
    if (aeCreateFileEvent(server.el, server.module_blocked_pipe[0], AE_READABLE,
        moduleBlockedClientPipeReadable,NULL) == AE_ERR) {
            serverPanic(
                "Error registering the readable event for the module "
                "blocked clients subsystem.");
    }

    /* Open the AOF file if needed. */
    if (server.aof_state == AOF_ON) {
        server.aof_fd = open(server.aof_filename,
                               O_WRONLY|O_APPEND|O_CREAT,0644);
        if (server.aof_fd == -1) {
            serverLog(LL_WARNING, "Can't open the append-only file: %s",
                strerror(errno));
            exit(1);
        }
    }

    /* 32 bit instances are limited to 4GB of address space, so if there is
     * no explicit limit in the user provided configuration we set a limit
     * at 3 GB using maxmemory with 'noeviction' policy'. This avoids
     * useless crashes of the Redis instance for out of memory. */
    if (server.arch_bits == 32 && server.maxmemory == 0) {
        serverLog(LL_WARNING,"Warning: 32 bit instance detected but no memory limit set. Setting 3 GB maxmemory limit with 'noeviction' policy now.");
        server.maxmemory = 3072LL*(1024*1024); /* 3 GB */
        server.maxmemory_policy = MAXMEMORY_NO_EVICTION;
    }

    if (server.cluster_enabled) clusterInit();
    replicationScriptCacheInit();
    scriptingInit(1);
    slowlogInit();
    latencyMonitorInit();
}