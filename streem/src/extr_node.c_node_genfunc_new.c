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
struct TYPE_3__ {int /*<<< orphan*/  id; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ node_genfunc ;
typedef  int /*<<< orphan*/  node ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_GENFUNC ; 
 TYPE_1__* malloc (int) ; 

node*
node_genfunc_new(node_string id)
{
  node_genfunc* ngf = malloc(sizeof(node_genfunc));
  ngf->type = NODE_GENFUNC;
  ngf->id = id;
  return (node*)ngf;
}