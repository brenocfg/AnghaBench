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
struct query_node {int /*<<< orphan*/  qu; struct query_node* next; int /*<<< orphan*/  id; } ;
struct optioninfo {int dummy; } ;
struct TYPE_2__ {struct query_node* head; } ;

/* Variables and functions */
 int /*<<< orphan*/  adns_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dequeue_query (struct query_node*) ; 
 TYPE_1__ outstanding ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

void of_cancel_id(const struct optioninfo *oi, const char *arg, const char *arg2) {
  struct query_node *qun;

  for (qun= outstanding.head;
       qun && strcmp(qun->id,arg);
       qun= qun->next);
  if (!qun) return;
  adns_cancel(qun->qu);
  dequeue_query(qun);
}