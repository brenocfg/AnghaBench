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
struct chmcTreeNode {int dummy; } ;
struct chmcFile {int entries_num; struct chmcTreeNode** sort_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct chmcFile*) ; 
 int /*<<< orphan*/  chmc_pmgl_add_entry (struct chmcFile*,struct chmcTreeNode*) ; 

void chmc_pmgl_done(struct chmcFile *chm)
{
	struct chmcTreeNode *entry;
	int i;

	assert(chm);

	for(i=0; i < chm->entries_num; i++) {
		entry = chm->sort_entries[i];
		chmc_pmgl_add_entry(chm, entry);
	}
}