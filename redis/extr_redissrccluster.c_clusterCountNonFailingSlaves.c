#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int numslaves; int /*<<< orphan*/ * slaves; } ;
typedef  TYPE_1__ clusterNode ;

/* Variables and functions */
 int /*<<< orphan*/  nodeFailed (int /*<<< orphan*/ ) ; 

int clusterCountNonFailingSlaves(clusterNode *n) {
    int j, okslaves = 0;

    for (j = 0; j < n->numslaves; j++)
        if (!nodeFailed(n->slaves[j])) okslaves++;
    return okslaves;
}