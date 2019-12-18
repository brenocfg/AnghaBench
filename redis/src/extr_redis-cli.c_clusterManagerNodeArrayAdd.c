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
struct TYPE_3__ {int len; scalar_t__ count; int /*<<< orphan*/ ** nodes; } ;
typedef  TYPE_1__ clusterManagerNodeArray ;
typedef  int /*<<< orphan*/  clusterManagerNode ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void clusterManagerNodeArrayAdd(clusterManagerNodeArray *array,
                                       clusterManagerNode *node)
{
    assert(array->nodes < (array->nodes + array->len));
    assert(node != NULL);
    assert(array->count < array->len);
    array->nodes[array->count++] = node;
}