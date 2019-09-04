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
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sds ;
struct TYPE_6__ {TYPE_2__* value; } ;
typedef  TYPE_1__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_7__ {scalar_t__ name; } ;
typedef  TYPE_2__ clusterManagerNode ;
struct TYPE_8__ {int /*<<< orphan*/ * nodes; } ;

/* Variables and functions */
 TYPE_4__ cluster_manager ; 
 TYPE_1__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdscmp (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdscpy (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdstolower (int /*<<< orphan*/ ) ; 

__attribute__((used)) static clusterManagerNode *clusterManagerNodeByName(const char *name) {
    if (cluster_manager.nodes == NULL) return NULL;
    clusterManagerNode *found = NULL;
    sds lcname = sdsempty();
    lcname = sdscpy(lcname, name);
    sdstolower(lcname);
    listIter li;
    listNode *ln;
    listRewind(cluster_manager.nodes, &li);
    while ((ln = listNext(&li)) != NULL) {
        clusterManagerNode *n = ln->value;
        if (n->name && !sdscmp(n->name, lcname)) {
            found = n;
            break;
        }
    }
    sdsfree(lcname);
    return found;
}