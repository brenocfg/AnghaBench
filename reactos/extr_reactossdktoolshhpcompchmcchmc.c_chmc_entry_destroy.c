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
struct chmcTreeNode {int flags; struct chmcTreeNode* buf; struct chmcTreeNode* name; } ;

/* Variables and functions */
 int CHMC_TNFL_STATIC ; 
 int /*<<< orphan*/  assert (struct chmcTreeNode*) ; 
 int /*<<< orphan*/  free (struct chmcTreeNode*) ; 

void chmc_entry_destroy( struct chmcTreeNode *node )
{
	assert(node);
	assert(node->name);

	free(node->name);
	if (node->buf && !(node->flags & CHMC_TNFL_STATIC))
		free(node->buf);
	free(node);
}