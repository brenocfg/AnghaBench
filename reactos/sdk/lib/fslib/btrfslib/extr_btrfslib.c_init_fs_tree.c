#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  btrfs_root ;
struct TYPE_10__ {int /*<<< orphan*/  dwHighDateTime; int /*<<< orphan*/  dwLowDateTime; } ;
struct TYPE_9__ {int generation; int st_nlink; int st_mode; int /*<<< orphan*/  st_atime; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_ctime; int /*<<< orphan*/  st_blocks; } ;
struct TYPE_8__ {int /*<<< orphan*/  HighPart; int /*<<< orphan*/  LowPart; } ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  TYPE_2__ INODE_ITEM ;
typedef  TYPE_3__ FILETIME ;

/* Variables and functions */
 int /*<<< orphan*/  GetSystemTimeAsFileTime (TYPE_3__*) ; 
 int /*<<< orphan*/  SUBVOL_ROOT_INODE ; 
 int /*<<< orphan*/  TYPE_INODE_ITEM ; 
 int /*<<< orphan*/  add_inode_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_item (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  win_time_to_unix (TYPE_1__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_fs_tree(btrfs_root* r, uint32_t node_size) {
    INODE_ITEM ii;
    FILETIME filetime;
    LARGE_INTEGER time;

    memset(&ii, 0, sizeof(INODE_ITEM));

    ii.generation = 1;
    ii.st_blocks = node_size;
    ii.st_nlink = 1;
    ii.st_mode = 040755;

    GetSystemTimeAsFileTime(&filetime);
    time.LowPart = filetime.dwLowDateTime;
    time.HighPart = filetime.dwHighDateTime;

    win_time_to_unix(time, &ii.st_atime);
    ii.st_ctime = ii.st_mtime = ii.st_atime;

    add_item(r, SUBVOL_ROOT_INODE, TYPE_INODE_ITEM, 0, &ii, sizeof(INODE_ITEM));

    add_inode_ref(r, SUBVOL_ROOT_INODE, SUBVOL_ROOT_INODE, 0, "..");
}