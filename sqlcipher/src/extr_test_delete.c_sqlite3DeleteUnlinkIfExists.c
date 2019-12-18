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
struct TYPE_4__ {int (* xDelete ) (TYPE_1__*,char const*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ sqlite3_vfs ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  F_OK ; 
 int SQLITE_ERROR ; 
 int SQLITE_IOERR_DELETE_NOENT ; 
 int SQLITE_OK ; 
 int access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int stub1 (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int unlink (char const*) ; 

__attribute__((used)) static int sqlite3DeleteUnlinkIfExists(
  sqlite3_vfs *pVfs,
  const char *zFile, 
  int *pbExists
){
  int rc = SQLITE_ERROR;
#if SQLITE_OS_WIN
  if( pVfs ){
    if( pbExists ) *pbExists = 1;
    rc = pVfs->xDelete(pVfs, zFile, 0);
    if( rc==SQLITE_IOERR_DELETE_NOENT ){
      if( pbExists ) *pbExists = 0;
      rc = SQLITE_OK;
    }
  }
#else
  assert( pVfs==0 );
  rc = access(zFile, F_OK);
  if( rc ){
    if( errno==ENOENT ){ 
      if( pbExists ) *pbExists = 0;
      rc = SQLITE_OK; 
    }
  }else{
    if( pbExists ) *pbExists = 1;
    rc = unlink(zFile);
  }
#endif
  return rc;
}