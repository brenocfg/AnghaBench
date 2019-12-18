#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  clusterState ;
struct TYPE_8__ {int port; int cport; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int cfd_count; int tls_port; int port; int cluster_announce_port; int cluster_announce_bus_port; TYPE_1__* cluster; int /*<<< orphan*/ * cfd; int /*<<< orphan*/  el; scalar_t__ tls_cluster; int /*<<< orphan*/  cluster_configfile; } ;
struct TYPE_6__ {int size; scalar_t__ mf_end; int /*<<< orphan*/  slots_keys_count; int /*<<< orphan*/  slots_to_keys; TYPE_3__* myself; int /*<<< orphan*/  slots; scalar_t__ stats_pfail_nodes; scalar_t__* stats_bus_messages_received; scalar_t__* stats_bus_messages_sent; scalar_t__ lastVoteEpoch; int /*<<< orphan*/  cant_failover_reason; scalar_t__ failover_auth_epoch; scalar_t__ failover_auth_rank; scalar_t__ failover_auth_count; scalar_t__ failover_auth_time; void* nodes_black_list; void* nodes; scalar_t__ todo_before_sleep; int /*<<< orphan*/  state; scalar_t__ currentEpoch; } ;

/* Variables and functions */
 scalar_t__ AE_ERR ; 
 int /*<<< orphan*/  AE_READABLE ; 
 int CLUSTERMSG_TYPE_COUNT ; 
 int /*<<< orphan*/  CLUSTER_CANT_FAILOVER_NONE ; 
 int /*<<< orphan*/  CLUSTER_FAIL ; 
 int CLUSTER_NODE_MASTER ; 
 int CLUSTER_NODE_MYSELF ; 
 int CLUSTER_PORT_INCR ; 
 scalar_t__ C_ERR ; 
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  LL_WARNING ; 
 scalar_t__ aeCreateFileEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clusterAcceptHandler ; 
 int /*<<< orphan*/  clusterAddNode (TYPE_3__*) ; 
 int /*<<< orphan*/  clusterCloseAllSlots () ; 
 scalar_t__ clusterLoadConfig (int /*<<< orphan*/ ) ; 
 scalar_t__ clusterLockConfig (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterNodesBlackListDictType ; 
 int /*<<< orphan*/  clusterNodesDictType ; 
 int /*<<< orphan*/  clusterSaveConfigOrDie (int) ; 
 int /*<<< orphan*/  clusterUpdateMyselfFlags () ; 
 TYPE_3__* createClusterNode (int /*<<< orphan*/ *,int) ; 
 void* dictCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ listenToPort (int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* myself ; 
 int /*<<< orphan*/  raxNew () ; 
 int /*<<< orphan*/  resetManualFailover () ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 
 TYPE_1__* zmalloc (int) ; 

void clusterInit(void) {
    int saveconf = 0;

    server.cluster = zmalloc(sizeof(clusterState));
    server.cluster->myself = NULL;
    server.cluster->currentEpoch = 0;
    server.cluster->state = CLUSTER_FAIL;
    server.cluster->size = 1;
    server.cluster->todo_before_sleep = 0;
    server.cluster->nodes = dictCreate(&clusterNodesDictType,NULL);
    server.cluster->nodes_black_list =
        dictCreate(&clusterNodesBlackListDictType,NULL);
    server.cluster->failover_auth_time = 0;
    server.cluster->failover_auth_count = 0;
    server.cluster->failover_auth_rank = 0;
    server.cluster->failover_auth_epoch = 0;
    server.cluster->cant_failover_reason = CLUSTER_CANT_FAILOVER_NONE;
    server.cluster->lastVoteEpoch = 0;
    for (int i = 0; i < CLUSTERMSG_TYPE_COUNT; i++) {
        server.cluster->stats_bus_messages_sent[i] = 0;
        server.cluster->stats_bus_messages_received[i] = 0;
    }
    server.cluster->stats_pfail_nodes = 0;
    memset(server.cluster->slots,0, sizeof(server.cluster->slots));
    clusterCloseAllSlots();

    /* Lock the cluster config file to make sure every node uses
     * its own nodes.conf. */
    if (clusterLockConfig(server.cluster_configfile) == C_ERR)
        exit(1);

    /* Load or create a new nodes configuration. */
    if (clusterLoadConfig(server.cluster_configfile) == C_ERR) {
        /* No configuration found. We will just use the random name provided
         * by the createClusterNode() function. */
        myself = server.cluster->myself =
            createClusterNode(NULL,CLUSTER_NODE_MYSELF|CLUSTER_NODE_MASTER);
        serverLog(LL_NOTICE,"No cluster configuration found, I'm %.40s",
            myself->name);
        clusterAddNode(myself);
        saveconf = 1;
    }
    if (saveconf) clusterSaveConfigOrDie(1);

    /* We need a listening TCP port for our cluster messaging needs. */
    server.cfd_count = 0;

    /* Port sanity check II
     * The other handshake port check is triggered too late to stop
     * us from trying to use a too-high cluster port number. */
    int port = server.tls_cluster ? server.tls_port : server.port;
    if (port > (65535-CLUSTER_PORT_INCR)) {
        serverLog(LL_WARNING, "Redis port number too high. "
                   "Cluster communication port is 10,000 port "
                   "numbers higher than your Redis port. "
                   "Your Redis port number must be "
                   "lower than 55535.");
        exit(1);
    }
    if (listenToPort(port+CLUSTER_PORT_INCR,
        server.cfd,&server.cfd_count) == C_ERR)
    {
        exit(1);
    } else {
        int j;

        for (j = 0; j < server.cfd_count; j++) {
            if (aeCreateFileEvent(server.el, server.cfd[j], AE_READABLE,
                clusterAcceptHandler, NULL) == AE_ERR)
                    serverPanic("Unrecoverable error creating Redis Cluster "
                                "file event.");
        }
    }

    /* The slots -> keys map is a radix tree. Initialize it here. */
    server.cluster->slots_to_keys = raxNew();
    memset(server.cluster->slots_keys_count,0,
           sizeof(server.cluster->slots_keys_count));

    /* Set myself->port / cport to my listening ports, we'll just need to
     * discover the IP address via MEET messages. */
    myself->port = port;
    myself->cport = port+CLUSTER_PORT_INCR;
    if (server.cluster_announce_port)
        myself->port = server.cluster_announce_port;
    if (server.cluster_announce_bus_port)
        myself->cport = server.cluster_announce_bus_port;

    server.cluster->mf_end = 0;
    resetManualFailover();
    clusterUpdateMyselfFlags();
}