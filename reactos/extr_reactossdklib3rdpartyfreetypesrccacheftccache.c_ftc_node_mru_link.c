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
struct TYPE_3__ {int /*<<< orphan*/  num_nodes; int /*<<< orphan*/  nodes_list; } ;
typedef  scalar_t__ FTC_Node ;
typedef  int /*<<< orphan*/  FTC_MruNode ;
typedef  TYPE_1__* FTC_Manager ;

/* Variables and functions */
 int /*<<< orphan*/  FTC_MruNode_Prepend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  ftc_node_mru_link( FTC_Node     node,
                     FTC_Manager  manager )
  {
    void  *nl = &manager->nodes_list;


    FTC_MruNode_Prepend( (FTC_MruNode*)nl,
                         (FTC_MruNode)node );
    manager->num_nodes++;
  }