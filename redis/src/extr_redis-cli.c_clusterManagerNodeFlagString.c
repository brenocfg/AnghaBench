#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sds ;
struct TYPE_5__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_6__ {int /*<<< orphan*/  flags_str; } ;
typedef  TYPE_2__ clusterManagerNode ;

/* Variables and functions */
 TYPE_1__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdscat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sdscatfmt (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsempty () ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static sds clusterManagerNodeFlagString(clusterManagerNode *node) {
    sds flags = sdsempty();
    if (!node->flags_str) return flags;
    int empty = 1;
    listIter li;
    listNode *ln;
    listRewind(node->flags_str, &li);
    while ((ln = listNext(&li)) != NULL) {
        sds flag = ln->value;
        if (strcmp(flag, "myself") == 0) continue;
        if (!empty) flags = sdscat(flags, ",");
        flags = sdscatfmt(flags, "%S", flag);
        empty = 0;
    }
    return flags;
}