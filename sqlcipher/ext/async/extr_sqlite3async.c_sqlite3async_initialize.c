#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  mxPathname; } ;
typedef  TYPE_1__ sqlite3_vfs ;
struct TYPE_6__ {void* pAppData; int /*<<< orphan*/  mxPathname; } ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 scalar_t__ async_os_initialize () ; 
 int /*<<< orphan*/  async_os_shutdown () ; 
 TYPE_2__ async_vfs ; 
 TYPE_1__* sqlite3_vfs_find (char const*) ; 
 int sqlite3_vfs_register (TYPE_2__*,int) ; 

int sqlite3async_initialize(const char *zParent, int isDefault){
  int rc = SQLITE_OK;
  if( async_vfs.pAppData==0 ){
    sqlite3_vfs *pParent = sqlite3_vfs_find(zParent);
    if( !pParent || async_os_initialize() ){
      rc = SQLITE_ERROR;
    }else if( SQLITE_OK!=(rc = sqlite3_vfs_register(&async_vfs, isDefault)) ){
      async_os_shutdown();
    }else{
      async_vfs.pAppData = (void *)pParent;
      async_vfs.mxPathname = ((sqlite3_vfs *)async_vfs.pAppData)->mxPathname;
    }
  }
  return rc;
}