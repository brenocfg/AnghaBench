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
struct TYPE_2__ {scalar_t__ show_owner; } ;
struct query_node {TYPE_1__ pqfr; } ;
typedef  int /*<<< orphan*/  adns_answer ;

/* Variables and functions */
 int /*<<< orphan*/  owner_show (struct query_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_ttl (struct query_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_withspace (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_owner_ttl(struct query_node *qun, adns_answer *answer) {
  if (qun->pqfr.show_owner) print_withspace(owner_show(qun,answer));
  print_ttl(qun,answer);
}