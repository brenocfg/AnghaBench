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
struct TYPE_3__ {int /*<<< orphan*/ * rhs; int /*<<< orphan*/  lhs; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ node_let ;
typedef  int /*<<< orphan*/  node ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_LET ; 
 TYPE_1__* malloc (int) ; 

node*
node_let_new(node_string lhs, node* rhs)
{
  node_let* nlet = malloc(sizeof(node_let));
  nlet->type = NODE_LET;
  nlet->lhs = lhs;
  nlet->rhs = rhs;
  return (node*)nlet;
}