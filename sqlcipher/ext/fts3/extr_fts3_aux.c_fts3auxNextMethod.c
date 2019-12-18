#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct Fts3auxColstats {int dummy; } ;
struct TYPE_8__ {scalar_t__ pVtab; } ;
typedef  TYPE_1__ sqlite3_vtab_cursor ;
typedef  int sqlite3_int64 ;
struct TYPE_12__ {scalar_t__ nDoc; int /*<<< orphan*/  nOcc; } ;
struct TYPE_11__ {int nDoclist; char* aDoclist; scalar_t__ nTerm; int /*<<< orphan*/  zTerm; } ;
struct TYPE_10__ {size_t iCol; size_t nStat; scalar_t__ nStop; int isEof; TYPE_5__* aStat; TYPE_4__ csr; scalar_t__ zStop; int /*<<< orphan*/  iRowid; } ;
struct TYPE_9__ {int /*<<< orphan*/ * pFts3Tab; } ;
typedef  TYPE_2__ Fts3auxTable ;
typedef  TYPE_3__ Fts3auxCursor ;
typedef  int /*<<< orphan*/  Fts3Table ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ fts3auxGrowStatArray (TYPE_3__*,int) ; 
 int memcmp (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3Fts3GetVarint (char*,int*) ; 
 int sqlite3Fts3SegReaderStep (int /*<<< orphan*/ *,TYPE_4__*) ; 

__attribute__((used)) static int fts3auxNextMethod(sqlite3_vtab_cursor *pCursor){
  Fts3auxCursor *pCsr = (Fts3auxCursor *)pCursor;
  Fts3Table *pFts3 = ((Fts3auxTable *)pCursor->pVtab)->pFts3Tab;
  int rc;

  /* Increment our pretend rowid value. */
  pCsr->iRowid++;

  for(pCsr->iCol++; pCsr->iCol<pCsr->nStat; pCsr->iCol++){
    if( pCsr->aStat[pCsr->iCol].nDoc>0 ) return SQLITE_OK;
  }

  rc = sqlite3Fts3SegReaderStep(pFts3, &pCsr->csr);
  if( rc==SQLITE_ROW ){
    int i = 0;
    int nDoclist = pCsr->csr.nDoclist;
    char *aDoclist = pCsr->csr.aDoclist;
    int iCol;

    int eState = 0;

    if( pCsr->zStop ){
      int n = (pCsr->nStop<pCsr->csr.nTerm) ? pCsr->nStop : pCsr->csr.nTerm;
      int mc = memcmp(pCsr->zStop, pCsr->csr.zTerm, n);
      if( mc<0 || (mc==0 && pCsr->csr.nTerm>pCsr->nStop) ){
        pCsr->isEof = 1;
        return SQLITE_OK;
      }
    }

    if( fts3auxGrowStatArray(pCsr, 2) ) return SQLITE_NOMEM;
    memset(pCsr->aStat, 0, sizeof(struct Fts3auxColstats) * pCsr->nStat);
    iCol = 0;

    while( i<nDoclist ){
      sqlite3_int64 v = 0;

      i += sqlite3Fts3GetVarint(&aDoclist[i], &v);
      switch( eState ){
        /* State 0. In this state the integer just read was a docid. */
        case 0:
          pCsr->aStat[0].nDoc++;
          eState = 1;
          iCol = 0;
          break;

        /* State 1. In this state we are expecting either a 1, indicating
        ** that the following integer will be a column number, or the
        ** start of a position list for column 0.  
        ** 
        ** The only difference between state 1 and state 2 is that if the
        ** integer encountered in state 1 is not 0 or 1, then we need to
        ** increment the column 0 "nDoc" count for this term.
        */
        case 1:
          assert( iCol==0 );
          if( v>1 ){
            pCsr->aStat[1].nDoc++;
          }
          eState = 2;
          /* fall through */

        case 2:
          if( v==0 ){       /* 0x00. Next integer will be a docid. */
            eState = 0;
          }else if( v==1 ){ /* 0x01. Next integer will be a column number. */
            eState = 3;
          }else{            /* 2 or greater. A position. */
            pCsr->aStat[iCol+1].nOcc++;
            pCsr->aStat[0].nOcc++;
          }
          break;

        /* State 3. The integer just read is a column number. */
        default: assert( eState==3 );
          iCol = (int)v;
          if( fts3auxGrowStatArray(pCsr, iCol+2) ) return SQLITE_NOMEM;
          pCsr->aStat[iCol+1].nDoc++;
          eState = 2;
          break;
      }
    }

    pCsr->iCol = 0;
    rc = SQLITE_OK;
  }else{
    pCsr->isEof = 1;
  }
  return rc;
}