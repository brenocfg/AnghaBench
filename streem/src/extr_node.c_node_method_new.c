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
struct TYPE_3__ {int /*<<< orphan*/ * body; int /*<<< orphan*/ * args; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ node_lambda ;
typedef  int /*<<< orphan*/  node ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_LAMBDA ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  node_args_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * node_args_new () ; 
 int /*<<< orphan*/  node_args_prepend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node_str_new (char*,int) ; 

node*
node_method_new(node* args, node* compstmt)
{
  node_lambda* lambda = malloc(sizeof(node_lambda));
  lambda->type = NODE_LAMBDA;
  if (args) {
    node_args_prepend(args, node_str_new("self", 4));
  }
  else {
    args = node_args_new();
    node_args_add(args, node_str_new("self", 4));
  }
  lambda->args = args;
  lambda->body = compstmt;
  return (node*)lambda;
}