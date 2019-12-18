#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp_file ;
typedef  int /*<<< orphan*/  fs_file ;
struct TYPE_4__ {int /*<<< orphan*/  szOsFile; int /*<<< orphan*/  mxPathname; } ;
struct TYPE_6__ {TYPE_1__ base; TYPE_2__* pParent; } ;
struct TYPE_5__ {int /*<<< orphan*/  mxPathname; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX (int,int) ; 
 int SQLITE_OK ; 
 TYPE_3__ fs_vfs ; 
 TYPE_2__* sqlite3_vfs_find (int /*<<< orphan*/ ) ; 
 int sqlite3_vfs_register (TYPE_1__*,int /*<<< orphan*/ ) ; 

int fs_register(void){
  if( fs_vfs.pParent ) return SQLITE_OK;
  fs_vfs.pParent = sqlite3_vfs_find(0);
  fs_vfs.base.mxPathname = fs_vfs.pParent->mxPathname;
  fs_vfs.base.szOsFile = MAX(sizeof(tmp_file), sizeof(fs_file));
  return sqlite3_vfs_register(&fs_vfs.base, 0);
}