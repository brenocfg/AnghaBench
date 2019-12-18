#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_11__ {int iGroup; scalar_t__ eType; size_t iDelete; } ;
struct TYPE_10__ {int nGroup; scalar_t__ bPatchset; TYPE_1__** apGroup; } ;
struct TYPE_9__ {int* aChange; int nCol; int* aPK; int nChange; int /*<<< orphan*/  zTab; } ;
typedef  TYPE_1__ FuzzChangesetGroup ;
typedef  TYPE_2__ FuzzChangeset ;
typedef  TYPE_3__ FuzzChange ;

/* Variables and functions */
 scalar_t__ FUZZ_COLUMN_ADD ; 
 scalar_t__ FUZZ_COLUMN_ADDPK ; 
 scalar_t__ FUZZ_COLUMN_DEL ; 
 scalar_t__ FUZZ_GROUP_DEL ; 
 scalar_t__ FUZZ_GROUP_DUP ; 
 int SQLITE_OK ; 
 int fuzzCopyChange (TYPE_2__*,int,TYPE_3__*,int**,int**) ; 
 int /*<<< orphan*/  fuzzPutVarint (int*,int) ; 
 int fuzzSelectChange (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  fuzzWriteFile (char const*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fuzzDoOneFuzz(
  const char *zOut,               /* Filename to write modified changeset to */
  u8 *pBuf,                       /* Buffer to use for modified changeset */
  FuzzChangeset *pParse           /* Parse of input changeset */
){
  FuzzChange change;
  int iGrp;
  int rc = -1;

  while( rc<0 ){
    u8 *pOut = pBuf;
    rc = fuzzSelectChange(pParse, &change);
    for(iGrp=0; rc==SQLITE_OK && iGrp<pParse->nGroup; iGrp++){
      FuzzChangesetGroup *pGrp = pParse->apGroup[iGrp];
      int nTab = strlen(pGrp->zTab) + 1;
      int j;
      int nRep = 1;

      /* If this is the group to delete for a FUZZ_GROUP_DEL change, jump to
      ** the next group. Unless this is the only group in the changeset - in
      ** that case this change cannot be applied.
      **
      ** Or, if this is a FUZZ_GROUP_DUP, set nRep to 2 to output two
      ** copies of the group. */
      if( change.iGroup==iGrp ){
        if( change.eType==FUZZ_GROUP_DEL ){
          if( pParse->nGroup==1 ) rc = -1;
          continue;
        }
        else if( change.eType==FUZZ_GROUP_DUP ){
          nRep = 2;
        }
      }

      for(j=0; j<nRep; j++){
        int i;
        u8 *pSaved;
        u8 *p = pGrp->aChange;
        int nCol = pGrp->nCol;
        int iPKDel = 0;
        if( iGrp==change.iGroup ){
          if( change.eType==FUZZ_COLUMN_ADD 
           || change.eType==FUZZ_COLUMN_ADDPK 
          ){
            nCol++;
          }else if( change.eType==FUZZ_COLUMN_DEL ){
            nCol--;
            iPKDel = pGrp->aPK[change.iDelete];
          }
        }

        /* Output a table header */
        pOut++[0] = pParse->bPatchset ? 'P' : 'T';
        pOut += fuzzPutVarint(pOut, nCol);

        for(i=0; i<pGrp->nCol; i++){
          if( iGrp!=change.iGroup || i!=change.iDelete ){
            u8 v = pGrp->aPK[i];
            if( iPKDel && v>iPKDel ) v--;
            *(pOut++) = v;
          }
        }
        if( nCol>pGrp->nCol ){
          if( change.eType==FUZZ_COLUMN_ADD ){
            *(pOut++) = 0x00;
          }else{
            u8 max = 0;
            for(i=0; i<pGrp->nCol; i++){
              if( pGrp->aPK[i]>max ) max = pGrp->aPK[i];
            }
            *(pOut++) = max+1;
          }
        }
        memcpy(pOut, pGrp->zTab, nTab);
        pOut += nTab;

        /* Output the change array. */
        pSaved = pOut;
        for(i=0; rc==SQLITE_OK && i<pGrp->nChange; i++){
          rc = fuzzCopyChange(pParse, iGrp, &change, &p, &pOut);
        }
        if( pOut==pSaved ) rc = -1;
      }
    }
    if( rc==SQLITE_OK ){
      fuzzWriteFile(zOut, pBuf, pOut-pBuf);
    }
  }

  return rc;
}