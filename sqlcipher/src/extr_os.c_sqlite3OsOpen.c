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
struct TYPE_7__ {int (* xOpen ) (TYPE_1__*,char const*,TYPE_2__*,int,int*) ;} ;
typedef  TYPE_1__ sqlite3_vfs ;
struct TYPE_8__ {scalar_t__ pMethods; } ;
typedef  TYPE_2__ sqlite3_file ;

/* Variables and functions */
 int /*<<< orphan*/  DO_OS_MALLOC_TEST (int /*<<< orphan*/ ) ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int stub1 (TYPE_1__*,char const*,TYPE_2__*,int,int*) ; 

int sqlite3OsOpen(
  sqlite3_vfs *pVfs,
  const char *zPath,
  sqlite3_file *pFile,
  int flags,
  int *pFlagsOut
){
  int rc;
  DO_OS_MALLOC_TEST(0);
  /* 0x87f7f is a mask of SQLITE_OPEN_ flags that are valid to be passed
  ** down into the VFS layer.  Some SQLITE_OPEN_ flags (for example,
  ** SQLITE_OPEN_FULLMUTEX or SQLITE_OPEN_SHAREDCACHE) are blocked before
  ** reaching the VFS. */
  rc = pVfs->xOpen(pVfs, zPath, pFile, flags & 0x87f7f, pFlagsOut);
  assert( rc==SQLITE_OK || pFile->pMethods==0 );
  return rc;
}