#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_19__ {TYPE_3__* value; } ;
typedef  TYPE_2__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
typedef  int /*<<< orphan*/  list ;
struct TYPE_20__ {float weight; int flags; scalar_t__ slots_count; int balance; char* ip; int port; int /*<<< orphan*/  slot; int /*<<< orphan*/  source; scalar_t__ replicate; } ;
typedef  TYPE_3__ clusterManagerReshardTableItem ;
typedef  TYPE_3__ clusterManagerNode ;
struct TYPE_18__ {char** weight; int weight_argc; int flags; float threshold; } ;
struct TYPE_17__ {int /*<<< orphan*/ * errors; int /*<<< orphan*/ * nodes; } ;
struct TYPE_16__ {TYPE_1__ cluster_manager_command; scalar_t__ verbose; } ;

/* Variables and functions */
 int CLUSTER_MANAGER_CMD_FLAG_EMPTYMASTER ; 
 int CLUSTER_MANAGER_CMD_FLAG_SIMULATE ; 
 int CLUSTER_MANAGER_FLAG_SLAVE ; 
 char* CLUSTER_MANAGER_INVALID_HOST_ARG ; 
 int CLUSTER_MANAGER_OPT_QUIET ; 
 int CLUSTER_MANAGER_OPT_UPDATE ; 
 scalar_t__ CLUSTER_MANAGER_SLOTS ; 
 int abs (int) ; 
 float atof (char*) ; 
 int /*<<< orphan*/  clusterManagerCheckCluster (int) ; 
 int /*<<< orphan*/  clusterManagerCompareNodeBalance ; 
 int /*<<< orphan*/ * clusterManagerComputeReshardTable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  clusterManagerLoadInfoFromNode (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterManagerLogErr (char*,...) ; 
 int /*<<< orphan*/  clusterManagerLogInfo (char*,int,float) ; 
 int /*<<< orphan*/  clusterManagerLogWarn (char*,float) ; 
 int clusterManagerMoveSlot (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 TYPE_3__* clusterManagerNewNode (char*,int) ; 
 TYPE_3__* clusterManagerNodeByAbbreviatedName (char*) ; 
 int /*<<< orphan*/  clusterManagerReleaseReshardTable (int /*<<< orphan*/ *) ; 
 TYPE_11__ cluster_manager ; 
 TYPE_10__ config ; 
 float fabs (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  getClusterHostFromCmdArgs (int,char**,char**,int*) ; 
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/ * listCreate () ; 
 scalar_t__ listLength (int /*<<< orphan*/ *) ; 
 TYPE_2__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  qsort (TYPE_3__**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  zfree (TYPE_3__**) ; 
 TYPE_3__** zmalloc (int) ; 

__attribute__((used)) static int clusterManagerCommandRebalance(int argc, char **argv) {
    int port = 0;
    char *ip = NULL;
    clusterManagerNode **weightedNodes = NULL;
    list *involved = NULL;
    if (!getClusterHostFromCmdArgs(argc, argv, &ip, &port)) goto invalid_args;
    clusterManagerNode *node = clusterManagerNewNode(ip, port);
    if (!clusterManagerLoadInfoFromNode(node, 0)) return 0;
    int result = 1, i;
    if (config.cluster_manager_command.weight != NULL) {
        for (i = 0; i < config.cluster_manager_command.weight_argc; i++) {
            char *name = config.cluster_manager_command.weight[i];
            char *p = strchr(name, '=');
            if (p == NULL) {
                result = 0;
                goto cleanup;
            }
            *p = '\0';
            float w = atof(++p);
            clusterManagerNode *n = clusterManagerNodeByAbbreviatedName(name);
            if (n == NULL) {
                clusterManagerLogErr("*** No such master node %s\n", name);
                result = 0;
                goto cleanup;
            }
            n->weight = w;
        }
    }
    float total_weight = 0;
    int nodes_involved = 0;
    int use_empty = config.cluster_manager_command.flags &
                    CLUSTER_MANAGER_CMD_FLAG_EMPTYMASTER;
    involved = listCreate();
    listIter li;
    listNode *ln;
    listRewind(cluster_manager.nodes, &li);
    /* Compute the total cluster weight. */
    while ((ln = listNext(&li)) != NULL) {
        clusterManagerNode *n = ln->value;
        if (n->flags & CLUSTER_MANAGER_FLAG_SLAVE || n->replicate)
            continue;
        if (!use_empty && n->slots_count == 0) {
            n->weight = 0;
            continue;
        }
        total_weight += n->weight;
        nodes_involved++;
        listAddNodeTail(involved, n);
    }
    weightedNodes = zmalloc(nodes_involved * sizeof(clusterManagerNode *));
    if (weightedNodes == NULL) goto cleanup;
    /* Check cluster, only proceed if it looks sane. */
    clusterManagerCheckCluster(1);
    if (cluster_manager.errors && listLength(cluster_manager.errors) > 0) {
        clusterManagerLogErr("*** Please fix your cluster problems "
                             "before rebalancing\n");
        result = 0;
        goto cleanup;
    }
    /* Calculate the slots balance for each node. It's the number of
     * slots the node should lose (if positive) or gain (if negative)
     * in order to be balanced. */
    int threshold_reached = 0, total_balance = 0;
    float threshold = config.cluster_manager_command.threshold;
    i = 0;
    listRewind(involved, &li);
    while ((ln = listNext(&li)) != NULL) {
        clusterManagerNode *n = ln->value;
        weightedNodes[i++] = n;
        int expected = (int) (((float)CLUSTER_MANAGER_SLOTS / total_weight) *
                        n->weight);
        n->balance = n->slots_count - expected;
        total_balance += n->balance;
        /* Compute the percentage of difference between the
         * expected number of slots and the real one, to see
         * if it's over the threshold specified by the user. */
        int over_threshold = 0;
        if (threshold > 0) {
            if (n->slots_count > 0) {
                float err_perc = fabs((100-(100.0*expected/n->slots_count)));
                if (err_perc > threshold) over_threshold = 1;
            } else if (expected > 1) {
                over_threshold = 1;
            }
        }
        if (over_threshold) threshold_reached = 1;
    }
    if (!threshold_reached) {
        clusterManagerLogWarn("*** No rebalancing needed! "
                             "All nodes are within the %.2f%% threshold.\n",
                             config.cluster_manager_command.threshold);
        goto cleanup;
    }
    /* Because of rounding, it is possible that the balance of all nodes
     * summed does not give 0. Make sure that nodes that have to provide
     * slots are always matched by nodes receiving slots. */
    while (total_balance > 0) {
        listRewind(involved, &li);
        while ((ln = listNext(&li)) != NULL) {
            clusterManagerNode *n = ln->value;
            if (n->balance <= 0 && total_balance > 0) {
                n->balance--;
                total_balance--;
            }
        }
    }
    /* Sort nodes by their slots balance. */
    qsort(weightedNodes, nodes_involved, sizeof(clusterManagerNode *),
          clusterManagerCompareNodeBalance);
    clusterManagerLogInfo(">>> Rebalancing across %d nodes. "
                          "Total weight = %.2f\n",
                          nodes_involved, total_weight);
    if (config.verbose) {
        for (i = 0; i < nodes_involved; i++) {
            clusterManagerNode *n = weightedNodes[i];
            printf("%s:%d balance is %d slots\n", n->ip, n->port, n->balance);
        }
    }
    /* Now we have at the start of the 'sn' array nodes that should get
     * slots, at the end nodes that must give slots.
     * We take two indexes, one at the start, and one at the end,
     * incrementing or decrementing the indexes accordingly til we
     * find nodes that need to get/provide slots. */
    int dst_idx = 0;
    int src_idx = nodes_involved - 1;
    int simulate = config.cluster_manager_command.flags &
                   CLUSTER_MANAGER_CMD_FLAG_SIMULATE;
    while (dst_idx < src_idx) {
        clusterManagerNode *dst = weightedNodes[dst_idx];
        clusterManagerNode *src = weightedNodes[src_idx];
        int db = abs(dst->balance);
        int sb = abs(src->balance);
        int numslots = (db < sb ? db : sb);
        if (numslots > 0) {
            printf("Moving %d slots from %s:%d to %s:%d\n", numslots,
                                                            src->ip,
                                                            src->port,
                                                            dst->ip,
                                                            dst->port);
            /* Actually move the slots. */
            list *lsrc = listCreate(), *table = NULL;
            listAddNodeTail(lsrc, src);
            table = clusterManagerComputeReshardTable(lsrc, numslots);
            listRelease(lsrc);
            int table_len = (int) listLength(table);
            if (!table || table_len != numslots) {
                clusterManagerLogErr("*** Assertion failed: Reshard table "
                                     "!= number of slots");
                result = 0;
                goto end_move;
            }
            if (simulate) {
                for (i = 0; i < table_len; i++) printf("#");
            } else {
                int opts = CLUSTER_MANAGER_OPT_QUIET |
                           CLUSTER_MANAGER_OPT_UPDATE;
                listRewind(table, &li);
                while ((ln = listNext(&li)) != NULL) {
                    clusterManagerReshardTableItem *item = ln->value;
                    result = clusterManagerMoveSlot(item->source,
                                                    dst,
                                                    item->slot,
                                                    opts, NULL);
                    if (!result) goto end_move;
                    printf("#");
                    fflush(stdout);
                }

            }
            printf("\n");
end_move:
            clusterManagerReleaseReshardTable(table);
            if (!result) goto cleanup;
        }
        /* Update nodes balance. */
        dst->balance += numslots;
        src->balance -= numslots;
        if (dst->balance == 0) dst_idx++;
        if (src->balance == 0) src_idx --;
    }
cleanup:
    if (involved != NULL) listRelease(involved);
    if (weightedNodes != NULL) zfree(weightedNodes);
    return result;
invalid_args:
    fprintf(stderr, CLUSTER_MANAGER_INVALID_HOST_ARG);
    return 0;
}