#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  clusterManagerCommandProc ;
struct TYPE_4__ {int /*<<< orphan*/ * backup_dir; int /*<<< orphan*/  threshold; int /*<<< orphan*/  pipeline; int /*<<< orphan*/  timeout; scalar_t__ slots; scalar_t__ weight_argc; int /*<<< orphan*/ * weight; int /*<<< orphan*/ * to; int /*<<< orphan*/ * from; scalar_t__ replicas; scalar_t__ flags; int /*<<< orphan*/ * argv; scalar_t__ argc; int /*<<< orphan*/ * name; } ;
struct TYPE_6__ {int hostport; int repeat; int interval; int last_cmd_type; int /*<<< orphan*/ * eval; scalar_t__ intrinsic_latency_mode; scalar_t__ lru_test_mode; scalar_t__ scan_mode; scalar_t__ stat_mode; scalar_t__ hotkeys; int /*<<< orphan*/  memkeys_samples; scalar_t__ memkeys; scalar_t__ bigkeys; scalar_t__ pipe_mode; scalar_t__ getrdb_mode; scalar_t__ slave_mode; scalar_t__ latency_dist_mode; scalar_t__ latency_mode; void* mb_delim; void* hostip; int /*<<< orphan*/  output; TYPE_1__ cluster_manager_command; scalar_t__ no_auth_warning; scalar_t__ verbose; scalar_t__ enable_ldb_on_eval; scalar_t__ eval_ldb_sync; scalar_t__ eval_ldb_end; scalar_t__ eval_ldb; int /*<<< orphan*/ * user; int /*<<< orphan*/ * auth; scalar_t__ stdinarg; int /*<<< orphan*/  pipe_timeout; int /*<<< orphan*/ * rdb_filename; int /*<<< orphan*/ * pattern; scalar_t__ cluster_mode; scalar_t__ lru_test_sample_size; scalar_t__ latency_history; scalar_t__ pubsub_mode; scalar_t__ monitor_mode; scalar_t__ shutdown; scalar_t__ interactive; scalar_t__ dbnum; int /*<<< orphan*/ * hostsocket; } ;
struct TYPE_5__ {int hints; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTER_MANAGER_MIGRATE_PIPELINE ; 
 int /*<<< orphan*/  CLUSTER_MANAGER_MIGRATE_TIMEOUT ; 
 scalar_t__ CLUSTER_MANAGER_MODE () ; 
 int /*<<< orphan*/  CLUSTER_MANAGER_REBALANCE_THRESHOLD ; 
 int /*<<< orphan*/  LRUTestMode () ; 
 int /*<<< orphan*/  OUTPUT_RAW ; 
 int /*<<< orphan*/  OUTPUT_STANDARD ; 
 int /*<<< orphan*/  REDIS_CLI_DEFAULT_PIPE_TIMEOUT ; 
 scalar_t__ REDIS_ERR ; 
 scalar_t__ REDIS_OK ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 scalar_t__ cliConnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterManagerMode (int /*<<< orphan*/ *) ; 
 TYPE_3__ config ; 
 int /*<<< orphan*/  convertToSds (int,char**) ; 
 int evalMode (int,char**) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  findBigKeys (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  findHotKeys () ; 
 int /*<<< orphan*/  getRDB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 int /*<<< orphan*/  intrinsicLatencyMode () ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  latencyDistMode () ; 
 int /*<<< orphan*/  latencyMode () ; 
 int noninteractive (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parseEnv () ; 
 int parseOptions (int,char**) ; 
 int /*<<< orphan*/  pipeMode () ; 
 TYPE_2__ pref ; 
 int /*<<< orphan*/  repl () ; 
 int /*<<< orphan*/  scanMode () ; 
 int /*<<< orphan*/  sdsfree (void*) ; 
 void* sdsnew (char*) ; 
 int /*<<< orphan*/  sendCapa () ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slaveMode () ; 
 int /*<<< orphan*/  spectrum_palette ; 
 int /*<<< orphan*/  spectrum_palette_color ; 
 int /*<<< orphan*/  spectrum_palette_color_size ; 
 int /*<<< orphan*/  spectrum_palette_size ; 
 int /*<<< orphan*/  statMode () ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/ * validateClusterManagerCommand () ; 

int main(int argc, char **argv) {
    int firstarg;

    config.hostip = sdsnew("127.0.0.1");
    config.hostport = 6379;
    config.hostsocket = NULL;
    config.repeat = 1;
    config.interval = 0;
    config.dbnum = 0;
    config.interactive = 0;
    config.shutdown = 0;
    config.monitor_mode = 0;
    config.pubsub_mode = 0;
    config.latency_mode = 0;
    config.latency_dist_mode = 0;
    config.latency_history = 0;
    config.lru_test_mode = 0;
    config.lru_test_sample_size = 0;
    config.cluster_mode = 0;
    config.slave_mode = 0;
    config.getrdb_mode = 0;
    config.stat_mode = 0;
    config.scan_mode = 0;
    config.intrinsic_latency_mode = 0;
    config.pattern = NULL;
    config.rdb_filename = NULL;
    config.pipe_mode = 0;
    config.pipe_timeout = REDIS_CLI_DEFAULT_PIPE_TIMEOUT;
    config.bigkeys = 0;
    config.hotkeys = 0;
    config.stdinarg = 0;
    config.auth = NULL;
    config.user = NULL;
    config.eval = NULL;
    config.eval_ldb = 0;
    config.eval_ldb_end = 0;
    config.eval_ldb_sync = 0;
    config.enable_ldb_on_eval = 0;
    config.last_cmd_type = -1;
    config.verbose = 0;
    config.no_auth_warning = 0;
    config.cluster_manager_command.name = NULL;
    config.cluster_manager_command.argc = 0;
    config.cluster_manager_command.argv = NULL;
    config.cluster_manager_command.flags = 0;
    config.cluster_manager_command.replicas = 0;
    config.cluster_manager_command.from = NULL;
    config.cluster_manager_command.to = NULL;
    config.cluster_manager_command.weight = NULL;
    config.cluster_manager_command.weight_argc = 0;
    config.cluster_manager_command.slots = 0;
    config.cluster_manager_command.timeout = CLUSTER_MANAGER_MIGRATE_TIMEOUT;
    config.cluster_manager_command.pipeline = CLUSTER_MANAGER_MIGRATE_PIPELINE;
    config.cluster_manager_command.threshold =
        CLUSTER_MANAGER_REBALANCE_THRESHOLD;
    config.cluster_manager_command.backup_dir = NULL;
    pref.hints = 1;

    spectrum_palette = spectrum_palette_color;
    spectrum_palette_size = spectrum_palette_color_size;

    if (!isatty(fileno(stdout)) && (getenv("FAKETTY") == NULL))
        config.output = OUTPUT_RAW;
    else
        config.output = OUTPUT_STANDARD;
    config.mb_delim = sdsnew("\n");

    firstarg = parseOptions(argc,argv);
    argc -= firstarg;
    argv += firstarg;

    parseEnv();

    /* Cluster Manager mode */
    if (CLUSTER_MANAGER_MODE()) {
        clusterManagerCommandProc *proc = validateClusterManagerCommand();
        if (!proc) {
            sdsfree(config.hostip);
            sdsfree(config.mb_delim);
            exit(1);
        }
        clusterManagerMode(proc);
    }

    /* Latency mode */
    if (config.latency_mode) {
        if (cliConnect(0) == REDIS_ERR) exit(1);
        latencyMode();
    }

    /* Latency distribution mode */
    if (config.latency_dist_mode) {
        if (cliConnect(0) == REDIS_ERR) exit(1);
        latencyDistMode();
    }

    /* Slave mode */
    if (config.slave_mode) {
        if (cliConnect(0) == REDIS_ERR) exit(1);
        sendCapa();
        slaveMode();
    }

    /* Get RDB mode. */
    if (config.getrdb_mode) {
        if (cliConnect(0) == REDIS_ERR) exit(1);
        sendCapa();
        getRDB(NULL);
    }

    /* Pipe mode */
    if (config.pipe_mode) {
        if (cliConnect(0) == REDIS_ERR) exit(1);
        pipeMode();
    }

    /* Find big keys */
    if (config.bigkeys) {
        if (cliConnect(0) == REDIS_ERR) exit(1);
        findBigKeys(0, 0);
    }

    /* Find large keys */
    if (config.memkeys) {
        if (cliConnect(0) == REDIS_ERR) exit(1);
        findBigKeys(1, config.memkeys_samples);
    }

    /* Find hot keys */
    if (config.hotkeys) {
        if (cliConnect(0) == REDIS_ERR) exit(1);
        findHotKeys();
    }

    /* Stat mode */
    if (config.stat_mode) {
        if (cliConnect(0) == REDIS_ERR) exit(1);
        if (config.interval == 0) config.interval = 1000000;
        statMode();
    }

    /* Scan mode */
    if (config.scan_mode) {
        if (cliConnect(0) == REDIS_ERR) exit(1);
        scanMode();
    }

    /* LRU test mode */
    if (config.lru_test_mode) {
        if (cliConnect(0) == REDIS_ERR) exit(1);
        LRUTestMode();
    }

    /* Intrinsic latency mode */
    if (config.intrinsic_latency_mode) intrinsicLatencyMode();

    /* Start interactive mode when no command is provided */
    if (argc == 0 && !config.eval) {
        /* Ignore SIGPIPE in interactive mode to force a reconnect */
        signal(SIGPIPE, SIG_IGN);

        /* Note that in repl mode we don't abort on connection error.
         * A new attempt will be performed for every command send. */
        cliConnect(0);
        repl();
    }

    /* Otherwise, we have some arguments to execute */
    if (cliConnect(0) != REDIS_OK) exit(1);
    if (config.eval) {
        return evalMode(argc,argv);
    } else {
        return noninteractive(argc,convertToSds(argc,argv));
    }
}