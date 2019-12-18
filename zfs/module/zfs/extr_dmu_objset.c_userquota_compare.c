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
struct TYPE_2__ {int /*<<< orphan*/  uqn_id; } ;
typedef  TYPE_1__ userquota_node_t ;

/* Variables and functions */
 int TREE_ISIGN (int) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
userquota_compare(const void *l, const void *r)
{
	const userquota_node_t *luqn = l;
	const userquota_node_t *ruqn = r;
	int rv;

	/*
	 * NB: can only access uqn_id because userquota_update_cache() doesn't
	 * pass in an entire userquota_node_t.
	 */
	rv = strcmp(luqn->uqn_id, ruqn->uqn_id);

	return (TREE_ISIGN(rv));
}