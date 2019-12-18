#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct strm_queue_node {struct strm_queue_node* next; struct strm_queue_node* head; } ;
struct strm_queue {struct strm_queue* next; struct strm_queue* head; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct strm_queue_node*) ; 

void
strm_queue_free(struct strm_queue* q)
{
  struct strm_queue_node* n = q->head;

  free(q);
  while (n) {
    struct strm_queue_node* tmp = n->next;
    free(n);
    n = tmp;
  }
}