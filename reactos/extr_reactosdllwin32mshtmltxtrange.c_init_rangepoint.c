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
struct TYPE_3__ {int /*<<< orphan*/  off; int /*<<< orphan*/ * node; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ rangepoint_t ;
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  int /*<<< orphan*/  UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  get_node_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMNode_AddRef (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_rangepoint(rangepoint_t *rangepoint, nsIDOMNode *node, UINT32 off)
{
    nsIDOMNode_AddRef(node);

    rangepoint->type = get_node_type(node);
    rangepoint->node = node;
    rangepoint->off = off;
}