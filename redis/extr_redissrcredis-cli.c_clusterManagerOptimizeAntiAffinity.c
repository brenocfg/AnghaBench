#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* value; } ;
typedef  TYPE_1__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
typedef  int /*<<< orphan*/  clusterManagerNodeArray ;
struct TYPE_10__ {char* replicate; int dirty; } ;
typedef  TYPE_2__ clusterManagerNode ;
struct TYPE_12__ {TYPE_5__* nodes; } ;
struct TYPE_11__ {int len; } ;

/* Variables and functions */
 int CLUSTER_MANAGER_LOG_LVL_SUCCESS ; 
 int CLUSTER_MANAGER_LOG_LVL_WARN ; 
 int clusterManagerGetAntiAffinityScore (int /*<<< orphan*/ *,int,TYPE_2__***,int*) ; 
 int /*<<< orphan*/  clusterManagerLog (int,char*,char*) ; 
 int /*<<< orphan*/  clusterManagerLogInfo (char*) ; 
 TYPE_7__ cluster_manager ; 
 TYPE_1__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int rand () ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 TYPE_2__** zcalloc (int) ; 
 int /*<<< orphan*/  zfree (TYPE_2__**) ; 

__attribute__((used)) static void clusterManagerOptimizeAntiAffinity(clusterManagerNodeArray *ipnodes,
    int ip_count)
{
    clusterManagerNode **offenders = NULL;
    int score = clusterManagerGetAntiAffinityScore(ipnodes, ip_count,
                                                   NULL, NULL);
    if (score == 0) goto cleanup;
    clusterManagerLogInfo(">>> Trying to optimize slaves allocation "
                          "for anti-affinity\n");
    int node_len = cluster_manager.nodes->len;
    int maxiter = 500 * node_len; // Effort is proportional to cluster size...
    srand(time(NULL));
    while (maxiter > 0) {
        int offending_len = 0;
        if (offenders != NULL) {
            zfree(offenders);
            offenders = NULL;
        }
        score = clusterManagerGetAntiAffinityScore(ipnodes,
                                                   ip_count,
                                                   &offenders,
                                                   &offending_len);
        if (score == 0) break; // Optimal anti affinity reached
        /* We'll try to randomly swap a slave's assigned master causing
         * an affinity problem with another random slave, to see if we
         * can improve the affinity. */
        int rand_idx = rand() % offending_len;
        clusterManagerNode *first = offenders[rand_idx],
                           *second = NULL;
        clusterManagerNode **other_replicas = zcalloc((node_len - 1) *
                                                      sizeof(*other_replicas));
        int other_replicas_count = 0;
        listIter li;
        listNode *ln;
        listRewind(cluster_manager.nodes, &li);
        while ((ln = listNext(&li)) != NULL) {
            clusterManagerNode *n = ln->value;
            if (n != first && n->replicate != NULL)
                other_replicas[other_replicas_count++] = n;
        }
        if (other_replicas_count == 0) {
            zfree(other_replicas);
            break;
        }
        rand_idx = rand() % other_replicas_count;
        second = other_replicas[rand_idx];
        char *first_master = first->replicate,
             *second_master = second->replicate;
        first->replicate = second_master, first->dirty = 1;
        second->replicate = first_master, second->dirty = 1;
        int new_score = clusterManagerGetAntiAffinityScore(ipnodes,
                                                           ip_count,
                                                           NULL, NULL);
        /* If the change actually makes thing worse, revert. Otherwise
         * leave as it is because the best solution may need a few
         * combined swaps. */
        if (new_score > score) {
            first->replicate = first_master;
            second->replicate = second_master;
        }
        zfree(other_replicas);
        maxiter--;
    }
    score = clusterManagerGetAntiAffinityScore(ipnodes, ip_count, NULL, NULL);
    char *msg;
    int perfect = (score == 0);
    int log_level = (perfect ? CLUSTER_MANAGER_LOG_LVL_SUCCESS :
                               CLUSTER_MANAGER_LOG_LVL_WARN);
    if (perfect) msg = "[OK] Perfect anti-affinity obtained!";
    else if (score >= 10000)
        msg = ("[WARNING] Some slaves are in the same host as their master");
    else
        msg=("[WARNING] Some slaves of the same master are in the same host");
    clusterManagerLog(log_level, "%s\n", msg);
cleanup:
    zfree(offenders);
}