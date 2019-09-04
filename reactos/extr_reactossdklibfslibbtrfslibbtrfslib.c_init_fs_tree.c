#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  btrfs_root ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_13__ {int /*<<< orphan*/  dwHighDateTime; int /*<<< orphan*/  dwLowDateTime; } ;
struct TYPE_12__ {int generation; int st_nlink; int st_mode; int n; char* name; scalar_t__ index; int /*<<< orphan*/  st_atime; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_ctime; int /*<<< orphan*/  st_blocks; } ;
struct TYPE_11__ {int /*<<< orphan*/  HighPart; int /*<<< orphan*/  LowPart; } ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  TYPE_2__ INODE_REF ;
typedef  TYPE_2__ INODE_ITEM ;
typedef  TYPE_4__ FILETIME ;

/* Variables and functions */
 int /*<<< orphan*/  GetSystemTimeAsFileTime (TYPE_4__*) ; 
 int /*<<< orphan*/  SUBVOL_ROOT_INODE ; 
 int /*<<< orphan*/  TYPE_INODE_ITEM ; 
 int /*<<< orphan*/  TYPE_INODE_REF ; 
 int /*<<< orphan*/  add_item (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  win_time_to_unix (TYPE_1__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_fs_tree(btrfs_root* r, UINT32 node_size) {
    INODE_ITEM ii;
    INODE_REF* ir;
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

#ifndef __REACTOS__
    ir = malloc(sizeof(INODE_REF) - 1 + 2);
#else
    ir = RtlAllocateHeap(RtlGetProcessHeap(), 0, sizeof(INODE_REF) - 1 + 2);
#endif

    ir->index = 0;
    ir->n = 2;
    ir->name[0] = '.';
    ir->name[1] = '.';

    add_item(r, SUBVOL_ROOT_INODE, TYPE_INODE_REF, SUBVOL_ROOT_INODE, ir, sizeof(INODE_REF) - 1 + ir->n);

#ifndef __REACTOS__
    free(ir);
#else
    RtlFreeHeap(RtlGetProcessHeap(), 0, ir);
#endif
}