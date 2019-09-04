#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_47__   TYPE_8__ ;
typedef  struct TYPE_46__   TYPE_6__ ;
typedef  struct TYPE_45__   TYPE_5__ ;
typedef  struct TYPE_44__   TYPE_4__ ;
typedef  struct TYPE_43__   TYPE_3__ ;
typedef  struct TYPE_42__   TYPE_2__ ;
typedef  struct TYPE_41__   TYPE_1__ ;
typedef  struct TYPE_40__   TYPE_15__ ;

/* Type definitions */
typedef  long long uint64_t ;
typedef  scalar_t__ sds ;
typedef  int /*<<< orphan*/  robj ;
struct TYPE_44__ {long long configEpoch; scalar_t__ numslots; unsigned int numslaves; struct TYPE_44__* slaveof; int /*<<< orphan*/ * link; int /*<<< orphan*/ * slaves; int /*<<< orphan*/  name; } ;
typedef  TYPE_4__ clusterNode ;
struct TYPE_45__ {int argc; TYPE_3__* db; TYPE_15__** argv; } ;
typedef  TYPE_5__ client ;
struct TYPE_47__ {scalar_t__ cluster_enabled; TYPE_2__* cluster; TYPE_1__* db; } ;
struct TYPE_46__ {int /*<<< orphan*/  ok; int /*<<< orphan*/  syntaxerr; int /*<<< orphan*/  crlf; } ;
struct TYPE_43__ {int /*<<< orphan*/  dict; } ;
struct TYPE_42__ {size_t state; long long currentEpoch; long long* stats_bus_messages_sent; long long* stats_bus_messages_received; int mf_can_start; int /*<<< orphan*/  nodes; scalar_t__ mf_end; int /*<<< orphan*/  size; TYPE_4__** slots; TYPE_4__** importing_slots_from; TYPE_4__** migrating_slots_to; } ;
struct TYPE_41__ {int /*<<< orphan*/  dict; } ;
struct TYPE_40__ {scalar_t__ ptr; } ;

