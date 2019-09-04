#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_12__ {int data_clusters; int /*<<< orphan*/  fat; } ;
struct TYPE_11__ {scalar_t__ value; } ;
typedef  TYPE_1__ FAT_ENTRY ;
typedef  TYPE_2__ DOS_FS ;
typedef  int /*<<< orphan*/  DOS_FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FAT_IS_BAD (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  get_fat (TYPE_1__*,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  get_owner (TYPE_2__*,int) ; 
 int next_cluster (TYPE_2__*,int) ; 
 int /*<<< orphan*/  set_fat (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  set_owner (TYPE_2__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tag_free(DOS_FS * fs, DOS_FILE * owner, uint32_t *num_refs,
		     uint32_t start_cluster)
{
    int prev;
    uint32_t i, walk;

    if (start_cluster == 0)
	start_cluster = 2;

    for (i = start_cluster; i < fs->data_clusters + 2; i++) {
	FAT_ENTRY curEntry;
	get_fat(&curEntry, fs->fat, i, fs);

	/* If the current entry is the head of an un-owned chain... */
	if (curEntry.value && !FAT_IS_BAD(fs, curEntry.value) &&
	    !get_owner(fs, i) && !num_refs[i]) {
	    prev = 0;
	    /* Walk the chain, claiming ownership as we go */
	    for (walk = i; walk != -1; walk = next_cluster(fs, walk)) {
		if (!get_owner(fs, walk)) {
		    set_owner(fs, walk, owner);
		} else {
		    /* We've run into cross-links between orphaned chains,
		     * or a cycle with a tail.
		     * Terminate this orphan chain (break the link)
		     */
		    set_fat(fs, prev, -1);

		    /* This is not necessary because 'walk' is owned and thus
		     * will never become the head of a chain (the only case
		     * that would matter during reclaim to files).
		     * It's easier to decrement than to prove that it's
		     * unnecessary.
		     */
		    num_refs[walk]--;
		    break;
		}
		prev = walk;
	    }
	}
    }
}