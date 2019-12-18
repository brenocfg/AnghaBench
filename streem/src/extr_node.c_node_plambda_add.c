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
struct TYPE_2__ {int /*<<< orphan*/ * next; } ;
typedef  TYPE_1__ node_plambda ;
typedef  int /*<<< orphan*/  node ;

/* Variables and functions */

node*
node_plambda_add(node* n, node* lambda)
{
  node_plambda* l = (node_plambda*)n;
  while (l->next) {
    l = (node_plambda*)l->next;
  }
  l->next = lambda;
  return n;
}