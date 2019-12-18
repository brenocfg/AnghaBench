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
struct TYPE_2__ {int balance; } ;
typedef  TYPE_1__ clusterManagerNode ;

/* Variables and functions */

int clusterManagerCompareNodeBalance(const void *n1, const void *n2) {
    clusterManagerNode *node1 = *((clusterManagerNode **) n1);
    clusterManagerNode *node2 = *((clusterManagerNode **) n2);
    return node1->balance - node2->balance;
}