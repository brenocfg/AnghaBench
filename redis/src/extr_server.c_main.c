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
typedef  int /*<<< orphan*/  uint8_t ;
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  hashseed ;
struct TYPE_2__ {char* configfile; scalar_t__ ipfd_count; scalar_t__ tlsfd_count; scalar_t__ sofd; int unixsocket; int maxmemory; int /*<<< orphan*/  el; scalar_t__ cluster_enabled; scalar_t__ sentinel_mode; scalar_t__ pidfile; int /*<<< orphan*/  supervised; scalar_t__ daemonize; int /*<<< orphan*/  supervised_mode; int /*<<< orphan*/ ** exec_argv; void* executable; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACLInit () ; 
 int /*<<< orphan*/  ACLLoadUsersAtStartup () ; 
 scalar_t__ C_ERR ; 
 int /*<<< orphan*/  InitServerLast () ; 
 int /*<<< orphan*/  LC_COLLATE ; 
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  REDIS_VERSION ; 
 int /*<<< orphan*/  aeDeleteEventLoop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aeMain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aeSetAfterSleepProc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aeSetBeforeSleepProc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afterSleep ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  beforeSleep ; 
 scalar_t__ checkForSentinelMode (int,char**) ; 
 int /*<<< orphan*/  checkTcpBacklogSettings () ; 
 int crc64Test (int,char**) ; 
 int /*<<< orphan*/  createPidFile () ; 
 int /*<<< orphan*/  daemonize () ; 
 int /*<<< orphan*/  dictSetHashFunctionSeed (int /*<<< orphan*/ *) ; 
 int endianconvTest (int,char**) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 void* getAbsolutePath (char*) ; 
 int /*<<< orphan*/  getRandomBytes (int /*<<< orphan*/ *,int) ; 
 int getpid () ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initSentinel () ; 
 int /*<<< orphan*/  initSentinelConfig () ; 
 int /*<<< orphan*/  initServer () ; 
 int /*<<< orphan*/  initServerConfig () ; 
 int intsetTest (int,char**) ; 
 int /*<<< orphan*/  linuxMemoryWarnings () ; 
 int /*<<< orphan*/  loadDataFromDisk () ; 
 int /*<<< orphan*/  loadServerConfig (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memtest (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  moduleInitModulesSystem () ; 
 int /*<<< orphan*/  moduleLoadFromQueue () ; 
 int /*<<< orphan*/  quicklistTest (int,char**) ; 
 int /*<<< orphan*/  redisAsciiArt () ; 
 int /*<<< orphan*/  redisGitDirty () ; 
 int /*<<< orphan*/  redisGitSHA1 () ; 
 int /*<<< orphan*/  redisIsSupervised (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redisOutOfMemoryHandler ; 
 int /*<<< orphan*/  redisSetProcTitle (char*) ; 
 int /*<<< orphan*/  redis_check_aof_main (int,char**) ; 
 int /*<<< orphan*/  redis_check_rdb_main (int,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resetServerSaveParams () ; 
 int /*<<< orphan*/  sdscat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sdscatrepr (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 scalar_t__ sdslen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sentinelIsRunning () ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int sha1Test (int,char**) ; 
 int /*<<< orphan*/  spt_init (int,char**) ; 
 int /*<<< orphan*/  srand (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 scalar_t__ strtol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tlsInit () ; 
 int /*<<< orphan*/  tzset () ; 
 int /*<<< orphan*/  usage () ; 
 int utilTest (int,char**) ; 
 scalar_t__ verifyClusterConfigWithData () ; 
 int /*<<< orphan*/  version () ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 
 int ziplistTest (int,char**) ; 
 int zipmapTest (int,char**) ; 
 int /*<<< orphan*/ ** zmalloc (int) ; 
 int /*<<< orphan*/  zmalloc_set_oom_handler (int /*<<< orphan*/ ) ; 
 int zmalloc_test (int,char**) ; 
 void* zstrdup (char*) ; 

int main(int argc, char **argv) {
    struct timeval tv;
    int j;

#ifdef REDIS_TEST
    if (argc == 3 && !strcasecmp(argv[1], "test")) {
        if (!strcasecmp(argv[2], "ziplist")) {
            return ziplistTest(argc, argv);
        } else if (!strcasecmp(argv[2], "quicklist")) {
            quicklistTest(argc, argv);
        } else if (!strcasecmp(argv[2], "intset")) {
            return intsetTest(argc, argv);
        } else if (!strcasecmp(argv[2], "zipmap")) {
            return zipmapTest(argc, argv);
        } else if (!strcasecmp(argv[2], "sha1test")) {
            return sha1Test(argc, argv);
        } else if (!strcasecmp(argv[2], "util")) {
            return utilTest(argc, argv);
        } else if (!strcasecmp(argv[2], "endianconv")) {
            return endianconvTest(argc, argv);
        } else if (!strcasecmp(argv[2], "crc64")) {
            return crc64Test(argc, argv);
        } else if (!strcasecmp(argv[2], "zmalloc")) {
            return zmalloc_test(argc, argv);
        }

        return -1; /* test not found */
    }
#endif

    /* We need to initialize our libraries, and the server configuration. */
#ifdef INIT_SETPROCTITLE_REPLACEMENT
    spt_init(argc, argv);
#endif
    setlocale(LC_COLLATE,"");
    tzset(); /* Populates 'timezone' global. */
    zmalloc_set_oom_handler(redisOutOfMemoryHandler);
    srand(time(NULL)^getpid());
    gettimeofday(&tv,NULL);

    uint8_t hashseed[16];
    getRandomBytes(hashseed,sizeof(hashseed));
    dictSetHashFunctionSeed(hashseed);
    server.sentinel_mode = checkForSentinelMode(argc,argv);
    initServerConfig();
    ACLInit(); /* The ACL subsystem must be initialized ASAP because the
                  basic networking code and client creation depends on it. */
    moduleInitModulesSystem();
    tlsInit();

    /* Store the executable path and arguments in a safe place in order
     * to be able to restart the server later. */
    server.executable = getAbsolutePath(argv[0]);
    server.exec_argv = zmalloc(sizeof(char*)*(argc+1));
    server.exec_argv[argc] = NULL;
    for (j = 0; j < argc; j++) server.exec_argv[j] = zstrdup(argv[j]);

    /* We need to init sentinel right now as parsing the configuration file
     * in sentinel mode will have the effect of populating the sentinel
     * data structures with master nodes to monitor. */
    if (server.sentinel_mode) {
        initSentinelConfig();
        initSentinel();
    }

    /* Check if we need to start in redis-check-rdb/aof mode. We just execute
     * the program main. However the program is part of the Redis executable
     * so that we can easily execute an RDB check on loading errors. */
    if (strstr(argv[0],"redis-check-rdb") != NULL)
        redis_check_rdb_main(argc,argv,NULL);
    else if (strstr(argv[0],"redis-check-aof") != NULL)
        redis_check_aof_main(argc,argv);

    if (argc >= 2) {
        j = 1; /* First option to parse in argv[] */
        sds options = sdsempty();
        char *configfile = NULL;

        /* Handle special options --help and --version */
        if (strcmp(argv[1], "-v") == 0 ||
            strcmp(argv[1], "--version") == 0) version();
        if (strcmp(argv[1], "--help") == 0 ||
            strcmp(argv[1], "-h") == 0) usage();
        if (strcmp(argv[1], "--test-memory") == 0) {
            if (argc == 3) {
                memtest(atoi(argv[2]),50);
                exit(0);
            } else {
                fprintf(stderr,"Please specify the amount of memory to test in megabytes.\n");
                fprintf(stderr,"Example: ./redis-server --test-memory 4096\n\n");
                exit(1);
            }
        }

        /* First argument is the config file name? */
        if (argv[j][0] != '-' || argv[j][1] != '-') {
            configfile = argv[j];
            server.configfile = getAbsolutePath(configfile);
            /* Replace the config file in server.exec_argv with
             * its absolute path. */
            zfree(server.exec_argv[j]);
            server.exec_argv[j] = zstrdup(server.configfile);
            j++;
        }

        /* All the other options are parsed and conceptually appended to the
         * configuration file. For instance --port 6380 will generate the
         * string "port 6380\n" to be parsed after the actual file name
         * is parsed, if any. */
        while(j != argc) {
            if (argv[j][0] == '-' && argv[j][1] == '-') {
                /* Option name */
                if (!strcmp(argv[j], "--check-rdb")) {
                    /* Argument has no options, need to skip for parsing. */
                    j++;
                    continue;
                }
                if (sdslen(options)) options = sdscat(options,"\n");
                options = sdscat(options,argv[j]+2);
                options = sdscat(options," ");
            } else {
                /* Option argument */
                options = sdscatrepr(options,argv[j],strlen(argv[j]));
                options = sdscat(options," ");
            }
            j++;
        }
        if (server.sentinel_mode && configfile && *configfile == '-') {
            serverLog(LL_WARNING,
                "Sentinel config from STDIN not allowed.");
            serverLog(LL_WARNING,
                "Sentinel needs config file on disk to save state.  Exiting...");
            exit(1);
        }
        resetServerSaveParams();
        loadServerConfig(configfile,options);
        sdsfree(options);
    }

    serverLog(LL_WARNING, "oO0OoO0OoO0Oo Redis is starting oO0OoO0OoO0Oo");
    serverLog(LL_WARNING,
        "Redis version=%s, bits=%d, commit=%s, modified=%d, pid=%d, just started",
            REDIS_VERSION,
            (sizeof(long) == 8) ? 64 : 32,
            redisGitSHA1(),
            strtol(redisGitDirty(),NULL,10) > 0,
            (int)getpid());

    if (argc == 1) {
        serverLog(LL_WARNING, "Warning: no config file specified, using the default config. In order to specify a config file use %s /path/to/%s.conf", argv[0], server.sentinel_mode ? "sentinel" : "redis");
    } else {
        serverLog(LL_WARNING, "Configuration loaded");
    }

    server.supervised = redisIsSupervised(server.supervised_mode);
    int background = server.daemonize && !server.supervised;
    if (background) daemonize();

    initServer();
    if (background || server.pidfile) createPidFile();
    redisSetProcTitle(argv[0]);
    redisAsciiArt();
    checkTcpBacklogSettings();

    if (!server.sentinel_mode) {
        /* Things not needed when running in Sentinel mode. */
        serverLog(LL_WARNING,"Server initialized");
    #ifdef __linux__
        linuxMemoryWarnings();
    #endif
        moduleLoadFromQueue();
        ACLLoadUsersAtStartup();
        InitServerLast();
        loadDataFromDisk();
        if (server.cluster_enabled) {
            if (verifyClusterConfigWithData() == C_ERR) {
                serverLog(LL_WARNING,
                    "You can't have keys in a DB different than DB 0 when in "
                    "Cluster mode. Exiting.");
                exit(1);
            }
        }
        if (server.ipfd_count > 0 || server.tlsfd_count > 0)
            serverLog(LL_NOTICE,"Ready to accept connections");
        if (server.sofd > 0)
            serverLog(LL_NOTICE,"The server is now ready to accept connections at %s", server.unixsocket);
    } else {
        InitServerLast();
        sentinelIsRunning();
    }

    /* Warning the user about suspicious maxmemory setting. */
    if (server.maxmemory > 0 && server.maxmemory < 1024*1024) {
        serverLog(LL_WARNING,"WARNING: You specified a maxmemory value that is less than 1MB (current value is %llu bytes). Are you sure this is what you really want?", server.maxmemory);
    }

    aeSetBeforeSleepProc(server.el,beforeSleep);
    aeSetAfterSleepProc(server.el,afterSleep);
    aeMain(server.el);
    aeDeleteEventLoop(server.el);
    return 0;
}