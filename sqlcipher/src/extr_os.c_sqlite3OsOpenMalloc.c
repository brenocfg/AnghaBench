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
struct TYPE_4__ {int /*<<< orphan*/  szOsFile; } ;
typedef  TYPE_1__ sqlite3_vfs ;
typedef  int /*<<< orphan*/  sqlite3_file ;

/* Variables and functions */
 int SQLITE_NOMEM_BKPT ; 
 int SQLITE_OK ; 
 scalar_t__ sqlite3MallocZero (int /*<<< orphan*/ ) ; 
 int sqlite3OsOpen (TYPE_1__*,char const*,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ *) ; 

int sqlite3OsOpenMalloc(
  sqlite3_vfs *pVfs,
  const char *zFile,
  sqlite3_file **ppFile,
  int flags,
  int *pOutFlags
){
  int rc;
  sqlite3_file *pFile;
  pFile = (sqlite3_file *)sqlite3MallocZero(pVfs->szOsFile);
  if( pFile ){
    rc = sqlite3OsOpen(pVfs, zFile, pFile, flags, pOutFlags);
    if( rc!=SQLITE_OK ){
      sqlite3_free(pFile);
    }else{
      *ppFile = pFile;
    }
  }else{
    rc = SQLITE_NOMEM_BKPT;
  }
  return rc;
}