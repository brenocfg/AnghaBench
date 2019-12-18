#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  node_string ;
struct TYPE_4__ {scalar_t__ type; scalar_t__ value; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ node_pair ;
struct TYPE_5__ {int len; int /*<<< orphan*/ * headers; scalar_t__* data; } ;
typedef  TYPE_2__ node_array ;
typedef  int /*<<< orphan*/  node ;

/* Variables and functions */
 scalar_t__ NODE_PAIR ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/ * node_array_new () ; 

node*
node_array_headers(node* np)
{
  int i;
  node_array* v;
  node_string* headers = NULL;

  if (!np)
    np = node_array_new();
  v = (node_array*)np;
  for (i = 0; i < v->len; i++) {
    node_pair* npair = (node_pair*)v->data[i];
    if (npair && npair->type == NODE_PAIR) {
      if (!headers) {
        headers = malloc(sizeof(node_string)*v->len);
      }
      headers[i] = npair->key;
      v->data[i] = npair->value;
      free(npair);
    }
  }
  v->headers = headers;

  return np;
}