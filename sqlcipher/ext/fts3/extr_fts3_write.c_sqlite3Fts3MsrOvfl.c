#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sqlite3_int64 ;
struct TYPE_11__ {scalar_t__ pVtab; } ;
struct TYPE_15__ {TYPE_1__ base; } ;
struct TYPE_14__ {int nSegment; TYPE_3__** apSegment; } ;
struct TYPE_13__ {scalar_t__ iStartBlock; scalar_t__ iLeafEndBlock; } ;
struct TYPE_12__ {int nPgsz; int bFts4; } ;
typedef  TYPE_2__ Fts3Table ;
typedef  TYPE_3__ Fts3SegReader ;
typedef  TYPE_4__ Fts3MultiSegReader ;
typedef  TYPE_5__ Fts3Cursor ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts3SegReaderIsPending (TYPE_3__*) ; 
 int /*<<< orphan*/  fts3SegReaderIsRootOnly (TYPE_3__*) ; 
 int sqlite3Fts3ReadBlock (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

int sqlite3Fts3MsrOvfl(
  Fts3Cursor *pCsr, 
  Fts3MultiSegReader *pMsr,
  int *pnOvfl
){
  Fts3Table *p = (Fts3Table*)pCsr->base.pVtab;
  int nOvfl = 0;
  int ii;
  int rc = SQLITE_OK;
  int pgsz = p->nPgsz;

  assert( p->bFts4 );
  assert( pgsz>0 );

  for(ii=0; rc==SQLITE_OK && ii<pMsr->nSegment; ii++){
    Fts3SegReader *pReader = pMsr->apSegment[ii];
    if( !fts3SegReaderIsPending(pReader) 
     && !fts3SegReaderIsRootOnly(pReader) 
    ){
      sqlite3_int64 jj;
      for(jj=pReader->iStartBlock; jj<=pReader->iLeafEndBlock; jj++){
        int nBlob;
        rc = sqlite3Fts3ReadBlock(p, jj, 0, &nBlob, 0);
        if( rc!=SQLITE_OK ) break;
        if( (nBlob+35)>pgsz ){
          nOvfl += (nBlob + 34)/pgsz;
        }
      }
    }
  }
  *pnOvfl = nOvfl;
  return rc;
}