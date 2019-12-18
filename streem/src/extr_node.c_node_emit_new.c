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
struct TYPE_3__ {int /*<<< orphan*/ * emit; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ node_emit ;
typedef  int /*<<< orphan*/  node ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_EMIT ; 
 TYPE_1__* malloc (int) ; 

node*
node_emit_new(node* value)
{
  node_emit* ne = malloc(sizeof(node_emit));
  ne->type = NODE_EMIT;
  ne->emit = value;
  return (node*)ne;
}