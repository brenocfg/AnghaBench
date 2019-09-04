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
struct _diskfree_t {unsigned int avail_clusters; int /*<<< orphan*/  total_clusters; int /*<<< orphan*/  bytes_per_sector; int /*<<< orphan*/  sectors_per_cluster; } ;
typedef  int /*<<< orphan*/  LPDWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetDiskFreeSpaceA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char toupper (unsigned int) ; 

unsigned int _getdiskfree(unsigned int _drive, struct _diskfree_t* _diskspace)
{
    char RootPathName[10];

    RootPathName[0] = toupper(_drive +'@');
    RootPathName[1] = ':';
    RootPathName[2] = '\\';
    RootPathName[3] = 0;
    if (_diskspace == NULL)
        return 0;
    if (!GetDiskFreeSpaceA(RootPathName,(LPDWORD)&_diskspace->sectors_per_cluster,(LPDWORD)&_diskspace->bytes_per_sector,
            (LPDWORD )&_diskspace->avail_clusters,(LPDWORD )&_diskspace->total_clusters))
        return 0;
    return _diskspace->avail_clusters;
}