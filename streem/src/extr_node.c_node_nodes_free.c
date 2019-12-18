#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t strm_int ;
struct TYPE_5__ {size_t len; struct TYPE_5__* data; } ;
typedef  TYPE_1__ node_nodes ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  node_free (TYPE_1__) ; 

void
node_nodes_free(node_nodes* v)
{
  strm_int i;

  for (i = 0; i < v->len; i++)
    node_free(v->data[i]);
  free(v->data);
  free(v);
}