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
struct callout {int queued; struct callout* next; struct callout* prev; } ;

/* Variables and functions */
 scalar_t__ callout_cmp (struct callout*,struct callout*) ; 
 struct callout* callout_queue ; 

__attribute__((used)) static void callout_insert(struct callout *c) {
  struct callout *node = callout_queue;

  if (!node) {
    callout_queue = c;
    c->prev = NULL;
    c->next = NULL;
    c->queued = 1;
    return;
  }
  
  if (callout_cmp(c, node)) {
    node->prev = c;
    c->prev = NULL;
    c->next = node;
    callout_queue = c;
    c->queued = 1;
    return;
  }
  
  while (node->next) {
    if (callout_cmp(c, node->next)) {
      c->prev = node;
      c->next = node->next;
      node->next->prev = c;
      node->next = c;
      c->queued = 1;
      return;
    }
    node = node->next;
  }
  
  c->prev = node;
  c->next = NULL;
  node->next = c;
  c->queued = 1;
}