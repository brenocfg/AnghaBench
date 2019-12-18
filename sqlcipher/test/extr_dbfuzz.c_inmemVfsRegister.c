#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int iVersion; int szOsFile; int mxPathname; char* zName; int /*<<< orphan*/  xCurrentTimeInt64; int /*<<< orphan*/  xSleep; int /*<<< orphan*/  xRandomness; int /*<<< orphan*/  xFullPathname; int /*<<< orphan*/  xAccess; int /*<<< orphan*/  xDelete; int /*<<< orphan*/  xOpen; } ;
typedef  TYPE_1__ sqlite3_vfs ;
typedef  int /*<<< orphan*/  VHandle ;

/* Variables and functions */
 int /*<<< orphan*/  inmemAccess ; 
 int /*<<< orphan*/  inmemDelete ; 
 int /*<<< orphan*/  inmemFullPathname ; 
 int /*<<< orphan*/  inmemOpen ; 
 TYPE_1__* sqlite3_vfs_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_vfs_register (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void inmemVfsRegister(void){
  static sqlite3_vfs inmemVfs;
  sqlite3_vfs *pDefault = sqlite3_vfs_find(0);
  inmemVfs.iVersion = 3;
  inmemVfs.szOsFile = sizeof(VHandle);
  inmemVfs.mxPathname = 200;
  inmemVfs.zName = "inmem";
  inmemVfs.xOpen = inmemOpen;
  inmemVfs.xDelete = inmemDelete;
  inmemVfs.xAccess = inmemAccess;
  inmemVfs.xFullPathname = inmemFullPathname;
  inmemVfs.xRandomness = pDefault->xRandomness;
  inmemVfs.xSleep = pDefault->xSleep;
  inmemVfs.xCurrentTimeInt64 = pDefault->xCurrentTimeInt64;
  sqlite3_vfs_register(&inmemVfs, 0);
}