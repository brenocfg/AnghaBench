#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_10__ {int data_clusters; unsigned long long cluster_size; int /*<<< orphan*/  fat; } ;
struct TYPE_9__ {scalar_t__ value; } ;
typedef  TYPE_1__ FAT_ENTRY ;
typedef  TYPE_2__ DOS_FS ;

/* Variables and functions */
 int /*<<< orphan*/  FAT_IS_BAD (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  get_fat (TYPE_1__*,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  get_owner (TYPE_2__*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  set_fat (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ verbose ; 

void reclaim_free(DOS_FS * fs)
{
    int reclaimed;
    uint32_t i;

    if (verbose)
	printf("Checking for unused clusters.\n");
    reclaimed = 0;
    for (i = 2; i < fs->data_clusters + 2; i++) {
	FAT_ENTRY curEntry;
	get_fat(&curEntry, fs->fat, i, fs);

	if (!get_owner(fs, i) && curEntry.value &&
#ifndef __REACTOS__
	    !FAT_IS_BAD(fs, curEntry.value)) {
#else
	    !FAT_IS_BAD(fs, curEntry.value) && rw) {
#endif
	    set_fat(fs, i, 0);
	    reclaimed++;
	}
    }
    if (reclaimed)
	printf("Reclaimed %d unused cluster%s (%llu bytes).\n", (int)reclaimed,
	       reclaimed == 1 ? "" : "s",
	       (unsigned long long)reclaimed * fs->cluster_size);
}