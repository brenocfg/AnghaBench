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
struct chmcPmglHeader {scalar_t__ block_next; scalar_t__ block_prev; } ;
struct TYPE_2__ {struct chmcPmglHeader header; } ;
struct chmcItspHeader {scalar_t__ num_blocks; scalar_t__ index_last; } ;
struct chmcPmglChunkNode {struct chmcPmglChunkNode* pmgl_last; TYPE_1__ chunk; int /*<<< orphan*/  pmgl_list; int /*<<< orphan*/  list; struct chmcItspHeader itsp; } ;
struct chmcFile {struct chmcFile* pmgl_last; TYPE_1__ chunk; int /*<<< orphan*/  pmgl_list; int /*<<< orphan*/  list; struct chmcItspHeader itsp; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct chmcPmglChunkNode*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void chmc_pmgl_add(struct chmcFile *chm, struct chmcPmglChunkNode *pmgl)
{
	struct chmcItspHeader *itsp = &chm->itsp;
	struct chmcPmglHeader *hdr;

	assert(chm);
	assert(pmgl);

	list_add_tail(&pmgl->list, &chm->pmgl_list);

	itsp->index_last = itsp->num_blocks;

	hdr = &pmgl->chunk.header;
	hdr->block_prev = itsp->num_blocks - 1;

	if (chm->pmgl_last) {
		hdr = &chm->pmgl_last->chunk.header;
		hdr->block_next = itsp->num_blocks;
	}

	itsp->num_blocks++;

	chm->pmgl_last = pmgl;
}