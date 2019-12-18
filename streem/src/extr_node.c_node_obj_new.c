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
typedef  int /*<<< orphan*/  node_string ;
struct TYPE_2__ {int /*<<< orphan*/  ns; } ;
typedef  TYPE_1__ node_array ;
typedef  int /*<<< orphan*/  node ;

/* Variables and functions */
 scalar_t__ node_array_new () ; 

node*
node_obj_new(node* np, node_string ns)
{
  node_array* v;

  if (!np) v = (node_array*)node_array_new();
  else v = (node_array*)np;
  v->ns = ns;
  return (node*)v;
}