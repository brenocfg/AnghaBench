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
struct strm_queue_node {int /*<<< orphan*/ * next; } ;
struct strm_queue {struct strm_queue_node* head; struct strm_queue_node* tail; } ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 

struct strm_queue*
strm_queue_new()
{
  struct strm_queue* q;

  q = (struct strm_queue*)malloc(sizeof(struct strm_queue));
  if (q == NULL) {
    return NULL;
  }
  q->head = (struct strm_queue_node*)malloc(sizeof(struct strm_queue_node)); /* Sentinel node */
  q->tail = q->head;
  q->head->next = NULL;
  return q;
}