/* Variables and functions */
 int CLUSTERMSG_TYPE_COUNT ; 
 scalar_t__ CLUSTER_MF_TIMEOUT ; 
 int /*<<< orphan*/  CLUSTER_NAMELEN ; 
 long long CLUSTER_PORT_INCR ; 
 int CLUSTER_SLOTS ; 
 int CLUSTER_TODO_SAVE_CONFIG ; 
 int CLUSTER_TODO_UPDATE_STATE ; 
 int C_OK ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  OBJ_STRING ; 
 int /*<<< orphan*/  addReply (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyArrayLen (TYPE_5__*,unsigned int) ; 
 int /*<<< orphan*/  addReplyBulk (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addReplyBulkCBuffer (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyBulkCString (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  addReplyError (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  addReplyErrorFormat (TYPE_5__*,char*,...) ; 
 int /*<<< orphan*/  addReplyHelp (TYPE_5__*,char const**) ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  addReplySds (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  addReplySubcommandSyntaxError (TYPE_5__*) ; 
 int clusterAddSlot (TYPE_4__*,int) ; 
 int /*<<< orphan*/  clusterBlacklistAddNode (TYPE_4__*) ; 
 int clusterBumpConfigEpochWithoutConsensus () ; 
 int /*<<< orphan*/  clusterDelNode (TYPE_4__*) ; 
 int /*<<< orphan*/  clusterDelNodeSlots (TYPE_4__*) ; 
 int clusterDelSlot (int) ; 
 int /*<<< orphan*/  clusterDoBeforeSleep (int) ; 
 int /*<<< orphan*/  clusterFailoverReplaceYourMaster () ; 
 scalar_t__ clusterGenNodeDescription (int /*<<< orphan*/ ) ; 
 scalar_t__ clusterGenNodesDescription (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterGetMessageTypeString (int) ; 
 TYPE_4__* clusterLookupNode (scalar_t__) ; 
 scalar_t__ clusterNodeFailureReportsCount (TYPE_4__*) ; 
 int /*<<< orphan*/  clusterReplyMultiBulkSlots (TYPE_5__*) ; 
 int /*<<< orphan*/  clusterReset (int) ; 
 int clusterSaveConfig (int) ; 
 int /*<<< orphan*/  clusterSendMFStart (TYPE_4__*) ; 
 int /*<<< orphan*/  clusterSetMaster (TYPE_4__*) ; 
 scalar_t__ clusterStartHandshake (scalar_t__,long long,long long) ; 
 scalar_t__ countKeysInSlot (long long) ; 
 int /*<<< orphan*/ * createObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  decrRefCount (int /*<<< orphan*/ *) ; 
 scalar_t__ dictSize (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 unsigned int getKeysInSlot (long long,int /*<<< orphan*/ **,long long) ; 
 int getLongLongFromObject (TYPE_15__*,long long*) ; 
 int getLongLongFromObjectOrReply (TYPE_5__*,TYPE_15__*,long long*,int /*<<< orphan*/ *) ; 
 int getSlotOrReply (TYPE_5__*,TYPE_15__*) ; 
 scalar_t__ keyHashSlot (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mstime () ; 
 TYPE_4__* myself ; 
 scalar_t__ nodeFailed (TYPE_4__*) ; 
 scalar_t__ nodeIsMaster (TYPE_4__*) ; 
 scalar_t__ nodeIsSlave (TYPE_4__*) ; 
 scalar_t__ nodeTimedOut (TYPE_4__*) ; 
 int /*<<< orphan*/  resetManualFailover () ; 
 scalar_t__ sdscatprintf (scalar_t__,char*,...) ; 
 scalar_t__ sdsempty () ; 
 int /*<<< orphan*/  sdsfree (scalar_t__) ; 
 scalar_t__ sdslen (scalar_t__) ; 
 TYPE_8__ server ; 
 int /*<<< orphan*/  serverAssertWithInfo (TYPE_5__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_6__ shared ; 
 int /*<<< orphan*/  strcasecmp (scalar_t__,char*) ; 
 long long strerror (scalar_t__) ; 
 int /*<<< orphan*/  zfree (unsigned char*) ; 
 void* zmalloc (int) ; 

void clusterCommand(client *c) {
    if (server.cluster_enabled == 0) {
        addReplyError(c,"This instance has cluster support disabled");
        return;
    }

    if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"help")) {
        const char *help[] = {
"ADDSLOTS <slot> [slot ...] -- Assign slots to current node.",
"BUMPEPOCH -- Advance the cluster config epoch.",
"COUNT-failure-reports <node-id> -- Return number of failure reports for <node-id>.",
"COUNTKEYSINSLOT <slot> - Return the number of keys in <slot>.",
"DELSLOTS <slot> [slot ...] -- Delete slots information from current node.",
"FAILOVER [force|takeover] -- Promote current replica node to being a master.",
"FORGET <node-id> -- Remove a node from the cluster.",
"GETKEYSINSLOT <slot> <count> -- Return key names stored by current node in a slot.",
"FLUSHSLOTS -- Delete current node own slots information.",
"INFO - Return onformation about the cluster.",
"KEYSLOT <key> -- Return the hash slot for <key>.",
"MEET <ip> <port> [bus-port] -- Connect nodes into a working cluster.",
"MYID -- Return the node id.",
"NODES -- Return cluster configuration seen by node. Output format:",
"    <id> <ip:port> <flags> <master> <pings> <pongs> <epoch> <link> <slot> ... <slot>",
"REPLICATE <node-id> -- Configure current node as replica to <node-id>.",
"RESET [hard|soft] -- Reset current node (default: soft).",
"SET-config-epoch <epoch> - Set config epoch of current node.",
"SETSLOT <slot> (importing|migrating|stable|node <node-id>) -- Set slot state.",
"REPLICAS <node-id> -- Return <node-id> replicas.",
"SLOTS -- Return information about slots range mappings. Each range is made of:",
"    start, end, master and replicas IP addresses, ports and ids",
NULL
        };
        addReplyHelp(c, help);
    } else if (!strcasecmp(c->argv[1]->ptr,"meet") && (c->argc == 4 || c->argc == 5)) {
        /* CLUSTER MEET <ip> <port> [cport] */
        long long port, cport;

        if (getLongLongFromObject(c->argv[3], &port) != C_OK) {
            addReplyErrorFormat(c,"Invalid TCP base port specified: %s",
                                (char*)c->argv[3]->ptr);
            return;
        }

        if (c->argc == 5) {
            if (getLongLongFromObject(c->argv[4], &cport) != C_OK) {
                addReplyErrorFormat(c,"Invalid TCP bus port specified: %s",
                                    (char*)c->argv[4]->ptr);
                return;
            }
        } else {
            cport = port + CLUSTER_PORT_INCR;
        }

        if (clusterStartHandshake(c->argv[2]->ptr,port,cport) == 0 &&
            errno == EINVAL)
        {
            addReplyErrorFormat(c,"Invalid node address specified: %s:%s",
                            (char*)c->argv[2]->ptr, (char*)c->argv[3]->ptr);
        } else {
            addReply(c,shared.ok);
        }
    } else if (!strcasecmp(c->argv[1]->ptr,"nodes") && c->argc == 2) {
        /* CLUSTER NODES */
        robj *o;
        sds ci = clusterGenNodesDescription(0);

        o = createObject(OBJ_STRING,ci);
        addReplyBulk(c,o);
        decrRefCount(o);
    } else if (!strcasecmp(c->argv[1]->ptr,"myid") && c->argc == 2) {
        /* CLUSTER MYID */
        addReplyBulkCBuffer(c,myself->name, CLUSTER_NAMELEN);
    } else if (!strcasecmp(c->argv[1]->ptr,"slots") && c->argc == 2) {
        /* CLUSTER SLOTS */
        clusterReplyMultiBulkSlots(c);
    } else if (!strcasecmp(c->argv[1]->ptr,"flushslots") && c->argc == 2) {
        /* CLUSTER FLUSHSLOTS */
        if (dictSize(server.db[0].dict) != 0) {
            addReplyError(c,"DB must be empty to perform CLUSTER FLUSHSLOTS.");
            return;
        }
        clusterDelNodeSlots(myself);
        clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|CLUSTER_TODO_SAVE_CONFIG);
        addReply(c,shared.ok);
    } else if ((!strcasecmp(c->argv[1]->ptr,"addslots") ||
               !strcasecmp(c->argv[1]->ptr,"delslots")) && c->argc >= 3)
    {
        /* CLUSTER ADDSLOTS <slot> [slot] ... */
        /* CLUSTER DELSLOTS <slot> [slot] ... */
        int j, slot;
        unsigned char *slots = zmalloc(CLUSTER_SLOTS);
        int del = !strcasecmp(c->argv[1]->ptr,"delslots");

        memset(slots,0,CLUSTER_SLOTS);
        /* Check that all the arguments are parseable and that all the
         * slots are not already busy. */
        for (j = 2; j < c->argc; j++) {
            if ((slot = getSlotOrReply(c,c->argv[j])) == -1) {
                zfree(slots);
                return;
            }
            if (del && server.cluster->slots[slot] == NULL) {
                addReplyErrorFormat(c,"Slot %d is already unassigned", slot);
                zfree(slots);
                return;
            } else if (!del && server.cluster->slots[slot]) {
                addReplyErrorFormat(c,"Slot %d is already busy", slot);
                zfree(slots);
                return;
            }
            if (slots[slot]++ == 1) {
                addReplyErrorFormat(c,"Slot %d specified multiple times",
                    (int)slot);
                zfree(slots);
                return;
            }
        }
        for (j = 0; j < CLUSTER_SLOTS; j++) {
            if (slots[j]) {
                int retval;

                /* If this slot was set as importing we can clear this
                 * state as now we are the real owner of the slot. */
                if (server.cluster->importing_slots_from[j])
                    server.cluster->importing_slots_from[j] = NULL;

                retval = del ? clusterDelSlot(j) :
                               clusterAddSlot(myself,j);
                serverAssertWithInfo(c,NULL,retval == C_OK);
            }
        }
        zfree(slots);
        clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|CLUSTER_TODO_SAVE_CONFIG);
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"setslot") && c->argc >= 4) {
        /* SETSLOT 10 MIGRATING <node ID> */
        /* SETSLOT 10 IMPORTING <node ID> */
        /* SETSLOT 10 STABLE */
        /* SETSLOT 10 NODE <node ID> */
        int slot;
        clusterNode *n;

        if (nodeIsSlave(myself)) {
            addReplyError(c,"Please use SETSLOT only with masters.");
            return;
        }

        if ((slot = getSlotOrReply(c,c->argv[2])) == -1) return;

        if (!strcasecmp(c->argv[3]->ptr,"migrating") && c->argc == 5) {
            if (server.cluster->slots[slot] != myself) {
                addReplyErrorFormat(c,"I'm not the owner of hash slot %u",slot);
                return;
            }
            if ((n = clusterLookupNode(c->argv[4]->ptr)) == NULL) {
                addReplyErrorFormat(c,"I don't know about node %s",
                    (char*)c->argv[4]->ptr);
                return;
            }
            server.cluster->migrating_slots_to[slot] = n;
        } else if (!strcasecmp(c->argv[3]->ptr,"importing") && c->argc == 5) {
            if (server.cluster->slots[slot] == myself) {
                addReplyErrorFormat(c,
                    "I'm already the owner of hash slot %u",slot);
                return;
            }
            if ((n = clusterLookupNode(c->argv[4]->ptr)) == NULL) {
                addReplyErrorFormat(c,"I don't know about node %s",
                    (char*)c->argv[4]->ptr);
                return;
            }
            server.cluster->importing_slots_from[slot] = n;
        } else if (!strcasecmp(c->argv[3]->ptr,"stable") && c->argc == 4) {
            /* CLUSTER SETSLOT <SLOT> STABLE */
            server.cluster->importing_slots_from[slot] = NULL;
            server.cluster->migrating_slots_to[slot] = NULL;
        } else if (!strcasecmp(c->argv[3]->ptr,"node") && c->argc == 5) {
            /* CLUSTER SETSLOT <SLOT> NODE <NODE ID> */
            clusterNode *n = clusterLookupNode(c->argv[4]->ptr);

            if (!n) {
                addReplyErrorFormat(c,"Unknown node %s",
                    (char*)c->argv[4]->ptr);
                return;
            }
            /* If this hash slot was served by 'myself' before to switch
             * make sure there are no longer local keys for this hash slot. */
            if (server.cluster->slots[slot] == myself && n != myself) {
                if (countKeysInSlot(slot) != 0) {
                    addReplyErrorFormat(c,
                        "Can't assign hashslot %d to a different node "
                        "while I still hold keys for this hash slot.", slot);
                    return;
                }
            }
            /* If this slot is in migrating status but we have no keys
             * for it assigning the slot to another node will clear
             * the migratig status. */
            if (countKeysInSlot(slot) == 0 &&
                server.cluster->migrating_slots_to[slot])
                server.cluster->migrating_slots_to[slot] = NULL;

            /* If this node was importing this slot, assigning the slot to
             * itself also clears the importing status. */
            if (n == myself &&
                server.cluster->importing_slots_from[slot])
            {
                /* This slot was manually migrated, set this node configEpoch
                 * to a new epoch so that the new version can be propagated
                 * by the cluster.
                 *
                 * Note that if this ever results in a collision with another
                 * node getting the same configEpoch, for example because a
                 * failover happens at the same time we close the slot, the
                 * configEpoch collision resolution will fix it assigning
                 * a different epoch to each node. */
                if (clusterBumpConfigEpochWithoutConsensus() == C_OK) {
                    serverLog(LL_WARNING,
                        "configEpoch updated after importing slot %d", slot);
                }
                server.cluster->importing_slots_from[slot] = NULL;
            }
            clusterDelSlot(slot);
            clusterAddSlot(n,slot);
        } else {
            addReplyError(c,
                "Invalid CLUSTER SETSLOT action or number of arguments. Try CLUSTER HELP");
            return;
        }
        clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|CLUSTER_TODO_UPDATE_STATE);
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"bumpepoch") && c->argc == 2) {
        /* CLUSTER BUMPEPOCH */
        int retval = clusterBumpConfigEpochWithoutConsensus();
        sds reply = sdscatprintf(sdsempty(),"+%s %llu\r\n",
                (retval == C_OK) ? "BUMPED" : "STILL",
                (unsigned long long) myself->configEpoch);
        addReplySds(c,reply);
    } else if (!strcasecmp(c->argv[1]->ptr,"info") && c->argc == 2) {
        /* CLUSTER INFO */
        char *statestr[] = {"ok","fail","needhelp"};
        int slots_assigned = 0, slots_ok = 0, slots_pfail = 0, slots_fail = 0;
        uint64_t myepoch;
        int j;

        for (j = 0; j < CLUSTER_SLOTS; j++) {
            clusterNode *n = server.cluster->slots[j];

            if (n == NULL) continue;
            slots_assigned++;
            if (nodeFailed(n)) {
                slots_fail++;
            } else if (nodeTimedOut(n)) {
                slots_pfail++;
            } else {
                slots_ok++;
            }
        }

        myepoch = (nodeIsSlave(myself) && myself->slaveof) ?
                  myself->slaveof->configEpoch : myself->configEpoch;

        sds info = sdscatprintf(sdsempty(),
            "cluster_state:%s\r\n"
            "cluster_slots_assigned:%d\r\n"
            "cluster_slots_ok:%d\r\n"
            "cluster_slots_pfail:%d\r\n"
            "cluster_slots_fail:%d\r\n"
            "cluster_known_nodes:%lu\r\n"
            "cluster_size:%d\r\n"
            "cluster_current_epoch:%llu\r\n"
            "cluster_my_epoch:%llu\r\n"
            , statestr[server.cluster->state],
            slots_assigned,
            slots_ok,
            slots_pfail,
            slots_fail,
            dictSize(server.cluster->nodes),
            server.cluster->size,
            (unsigned long long) server.cluster->currentEpoch,
            (unsigned long long) myepoch
        );

        /* Show stats about messages sent and received. */
        long long tot_msg_sent = 0;
        long long tot_msg_received = 0;

        for (int i = 0; i < CLUSTERMSG_TYPE_COUNT; i++) {
            if (server.cluster->stats_bus_messages_sent[i] == 0) continue;
            tot_msg_sent += server.cluster->stats_bus_messages_sent[i];
            info = sdscatprintf(info,
                "cluster_stats_messages_%s_sent:%lld\r\n",
                clusterGetMessageTypeString(i),
                server.cluster->stats_bus_messages_sent[i]);
        }
        info = sdscatprintf(info,
            "cluster_stats_messages_sent:%lld\r\n", tot_msg_sent);

        for (int i = 0; i < CLUSTERMSG_TYPE_COUNT; i++) {
            if (server.cluster->stats_bus_messages_received[i] == 0) continue;
            tot_msg_received += server.cluster->stats_bus_messages_received[i];
            info = sdscatprintf(info,
                "cluster_stats_messages_%s_received:%lld\r\n",
                clusterGetMessageTypeString(i),
                server.cluster->stats_bus_messages_received[i]);
        }
        info = sdscatprintf(info,
            "cluster_stats_messages_received:%lld\r\n", tot_msg_received);

        /* Produce the reply protocol. */
        addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",
            (unsigned long)sdslen(info)));
        addReplySds(c,info);
        addReply(c,shared.crlf);
    } else if (!strcasecmp(c->argv[1]->ptr,"saveconfig") && c->argc == 2) {
        int retval = clusterSaveConfig(1);

        if (retval == 0)
            addReply(c,shared.ok);
        else
            addReplyErrorFormat(c,"error saving the cluster node config: %s",
                strerror(errno));
    } else if (!strcasecmp(c->argv[1]->ptr,"keyslot") && c->argc == 3) {
        /* CLUSTER KEYSLOT <key> */
        sds key = c->argv[2]->ptr;

        addReplyLongLong(c,keyHashSlot(key,sdslen(key)));
    } else if (!strcasecmp(c->argv[1]->ptr,"countkeysinslot") && c->argc == 3) {
        /* CLUSTER COUNTKEYSINSLOT <slot> */
        long long slot;

        if (getLongLongFromObjectOrReply(c,c->argv[2],&slot,NULL) != C_OK)
            return;
        if (slot < 0 || slot >= CLUSTER_SLOTS) {
            addReplyError(c,"Invalid slot");
            return;
        }
        addReplyLongLong(c,countKeysInSlot(slot));
    } else if (!strcasecmp(c->argv[1]->ptr,"getkeysinslot") && c->argc == 4) {
        /* CLUSTER GETKEYSINSLOT <slot> <count> */
        long long maxkeys, slot;
        unsigned int numkeys, j;
        robj **keys;

        if (getLongLongFromObjectOrReply(c,c->argv[2],&slot,NULL) != C_OK)
            return;
        if (getLongLongFromObjectOrReply(c,c->argv[3],&maxkeys,NULL)
            != C_OK)
            return;
        if (slot < 0 || slot >= CLUSTER_SLOTS || maxkeys < 0) {
            addReplyError(c,"Invalid slot or number of keys");
            return;
        }

        /* Avoid allocating more than needed in case of large COUNT argument
         * and smaller actual number of keys. */
        unsigned int keys_in_slot = countKeysInSlot(slot);
        if (maxkeys > keys_in_slot) maxkeys = keys_in_slot;

        keys = zmalloc(sizeof(robj*)*maxkeys);
        numkeys = getKeysInSlot(slot, keys, maxkeys);
        addReplyArrayLen(c,numkeys);
        for (j = 0; j < numkeys; j++) {
            addReplyBulk(c,keys[j]);
            decrRefCount(keys[j]);
        }
        zfree(keys);
    } else if (!strcasecmp(c->argv[1]->ptr,"forget") && c->argc == 3) {
        /* CLUSTER FORGET <NODE ID> */
        clusterNode *n = clusterLookupNode(c->argv[2]->ptr);

        if (!n) {
            addReplyErrorFormat(c,"Unknown node %s", (char*)c->argv[2]->ptr);
            return;
        } else if (n == myself) {
            addReplyError(c,"I tried hard but I can't forget myself...");
            return;
        } else if (nodeIsSlave(myself) && myself->slaveof == n) {
            addReplyError(c,"Can't forget my master!");
            return;
        }
        clusterBlacklistAddNode(n);
        clusterDelNode(n);
        clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|
                             CLUSTER_TODO_SAVE_CONFIG);
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"replicate") && c->argc == 3) {
        /* CLUSTER REPLICATE <NODE ID> */
        clusterNode *n = clusterLookupNode(c->argv[2]->ptr);

        /* Lookup the specified node in our table. */
        if (!n) {
            addReplyErrorFormat(c,"Unknown node %s", (char*)c->argv[2]->ptr);
            return;
        }

        /* I can't replicate myself. */
        if (n == myself) {
            addReplyError(c,"Can't replicate myself");
            return;
        }

        /* Can't replicate a slave. */
        if (nodeIsSlave(n)) {
            addReplyError(c,"I can only replicate a master, not a replica.");
            return;
        }

        /* If the instance is currently a master, it should have no assigned
         * slots nor keys to accept to replicate some other node.
         * Slaves can switch to another master without issues. */
        if (nodeIsMaster(myself) &&
            (myself->numslots != 0 || dictSize(server.db[0].dict) != 0)) {
            addReplyError(c,
                "To set a master the node must be empty and "
                "without assigned slots.");
            return;
        }

        /* Set the master. */
        clusterSetMaster(n);
        clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|CLUSTER_TODO_SAVE_CONFIG);
        addReply(c,shared.ok);
    } else if ((!strcasecmp(c->argv[1]->ptr,"slaves") ||
                !strcasecmp(c->argv[1]->ptr,"replicas")) && c->argc == 3) {
        /* CLUSTER SLAVES <NODE ID> */
        clusterNode *n = clusterLookupNode(c->argv[2]->ptr);
        int j;

        /* Lookup the specified node in our table. */
        if (!n) {
            addReplyErrorFormat(c,"Unknown node %s", (char*)c->argv[2]->ptr);
            return;
        }

        if (nodeIsSlave(n)) {
            addReplyError(c,"The specified node is not a master");
            return;
        }

        addReplyArrayLen(c,n->numslaves);
        for (j = 0; j < n->numslaves; j++) {
            sds ni = clusterGenNodeDescription(n->slaves[j]);
            addReplyBulkCString(c,ni);
            sdsfree(ni);
        }
    } else if (!strcasecmp(c->argv[1]->ptr,"count-failure-reports") &&
               c->argc == 3)
    {
        /* CLUSTER COUNT-FAILURE-REPORTS <NODE ID> */
        clusterNode *n = clusterLookupNode(c->argv[2]->ptr);

        if (!n) {
            addReplyErrorFormat(c,"Unknown node %s", (char*)c->argv[2]->ptr);
            return;
        } else {
            addReplyLongLong(c,clusterNodeFailureReportsCount(n));
        }
    } else if (!strcasecmp(c->argv[1]->ptr,"failover") &&
               (c->argc == 2 || c->argc == 3))
    {
        /* CLUSTER FAILOVER [FORCE|TAKEOVER] */
        int force = 0, takeover = 0;

        if (c->argc == 3) {
            if (!strcasecmp(c->argv[2]->ptr,"force")) {
                force = 1;
            } else if (!strcasecmp(c->argv[2]->ptr,"takeover")) {
                takeover = 1;
                force = 1; /* Takeover also implies force. */
            } else {
                addReply(c,shared.syntaxerr);
                return;
            }
        }

        /* Check preconditions. */
        if (nodeIsMaster(myself)) {
            addReplyError(c,"You should send CLUSTER FAILOVER to a replica");
            return;
        } else if (myself->slaveof == NULL) {
            addReplyError(c,"I'm a replica but my master is unknown to me");
            return;
        } else if (!force &&
                   (nodeFailed(myself->slaveof) ||
                    myself->slaveof->link == NULL))
        {
            addReplyError(c,"Master is down or failed, "
                            "please use CLUSTER FAILOVER FORCE");
            return;
        }
        resetManualFailover();
        server.cluster->mf_end = mstime() + CLUSTER_MF_TIMEOUT;

        if (takeover) {
            /* A takeover does not perform any initial check. It just
             * generates a new configuration epoch for this node without
             * consensus, claims the master's slots, and broadcast the new
             * configuration. */
            serverLog(LL_WARNING,"Taking over the master (user request).");
            clusterBumpConfigEpochWithoutConsensus();
            clusterFailoverReplaceYourMaster();
        } else if (force) {
            /* If this is a forced failover, we don't need to talk with our
             * master to agree about the offset. We just failover taking over
             * it without coordination. */
            serverLog(LL_WARNING,"Forced failover user request accepted.");
            server.cluster->mf_can_start = 1;
        } else {
            serverLog(LL_WARNING,"Manual failover user request accepted.");
            clusterSendMFStart(myself->slaveof);
        }
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"set-config-epoch") && c->argc == 3)
    {
        /* CLUSTER SET-CONFIG-EPOCH <epoch>
         *
         * The user is allowed to set the config epoch only when a node is
         * totally fresh: no config epoch, no other known node, and so forth.
         * This happens at cluster creation time to start with a cluster where
         * every node has a different node ID, without to rely on the conflicts
         * resolution system which is too slow when a big cluster is created. */
        long long epoch;

        if (getLongLongFromObjectOrReply(c,c->argv[2],&epoch,NULL) != C_OK)
            return;

        if (epoch < 0) {
            addReplyErrorFormat(c,"Invalid config epoch specified: %lld",epoch);
        } else if (dictSize(server.cluster->nodes) > 1) {
            addReplyError(c,"The user can assign a config epoch only when the "
                            "node does not know any other node.");
        } else if (myself->configEpoch != 0) {
            addReplyError(c,"Node config epoch is already non-zero");
        } else {
            myself->configEpoch = epoch;
            serverLog(LL_WARNING,
                "configEpoch set to %llu via CLUSTER SET-CONFIG-EPOCH",
                (unsigned long long) myself->configEpoch);

            if (server.cluster->currentEpoch < (uint64_t)epoch)
                server.cluster->currentEpoch = epoch;
            /* No need to fsync the config here since in the unlucky event
             * of a failure to persist the config, the conflict resolution code
             * will assign an unique config to this node. */
            clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|
                                 CLUSTER_TODO_SAVE_CONFIG);
            addReply(c,shared.ok);
        }
    } else if (!strcasecmp(c->argv[1]->ptr,"reset") &&
               (c->argc == 2 || c->argc == 3))
    {
        /* CLUSTER RESET [SOFT|HARD] */
        int hard = 0;

        /* Parse soft/hard argument. Default is soft. */
        if (c->argc == 3) {
            if (!strcasecmp(c->argv[2]->ptr,"hard")) {
                hard = 1;
            } else if (!strcasecmp(c->argv[2]->ptr,"soft")) {
                hard = 0;
            } else {
                addReply(c,shared.syntaxerr);
                return;
            }
        }

        /* Slaves can be reset while containing data, but not master nodes
         * that must be empty. */
        if (nodeIsMaster(myself) && dictSize(c->db->dict) != 0) {
            addReplyError(c,"CLUSTER RESET can't be called with "
                            "master nodes containing keys");
            return;
        }
        clusterReset(hard);
        addReply(c,shared.ok);
    } else {
        addReplySubcommandSyntaxError(c);
        return;
    }
}