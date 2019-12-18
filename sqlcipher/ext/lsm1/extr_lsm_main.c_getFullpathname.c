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
struct TYPE_6__ {int (* xFullpath ) (TYPE_1__*,char const*,char*,int*) ;} ;
typedef  TYPE_1__ lsm_env ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  lsmFree (TYPE_1__*,char*) ; 
 char* lsmReallocOrFreeRc (TYPE_1__*,char*,int,int*) ; 
 int stub1 (TYPE_1__*,char const*,char*,int*) ; 

__attribute__((used)) static int getFullpathname(
  lsm_env *pEnv, 
  const char *zRel,
  char **pzAbs
){
  int nAlloc = 0;
  char *zAlloc = 0;
  int nReq = 0;
  int rc;

  do{
    nAlloc = nReq;
    rc = pEnv->xFullpath(pEnv, zRel, zAlloc, &nReq);
    if( nReq>nAlloc ){
      zAlloc = lsmReallocOrFreeRc(pEnv, zAlloc, nReq, &rc);
    }
  }while( nReq>nAlloc && rc==LSM_OK );

  if( rc!=LSM_OK ){
    lsmFree(pEnv, zAlloc);
    zAlloc = 0;
  }
  *pzAbs = zAlloc;
  return rc;
}