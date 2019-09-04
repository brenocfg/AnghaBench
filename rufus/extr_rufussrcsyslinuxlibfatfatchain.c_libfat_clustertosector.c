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
struct libfat_filesystem {int rootcluster; int rootdir; int endcluster; int data; int clustshift; } ;
typedef  int libfat_sector_t ;
typedef  int int32_t ;

/* Variables and functions */

libfat_sector_t libfat_clustertosector(const struct libfat_filesystem *fs,
				       int32_t cluster)
{
    if (cluster == 0)
	cluster = fs->rootcluster;

    if (cluster == 0)
	return fs->rootdir;
    else if (cluster < 2 || cluster >= fs->endcluster)
	return -1;
    else
	return fs->data + ((libfat_sector_t) (cluster - 2) << fs->clustshift);
}