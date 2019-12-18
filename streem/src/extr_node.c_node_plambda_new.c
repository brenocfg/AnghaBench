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
struct TYPE_3__ {int /*<<< orphan*/ * body; int /*<<< orphan*/ * cond; int /*<<< orphan*/ * pat; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ node_plambda ;
typedef  int /*<<< orphan*/  node ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_PLAMBDA ; 
 TYPE_1__* malloc (int) ; 

node*
node_plambda_new(node* pat, node* cond)
{
  node_plambda* lambda = malloc(sizeof(node_plambda));
  lambda->type = NODE_PLAMBDA;
  lambda->pat = pat;
  lambda->cond = cond;
  lambda->body = NULL;
  return (node*)lambda;
}