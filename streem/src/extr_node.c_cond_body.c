#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* body; scalar_t__ block; } ;
typedef  TYPE_1__ node_lambda ;
struct TYPE_6__ {scalar_t__ type; } ;
typedef  TYPE_2__ node ;

/* Variables and functions */
 scalar_t__ NODE_LAMBDA ; 

__attribute__((used)) static node*
cond_body(node* body)
{
  if (body == NULL) return NULL;
  if (body->type == NODE_LAMBDA) {
    node_lambda* lambda = (node_lambda*)body;
    if (lambda->block) {
      return lambda->body;
    }
  }
  return body;
}