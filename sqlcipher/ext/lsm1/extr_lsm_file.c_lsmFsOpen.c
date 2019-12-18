#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ pWorker; scalar_t__ pClient; TYPE_3__* pFS; int /*<<< orphan*/  pEnv; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_12__ {char* zDb; char* zLog; int nPagesize; int nCacheMax; int nHash; int /*<<< orphan*/  fdDb; int /*<<< orphan*/  pEnv; int /*<<< orphan*/  szSector; TYPE_2__* pLsmFile; void* apHash; TYPE_1__* pDb; int /*<<< orphan*/  nMetaRwSize; int /*<<< orphan*/  nMetasize; int /*<<< orphan*/  nBlocksize; } ;
struct TYPE_11__ {int /*<<< orphan*/  pFile; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_2__ LsmFile ;
typedef  TYPE_3__ FileSystem ;

/* Variables and functions */
 int /*<<< orphan*/  LSM_DFLT_BLOCK_SIZE ; 
 int LSM_DFLT_PAGE_SIZE ; 
 int /*<<< orphan*/  LSM_META_PAGE_SIZE ; 
 int /*<<< orphan*/  LSM_META_RW_PAGE_SIZE ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fsOpenFile (TYPE_3__*,int,int /*<<< orphan*/ ,int*) ; 
 TYPE_2__* lsmDbRecycleFd (TYPE_1__*) ; 
 int /*<<< orphan*/  lsmEnvSectorSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsmFsClose (TYPE_3__*) ; 
 void* lsmMallocZeroRc (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int strlen (char const*) ; 

int lsmFsOpen(
  lsm_db *pDb,                    /* Database connection to open fd for */
  const char *zDb,                /* Full path to database file */
  int bReadonly                   /* True to open db file read-only */
){
  FileSystem *pFS;
  int rc = LSM_OK;
  int nDb = strlen(zDb);
  int nByte;

  assert( pDb->pFS==0 );
  assert( pDb->pWorker==0 && pDb->pClient==0 );

  nByte = sizeof(FileSystem) + nDb+1 + nDb+4+1;
  pFS = (FileSystem *)lsmMallocZeroRc(pDb->pEnv, nByte, &rc);
  if( pFS ){
    LsmFile *pLsmFile;
    pFS->zDb = (char *)&pFS[1];
    pFS->zLog = &pFS->zDb[nDb+1];
    pFS->nPagesize = LSM_DFLT_PAGE_SIZE;
    pFS->nBlocksize = LSM_DFLT_BLOCK_SIZE;
    pFS->nMetasize = LSM_META_PAGE_SIZE;
    pFS->nMetaRwSize = LSM_META_RW_PAGE_SIZE;
    pFS->pDb = pDb;
    pFS->pEnv = pDb->pEnv;

    /* Make a copy of the database and log file names. */
    memcpy(pFS->zDb, zDb, nDb+1);
    memcpy(pFS->zLog, zDb, nDb);
    memcpy(&pFS->zLog[nDb], "-log", 5);

    /* Allocate the hash-table here. At some point, it should be changed
    ** so that it can grow dynamicly. */
    pFS->nCacheMax = 2048*1024 / pFS->nPagesize;
    pFS->nHash = 4096;
    pFS->apHash = lsmMallocZeroRc(pDb->pEnv, sizeof(Page *) * pFS->nHash, &rc);

    /* Open the database file */
    pLsmFile = lsmDbRecycleFd(pDb);
    if( pLsmFile ){
      pFS->pLsmFile = pLsmFile;
      pFS->fdDb = pLsmFile->pFile;
      memset(pLsmFile, 0, sizeof(LsmFile));
    }else{
      pFS->pLsmFile = lsmMallocZeroRc(pDb->pEnv, sizeof(LsmFile), &rc);
      if( rc==LSM_OK ){
        pFS->fdDb = fsOpenFile(pFS, bReadonly, 0, &rc);
      }
    }

    if( rc!=LSM_OK ){
      lsmFsClose(pFS);
      pFS = 0;
    }else{
      pFS->szSector = lsmEnvSectorSize(pFS->pEnv, pFS->fdDb);
    }
  }

  pDb->pFS = pFS;
  return rc;
}