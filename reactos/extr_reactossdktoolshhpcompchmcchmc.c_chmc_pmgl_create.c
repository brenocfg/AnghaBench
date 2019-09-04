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
struct chmcPmglChunkNode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  chmc_pmgl_init (struct chmcPmglChunkNode*) ; 
 struct chmcPmglChunkNode* malloc (int) ; 

struct chmcPmglChunkNode *chmc_pmgl_create(void)
{
	struct chmcPmglChunkNode *node;

	node = malloc(sizeof(struct chmcPmglChunkNode));
	if (node)
		chmc_pmgl_init(node);

	return node;
}