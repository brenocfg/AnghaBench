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
struct chmcPmgiChunkNode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  chmc_pmgi_init (struct chmcPmgiChunkNode*) ; 
 struct chmcPmgiChunkNode* malloc (int) ; 

struct chmcPmgiChunkNode *chmc_pmgi_create(void)
{
	struct chmcPmgiChunkNode *node;

	node = malloc(sizeof(struct chmcPmgiChunkNode));
	if (node)
		chmc_pmgi_init(node);

	return node;
}