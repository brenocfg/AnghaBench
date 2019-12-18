#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int (* xAccess ) (TYPE_2__*,char const*,int,int*) ;} ;
typedef  TYPE_2__ sqlite3_vfs ;
typedef  scalar_t__ sqlite3_int64 ;
struct TYPE_11__ {TYPE_2__* pRealVfs; } ;
typedef  TYPE_3__ rbu_vfs ;
struct TYPE_12__ {int /*<<< orphan*/  base; TYPE_1__* pRbu; } ;
typedef  TYPE_4__ rbu_file ;
struct TYPE_9__ {scalar_t__ eStage; } ;

/* Variables and functions */
 scalar_t__ RBU_STAGE_OAL ; 
 int SQLITE_ACCESS_EXISTS ; 
 int SQLITE_CANTOPEN ; 
 int SQLITE_OK ; 
 TYPE_4__* rbuFindMaindb (TYPE_3__*,char const*,int) ; 
 int rbuVfsFileSize (int /*<<< orphan*/ *,scalar_t__*) ; 
 int stub1 (TYPE_2__*,char const*,int,int*) ; 

__attribute__((used)) static int rbuVfsAccess(
  sqlite3_vfs *pVfs, 
  const char *zPath, 
  int flags, 
  int *pResOut
){
  rbu_vfs *pRbuVfs = (rbu_vfs*)pVfs;
  sqlite3_vfs *pRealVfs = pRbuVfs->pRealVfs;
  int rc;

  rc = pRealVfs->xAccess(pRealVfs, zPath, flags, pResOut);

  /* If this call is to check if a *-wal file associated with an RBU target
  ** database connection exists, and the RBU update is in RBU_STAGE_OAL,
  ** the following special handling is activated:
  **
  **   a) if the *-wal file does exist, return SQLITE_CANTOPEN. This
  **      ensures that the RBU extension never tries to update a database
  **      in wal mode, even if the first page of the database file has
  **      been damaged. 
  **
  **   b) if the *-wal file does not exist, claim that it does anyway,
  **      causing SQLite to call xOpen() to open it. This call will also
  **      be intercepted (see the rbuVfsOpen() function) and the *-oal
  **      file opened instead.
  */
  if( rc==SQLITE_OK && flags==SQLITE_ACCESS_EXISTS ){
    rbu_file *pDb = rbuFindMaindb(pRbuVfs, zPath, 1);
    if( pDb && pDb->pRbu && pDb->pRbu->eStage==RBU_STAGE_OAL ){
      if( *pResOut ){
        rc = SQLITE_CANTOPEN;
      }else{
        sqlite3_int64 sz = 0;
        rc = rbuVfsFileSize(&pDb->base, &sz);
        *pResOut = (sz>0);
      }
    }
  }

  return rc;
}