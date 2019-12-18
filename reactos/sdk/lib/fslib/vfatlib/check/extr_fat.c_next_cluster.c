#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/  fat; } ;
struct TYPE_8__ {int value; } ;
typedef  TYPE_1__ FAT_ENTRY ;
typedef  TYPE_2__ DOS_FS ;

/* Variables and functions */
 scalar_t__ FAT_IS_BAD (TYPE_2__*,int) ; 
 scalar_t__ FAT_IS_EOF (TYPE_2__*,int) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  get_fat (TYPE_1__*,int /*<<< orphan*/ ,int,TYPE_2__*) ; 

uint32_t next_cluster(DOS_FS * fs, uint32_t cluster)
{
    uint32_t value;
    FAT_ENTRY curEntry;

    get_fat(&curEntry, fs->fat, cluster, fs);

    value = curEntry.value;
    if (FAT_IS_BAD(fs, value))
	die("Internal error: next_cluster on bad cluster");
    return FAT_IS_EOF(fs, value) ? -1 : value;
}