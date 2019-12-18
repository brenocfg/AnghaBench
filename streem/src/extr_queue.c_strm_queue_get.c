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
struct strm_queue_node {scalar_t__ n; struct strm_queue_node* next; } ;
struct strm_queue {struct strm_queue_node* head; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct strm_queue_node*) ; 
 scalar_t__ strm_atomic_cas (struct strm_queue_node*,struct strm_queue_node*,struct strm_queue_node*) ; 

void*
strm_queue_get(struct strm_queue* q)
{
  while (1) {
    struct strm_queue_node *n = q->head;
    struct strm_queue_node *next = n->next;
    if (n != q->head) continue;
    if (next == NULL) {
      return NULL;
    }
    if (strm_atomic_cas(q->head, n, next)) {
      void *val = (void*)next->n;
      free(n);                  /* may cause ABA problem; use GC */
      return val;
    }
  }
}