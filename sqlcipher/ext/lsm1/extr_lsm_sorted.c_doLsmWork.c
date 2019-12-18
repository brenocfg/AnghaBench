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
typedef  int /*<<< orphan*/  lsm_db ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int doLsmSingleWork (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int*,int*) ; 
 int lsm_checkpoint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int doLsmWork(lsm_db *pDb, int nMerge, int nPage, int *pnWrite){
  int rc = LSM_OK;                /* Return code */
  int nWrite = 0;                 /* Number of pages written */

  assert( nMerge>=1 );

  if( nPage!=0 ){
    int bCkpt = 0;
    do {
      int nThis = 0;
      int nReq = (nPage>=0) ? (nPage-nWrite) : ((int)0x7FFFFFFF);

      bCkpt = 0;
      rc = doLsmSingleWork(pDb, 0, nMerge, nReq, &nThis, &bCkpt);
      nWrite += nThis;
      if( rc==LSM_OK && bCkpt ){
        rc = lsm_checkpoint(pDb, 0);
      }
    }while( rc==LSM_OK && bCkpt && (nWrite<nPage || nPage<0) );
  }

  if( pnWrite ){
    if( rc==LSM_OK ){
      *pnWrite = nWrite;
    }else{
      *pnWrite = 0;
    }
  }
  return rc;
}