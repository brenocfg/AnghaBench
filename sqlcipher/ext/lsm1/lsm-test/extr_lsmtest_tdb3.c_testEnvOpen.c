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
typedef  int /*<<< orphan*/  lsm_file ;
struct TYPE_7__ {int (* xOpen ) (TYPE_1__*,char const*,int,int /*<<< orphan*/ *) ;scalar_t__ pVfsCtx; } ;
typedef  TYPE_1__ lsm_env ;
struct TYPE_8__ {int bLog; int /*<<< orphan*/  pReal; int /*<<< orphan*/ * pDb; } ;
typedef  TYPE_2__ LsmFile ;
typedef  int /*<<< orphan*/  LsmDb ;

/* Variables and functions */
 int LSM_OK ; 
 scalar_t__ memcmp (char*,char const*,int) ; 
 int strlen (char const*) ; 
 int stub1 (TYPE_1__*,char const*,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* tdb_lsm_env () ; 
 int /*<<< orphan*/  testFree (TYPE_2__*) ; 
 scalar_t__ testMalloc (int) ; 

__attribute__((used)) static int testEnvOpen(
  lsm_env *pEnv,                  /* Environment for current LsmDb */
  const char *zFile,              /* Name of file to open */
  int flags,
  lsm_file **ppFile               /* OUT: New file handle object */
){
  lsm_env *pRealEnv = tdb_lsm_env();
  LsmDb *pDb = (LsmDb *)pEnv->pVfsCtx;
  int rc;                         /* Return Code */
  LsmFile *pRet;                  /* The new file handle */
  int nFile;                      /* Length of string zFile in bytes */

  nFile = strlen(zFile);
  pRet = (LsmFile *)testMalloc(sizeof(LsmFile));
  pRet->pDb = pDb;
  pRet->bLog = (nFile > 4 && 0==memcmp("-log", &zFile[nFile-4], 4));

  rc = pRealEnv->xOpen(pRealEnv, zFile, flags, &pRet->pReal);
  if( rc!=LSM_OK ){
    testFree(pRet);
    pRet = 0;
  }

  *ppFile = (lsm_file *)pRet;
  return rc;
}