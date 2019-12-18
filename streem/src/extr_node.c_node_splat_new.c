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
struct TYPE_3__ {int /*<<< orphan*/ * node; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ node_splat ;
typedef  int /*<<< orphan*/  node ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_SPLAT ; 
 TYPE_1__* malloc (int) ; 

node*
node_splat_new(node* n)
{
  node_splat* splat = malloc(sizeof(node_splat));
  splat->type = NODE_SPLAT;
  splat->node = n;
  return (node*)splat;
}