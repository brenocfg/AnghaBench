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
struct query_node {struct query_node* owner; struct query_node* id; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_UNLINK (int /*<<< orphan*/ ,struct query_node*) ; 
 int /*<<< orphan*/  free (struct query_node*) ; 
 int /*<<< orphan*/  outstanding ; 

__attribute__((used)) static void dequeue_query(struct query_node *qun) {
  LIST_UNLINK(outstanding,qun);
  free(qun->id);
  free(qun->owner);
  free(qun);
}