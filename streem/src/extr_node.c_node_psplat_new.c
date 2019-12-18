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
struct TYPE_3__ {int /*<<< orphan*/ * tail; int /*<<< orphan*/ * mid; int /*<<< orphan*/ * head; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ node_psplat ;
typedef  int /*<<< orphan*/  node ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_PSPLAT ; 
 TYPE_1__* malloc (int) ; 

node*
node_psplat_new(node* head, node* mid, node* tail)
{
  node_psplat* cons = malloc(sizeof(node_psplat));
  cons->type = NODE_PSPLAT;
  cons->head = head;
  cons->mid = mid;
  cons->tail = tail;
  return (node*)cons;
}