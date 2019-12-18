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
struct TYPE_3__ {int len; scalar_t__ count; int /*<<< orphan*/  nodes; int /*<<< orphan*/  alloc; } ;
typedef  TYPE_1__ clusterManagerNodeArray ;
typedef  int /*<<< orphan*/  clusterManagerNode ;

/* Variables and functions */
 int /*<<< orphan*/  zcalloc (int) ; 

__attribute__((used)) static void clusterManagerNodeArrayInit(clusterManagerNodeArray *array,
                                        int alloc_len)
{
    array->nodes = zcalloc(alloc_len * sizeof(clusterManagerNode*));
    array->alloc = array->nodes;
    array->len = alloc_len;
    array->count = 0;
}