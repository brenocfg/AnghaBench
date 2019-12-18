#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_8__ {int iOutputOff; } ;
struct TYPE_7__ {int /*<<< orphan*/  pPage; TYPE_1__* pLevel; } ;
struct TYPE_6__ {TYPE_3__* pMerge; } ;
typedef  TYPE_2__ MergeWorker ;
typedef  TYPE_3__ Merge ;

/* Variables and functions */
 int LSM_MIN (int,scalar_t__) ; 
 int LSM_OK ; 
 scalar_t__ SEGMENT_EOF (int,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fsPageData (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  lsmFsPageWritable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int mergeWorkerNextPage (TYPE_2__*,int) ; 
 int pageGetNRec (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mergeWorkerData(
  MergeWorker *pMW,               /* Merge worker object */
  int bSep,                       /* True to write to separators run */
  int iFPtr,                      /* Footer ptr for new pages */
  u8 *aWrite,                     /* Write data from this buffer */
  int nWrite                      /* Size of aWrite[] in bytes */
){
  int rc = LSM_OK;                /* Return code */
  int nRem = nWrite;              /* Number of bytes still to write */

  while( rc==LSM_OK && nRem>0 ){
    Merge *pMerge = pMW->pLevel->pMerge;
    int nCopy;                    /* Number of bytes to copy */
    u8 *aData;                    /* Pointer to buffer of current output page */
    int nData;                    /* Size of aData[] in bytes */
    int nRec;                     /* Number of records on current output page */
    int iOff;                     /* Offset in aData[] to write to */

    assert( lsmFsPageWritable(pMW->pPage) );
   
    aData = fsPageData(pMW->pPage, &nData);
    nRec = pageGetNRec(aData, nData);
    iOff = pMerge->iOutputOff;
    nCopy = LSM_MIN(nRem, SEGMENT_EOF(nData, nRec) - iOff);

    memcpy(&aData[iOff], &aWrite[nWrite-nRem], nCopy);
    nRem -= nCopy;

    if( nRem>0 ){
      rc = mergeWorkerNextPage(pMW, iFPtr);
    }else{
      pMerge->iOutputOff = iOff + nCopy;
    }
  }

  return rc;
}