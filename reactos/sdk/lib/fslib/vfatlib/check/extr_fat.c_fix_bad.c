#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_11__ {int data_clusters; int /*<<< orphan*/  cluster_size; int /*<<< orphan*/  fat; } ;
struct TYPE_10__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ FAT_ENTRY ;
typedef  TYPE_2__ DOS_FS ;

/* Variables and functions */
 int /*<<< orphan*/  FAT_IS_BAD (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cluster_start (TYPE_2__*,int) ; 
 int /*<<< orphan*/  fs_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_fat (TYPE_1__*,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  get_owner (TYPE_2__*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  set_fat (TYPE_2__*,int,int) ; 
 scalar_t__ verbose ; 

void fix_bad(DOS_FS * fs)
{
    uint32_t i;

    if (verbose)
	printf("Checking for bad clusters.\n");
    for (i = 2; i < fs->data_clusters + 2; i++) {
	FAT_ENTRY curEntry;
	get_fat(&curEntry, fs->fat, i, fs);

	if (!get_owner(fs, i) && !FAT_IS_BAD(fs, curEntry.value))
	    if (!fs_test(cluster_start(fs, i), fs->cluster_size)) {
		printf("Cluster %lu is unreadable.\n", (unsigned long)i);
		set_fat(fs, i, -2);
	    }
    }
}