#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ bReadonly; scalar_t__ pShmhdr; int /*<<< orphan*/  pEnv; int /*<<< orphan*/  aSnapshot; int /*<<< orphan*/  pFS; scalar_t__ pDatabase; } ;
typedef  TYPE_1__ lsm_db ;

/* Variables and functions */
 int LSM_MISUSE ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertRwclientLockValue (TYPE_1__*) ; 
 int getFullpathname (int /*<<< orphan*/ ,char const*,char**) ; 
 int /*<<< orphan*/  lsmCheckpointBlksz (int /*<<< orphan*/ ) ; 
 int lsmCheckpointLoad (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsmCheckpointPgsz (int /*<<< orphan*/ ) ; 
 int lsmDbDatabaseConnect (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  lsmFree (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lsmFsSetBlockSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsmFsSetPageSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int lsm_open(lsm_db *pDb, const char *zFilename){
  int rc;

  if( pDb->pDatabase ){
    rc = LSM_MISUSE;
  }else{
    char *zFull;

    /* Translate the possibly relative pathname supplied by the user into
    ** an absolute pathname. This is required because the supplied path
    ** is used (either directly or with "-log" appended to it) for more 
    ** than one purpose - to open both the database and log files, and 
    ** perhaps to unlink the log file during disconnection. An absolute
    ** path is required to ensure that the correct files are operated
    ** on even if the application changes the cwd.  */
    rc = getFullpathname(pDb->pEnv, zFilename, &zFull);
    assert( rc==LSM_OK || zFull==0 );

    /* Connect to the database. */
    if( rc==LSM_OK ){
      rc = lsmDbDatabaseConnect(pDb, zFull);
    }

    if( pDb->bReadonly==0 ){
      /* Configure the file-system connection with the page-size and block-size
      ** of this database. Even if the database file is zero bytes in size
      ** on disk, these values have been set in shared-memory by now, and so 
      ** are guaranteed not to change during the lifetime of this connection.  
      */
      if( rc==LSM_OK && LSM_OK==(rc = lsmCheckpointLoad(pDb, 0)) ){
        lsmFsSetPageSize(pDb->pFS, lsmCheckpointPgsz(pDb->aSnapshot));
        lsmFsSetBlockSize(pDb->pFS, lsmCheckpointBlksz(pDb->aSnapshot));
      }
    }

    lsmFree(pDb->pEnv, zFull);
    assertRwclientLockValue(pDb);
  }

  assert( pDb->bReadonly==0 || pDb->bReadonly==1 );
  assert( rc!=LSM_OK || (pDb->pShmhdr==0)==(pDb->bReadonly==1) );

  return rc;
}