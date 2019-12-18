#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  lsm_env ;

/* Variables and functions */
 scalar_t__ ERANGE ; 
 int LSM_IOERR_BKPT ; 
 int LSM_NOMEM_BKPT ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 char* getcwd (char*,int) ; 
 int /*<<< orphan*/  lsmFree (int /*<<< orphan*/ *,char*) ; 
 char* lsmMalloc (int /*<<< orphan*/ *,int) ; 
 char* lsmReallocOrFree (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int lsmPosixOsFullpath(
  lsm_env *pEnv,
  const char *zName,
  char *zOut,
  int *pnOut
){
  int nBuf = *pnOut;
  int nReq;

  if( zName[0]!='/' ){
    char *z;
    char *zTmp;
    int nTmp = 512;
    zTmp = lsmMalloc(pEnv, nTmp);
    while( zTmp ){
      z = getcwd(zTmp, nTmp);
      if( z || errno!=ERANGE ) break;
      nTmp = nTmp*2;
      zTmp = lsmReallocOrFree(pEnv, zTmp, nTmp);
    }
    if( zTmp==0 ) return LSM_NOMEM_BKPT;
    if( z==0 ) return LSM_IOERR_BKPT;
    assert( z==zTmp );

    nTmp = strlen(zTmp);
    nReq = nTmp + 1 + strlen(zName) + 1;
    if( nReq<=nBuf ){
      memcpy(zOut, zTmp, nTmp);
      zOut[nTmp] = '/';
      memcpy(&zOut[nTmp+1], zName, strlen(zName)+1);
    }
    lsmFree(pEnv, zTmp);
  }else{
    nReq = strlen(zName)+1;
    if( nReq<=nBuf ){
      memcpy(zOut, zName, strlen(zName)+1);
    }
  }

  *pnOut = nReq;
  return LSM_OK;
}