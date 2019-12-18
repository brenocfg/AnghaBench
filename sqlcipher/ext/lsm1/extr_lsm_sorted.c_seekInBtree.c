#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_14__ {void* pData; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_13__ {TYPE_1__* pDb; } ;
struct TYPE_12__ {scalar_t__ iRoot; } ;
struct TYPE_11__ {int /*<<< orphan*/  xCmp; int /*<<< orphan*/  pFS; } ;
typedef  TYPE_2__ Segment ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_3__ MultiCursor ;
typedef  int LsmPgno ;
typedef  TYPE_4__ LsmBlob ;

/* Variables and functions */
 int LSM_OK ; 
 int SEGMENT_BTREE_FLAG ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * fsPageData (int /*<<< orphan*/ *,int*) ; 
 int lsmFsDbPageGet (int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  lsmFsPageRelease (int /*<<< orphan*/ *) ; 
 int pageGetBtreeKey (TYPE_2__*,int /*<<< orphan*/ *,int,int*,int*,void**,int*,TYPE_4__*) ; 
 int pageGetBtreeRef (int /*<<< orphan*/ *,int) ; 
 int pageGetFlags (int /*<<< orphan*/ *,int) ; 
 int pageGetNRec (int /*<<< orphan*/ *,int) ; 
 scalar_t__ pageGetPtr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sortedBlobFree (TYPE_4__*) ; 
 int sortedKeyCompare (int /*<<< orphan*/ ,int,void*,int,int,void*,int) ; 

__attribute__((used)) static int seekInBtree(
  MultiCursor *pCsr,              /* Multi-cursor object */
  Segment *pSeg,                  /* Seek within this segment */
  int iTopic,
  void *pKey, int nKey,           /* Key to seek to */
  LsmPgno *aPg,                   /* OUT: Page numbers */
  Page **ppPg                     /* OUT: Leaf (sorted-run) page reference */
){
  int i = 0;
  int rc;
  int iPg;
  Page *pPg = 0;
  LsmBlob blob = {0, 0, 0};

  iPg = (int)pSeg->iRoot;
  do {
    LsmPgno *piFirst = 0;
    if( aPg ){
      aPg[i++] = iPg;
      piFirst = &aPg[i];
    }

    rc = lsmFsDbPageGet(pCsr->pDb->pFS, pSeg, iPg, &pPg);
    assert( rc==LSM_OK || pPg==0 );
    if( rc==LSM_OK ){
      u8 *aData;                  /* Buffer containing page data */
      int nData;                  /* Size of aData[] in bytes */
      int iMin;
      int iMax;
      int nRec;
      int flags;

      aData = fsPageData(pPg, &nData);
      flags = pageGetFlags(aData, nData);
      if( (flags & SEGMENT_BTREE_FLAG)==0 ) break;

      iPg = (int)pageGetPtr(aData, nData);
      nRec = pageGetNRec(aData, nData);

      iMin = 0;
      iMax = nRec-1;
      while( iMax>=iMin ){
        int iTry = (iMin+iMax)/2;
        void *pKeyT; int nKeyT;       /* Key for cell iTry */
        int iTopicT;                  /* Topic for key pKeyT/nKeyT */
        LsmPgno iPtr;                 /* Pointer associated with cell iTry */
        int res;                      /* (pKey - pKeyT) */

        rc = pageGetBtreeKey(
            pSeg, pPg, iTry, &iPtr, &iTopicT, &pKeyT, &nKeyT, &blob
        );
        if( rc!=LSM_OK ) break;
        if( piFirst && pKeyT==blob.pData ){
          *piFirst = pageGetBtreeRef(pPg, iTry);
          piFirst = 0;
          i++;
        }

        res = sortedKeyCompare(
            pCsr->pDb->xCmp, iTopic, pKey, nKey, iTopicT, pKeyT, nKeyT
        );
        if( res<0 ){
          iPg = (int)iPtr;
          iMax = iTry-1;
        }else{
          iMin = iTry+1;
        }
      }
      lsmFsPageRelease(pPg);
      pPg = 0;
    }
  }while( rc==LSM_OK );

  sortedBlobFree(&blob);
  assert( (rc==LSM_OK)==(pPg!=0) );
  if( ppPg ){
    *ppPg = pPg;
  }else{
    lsmFsPageRelease(pPg);
  }
  return rc;
}