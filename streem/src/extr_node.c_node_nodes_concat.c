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
struct TYPE_2__ {int len; int max; int data; } ;
typedef  TYPE_1__ node_nodes ;
typedef  int /*<<< orphan*/  node ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int,int,int) ; 
 int realloc (int,int) ; 

node*
node_nodes_concat(node* s, node* s2)
{
  if (!s) return s2;
  if (s2) {
    node_nodes* v = (node_nodes*)s;
    node_nodes* v2 = (node_nodes*)s2;

    if (v->len + v2->len > v->max) {
      v->max = v->len + v2->len + 10;
      v->data = realloc(v->data, sizeof(void*) * v->max);
    }
    memcpy(v->data+v->len, v2->data, v2->len*sizeof(node*));
    v->len += v2->len;
  }
  return s;
}