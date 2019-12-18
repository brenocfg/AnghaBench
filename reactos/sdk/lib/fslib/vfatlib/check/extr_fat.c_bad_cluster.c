#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {int /*<<< orphan*/  fat; } ;
struct TYPE_7__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ FAT_ENTRY ;
typedef  TYPE_2__ DOS_FS ;

/* Variables and functions */
 int FAT_IS_BAD (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_fat (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

int bad_cluster(DOS_FS * fs, uint32_t cluster)
{
    FAT_ENTRY curEntry;
    get_fat(&curEntry, fs->fat, cluster, fs);

    return FAT_IS_BAD(fs, curEntry.value);
}