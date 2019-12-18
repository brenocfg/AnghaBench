#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  char* sds ;
struct TYPE_10__ {TYPE_3__* value; } ;
typedef  TYPE_1__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
typedef  int /*<<< orphan*/  dict ;
struct TYPE_11__ {int len; TYPE_3__** nodes; } ;
typedef  TYPE_2__ clusterManagerNodeArray ;
struct TYPE_12__ {char* ip; char* replicate; char* name; } ;
typedef  TYPE_3__ clusterManagerNode ;
struct TYPE_14__ {TYPE_5__* nodes; } ;
struct TYPE_13__ {int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterManagerDictType ; 
 TYPE_7__ cluster_manager ; 
 int /*<<< orphan*/ * dictCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictFind (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ *) ; 
 scalar_t__ dictGetKey (int /*<<< orphan*/ *) ; 
 scalar_t__ dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReplace (int /*<<< orphan*/ *,char*,char*) ; 
 TYPE_1__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (TYPE_5__*,int /*<<< orphan*/ *) ; 
 char* sdscat (char*,char*) ; 
 char* sdscatprintf (char*,char*,char*) ; 
 char* sdsdup (char*) ; 
 char* sdsempty () ; 
 int sdslen (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 TYPE_3__** zcalloc (int) ; 

__attribute__((used)) static int clusterManagerGetAntiAffinityScore(clusterManagerNodeArray *ipnodes,
    int ip_count, clusterManagerNode ***offending, int *offending_len)
{
    int score = 0, i, j;
    int node_len = cluster_manager.nodes->len;
    clusterManagerNode **offending_p = NULL;
    if (offending != NULL) {
        *offending = zcalloc(node_len * sizeof(clusterManagerNode*));
        offending_p = *offending;
    }
    /* For each set of nodes in the same host, split by
     * related nodes (masters and slaves which are involved in
     * replication of each other) */
    for (i = 0; i < ip_count; i++) {
        clusterManagerNodeArray *node_array = &(ipnodes[i]);
        dict *related = dictCreate(&clusterManagerDictType, NULL);
        char *ip = NULL;
        for (j = 0; j < node_array->len; j++) {
            clusterManagerNode *node = node_array->nodes[j];
            if (node == NULL) continue;
            if (!ip) ip = node->ip;
            sds types;
            /* We always use the Master ID as key. */
            sds key = (!node->replicate ? node->name : node->replicate);
            assert(key != NULL);
            dictEntry *entry = dictFind(related, key);
            if (entry) types = sdsdup((sds) dictGetVal(entry));
            else types = sdsempty();
            /* Master type 'm' is always set as the first character of the
             * types string. */
            if (!node->replicate) types = sdscatprintf(types, "m%s", types);
            else types = sdscat(types, "s");
            dictReplace(related, key, types);
        }
        /* Now it's trivial to check, for each related group having the
         * same host, what is their local score. */
        dictIterator *iter = dictGetIterator(related);
        dictEntry *entry;
        while ((entry = dictNext(iter)) != NULL) {
            sds types = (sds) dictGetVal(entry);
            sds name = (sds) dictGetKey(entry);
            int typeslen = sdslen(types);
            if (typeslen < 2) continue;
            if (types[0] == 'm') score += (10000 * (typeslen - 1));
            else score += (1 * typeslen);
            if (offending == NULL) continue;
            /* Populate the list of offending nodes. */
            listIter li;
            listNode *ln;
            listRewind(cluster_manager.nodes, &li);
            while ((ln = listNext(&li)) != NULL) {
                clusterManagerNode *n = ln->value;
                if (n->replicate == NULL) continue;
                if (!strcmp(n->replicate, name) && !strcmp(n->ip, ip)) {
                    *(offending_p++) = n;
                    if (offending_len != NULL) (*offending_len)++;
                    break;
                }
            }
        }
        //if (offending_len != NULL) *offending_len = offending_p - *offending;
        dictReleaseIterator(iter);
        dictRelease(related);
    }
    return score;
}