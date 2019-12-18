#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct callout {scalar_t__ queued; TYPE_2__* next; TYPE_1__* prev; } ;
struct TYPE_4__ {TYPE_1__* prev; } ;
struct TYPE_3__ {TYPE_2__* next; } ;

/* Variables and functions */
 TYPE_2__* callout_queue ; 

__attribute__((used)) static void callout_remove(struct callout *c) {
  if (!c->queued) {
    return;
  }

  if (c->prev) {
    c->prev->next = c->next;
  } else {
    callout_queue = c->next;
  }
  
  if (c->next) {
    c->next->prev = c->prev;
  }
  
  c->prev = NULL;
  c->next = NULL;
  c->queued = 0;
}