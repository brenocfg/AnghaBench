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
struct TYPE_2__ {int block_prev; int block_next; scalar_t__ unknown_0008; scalar_t__ free_space; int /*<<< orphan*/  signature; } ;
struct chmcPmglChunk {int /*<<< orphan*/  data; TYPE_1__ header; } ;
struct chmcPmglChunkNode {struct chmcPmglChunk chunk; scalar_t__ index_len; scalar_t__ data_len; } ;

/* Variables and functions */
 scalar_t__ CHMC_PMGL_DATA_LEN ; 
 int /*<<< orphan*/  assert (struct chmcPmglChunkNode*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void chmc_pmgl_init(struct chmcPmglChunkNode *node)
{
	struct chmcPmglChunk *chunk;

	assert(node);

	node->data_len = 0;
	node->index_len = 0;

	chunk = &node->chunk;

	memcpy(chunk->header.signature, "PMGL", 4);

	// FIXME check it is the right len
	chunk->header.free_space = CHMC_PMGL_DATA_LEN + 2;
	chunk->header.unknown_0008 = 0;
	chunk->header.block_prev = -1;
	chunk->header.block_next = -1;

	memset(chunk->data, 0, CHMC_PMGL_DATA_LEN);
}