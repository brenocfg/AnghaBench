#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int i64 ;
typedef  int /*<<< orphan*/  filter ;
typedef  int /*<<< orphan*/  csr ;
struct TYPE_9__ {int flags; char* aDoclist; size_t nDoclist; int /*<<< orphan*/  nTerm; int /*<<< orphan*/  zTerm; } ;
typedef  int /*<<< orphan*/  Fts3Table ;
typedef  TYPE_1__ Fts3SegFilter ;
typedef  TYPE_1__ Fts3MultiSegReader ;

/* Variables and functions */
 int /*<<< orphan*/  FTS3_SEGCURSOR_ALL ; 
 int FTS3_SEGMENT_IGNORE_EMPTY ; 
 int FTS3_SEGMENT_REQUIRE_POS ; 
 int FTS3_SEGMENT_SCAN ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts3ChecksumEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3Fts3GetVarint (char*,int*) ; 
 int sqlite3Fts3SegReaderCursor (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3Fts3SegReaderFinish (TYPE_1__*) ; 
 int sqlite3Fts3SegReaderStart (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 int sqlite3Fts3SegReaderStep (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static u64 fts3ChecksumIndex(
  Fts3Table *p,                   /* FTS3 table handle */
  int iLangid,                    /* Language id to return cksum for */
  int iIndex,                     /* Index to cksum (0..p->nIndex-1) */
  int *pRc                        /* OUT: Return code */
){
  Fts3SegFilter filter;
  Fts3MultiSegReader csr;
  int rc;
  u64 cksum = 0;

  assert( *pRc==SQLITE_OK );

  memset(&filter, 0, sizeof(filter));
  memset(&csr, 0, sizeof(csr));
  filter.flags =  FTS3_SEGMENT_REQUIRE_POS|FTS3_SEGMENT_IGNORE_EMPTY;
  filter.flags |= FTS3_SEGMENT_SCAN;

  rc = sqlite3Fts3SegReaderCursor(
      p, iLangid, iIndex, FTS3_SEGCURSOR_ALL, 0, 0, 0, 1,&csr
  );
  if( rc==SQLITE_OK ){
    rc = sqlite3Fts3SegReaderStart(p, &csr, &filter);
  }

  if( rc==SQLITE_OK ){
    while( SQLITE_ROW==(rc = sqlite3Fts3SegReaderStep(p, &csr)) ){
      char *pCsr = csr.aDoclist;
      char *pEnd = &pCsr[csr.nDoclist];

      i64 iDocid = 0;
      i64 iCol = 0;
      i64 iPos = 0;

      pCsr += sqlite3Fts3GetVarint(pCsr, &iDocid);
      while( pCsr<pEnd ){
        i64 iVal = 0;
        pCsr += sqlite3Fts3GetVarint(pCsr, &iVal);
        if( pCsr<pEnd ){
          if( iVal==0 || iVal==1 ){
            iCol = 0;
            iPos = 0;
            if( iVal ){
              pCsr += sqlite3Fts3GetVarint(pCsr, &iCol);
            }else{
              pCsr += sqlite3Fts3GetVarint(pCsr, &iVal);
              iDocid += iVal;
            }
          }else{
            iPos += (iVal - 2);
            cksum = cksum ^ fts3ChecksumEntry(
                csr.zTerm, csr.nTerm, iLangid, iIndex, iDocid,
                (int)iCol, (int)iPos
            );
          }
        }
      }
    }
  }
  sqlite3Fts3SegReaderFinish(&csr);

  *pRc = rc;
  return cksum;
}