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
typedef  int /*<<< orphan*/  node_string ;
struct TYPE_3__ {int /*<<< orphan*/ * args; int /*<<< orphan*/  ident; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ node_call ;
typedef  int /*<<< orphan*/  node ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_CALL ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/ * node_array_new () ; 
 int /*<<< orphan*/  node_nodes_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node_nodes_prepend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

node*
node_call_new(node_string ident, node* recv, node* args, node* blk)
{
  node_call* ncall = malloc(sizeof(node_call));
  ncall->type = NODE_CALL;
  ncall->ident = ident;
  if (!args) args = node_array_new();
  if (recv) {
    node_nodes_prepend(args, recv);
  }
  if (blk) {
    node_nodes_add(args, blk);
  }
  ncall->args = args;
  return (node*)ncall;
}