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
struct ValueNewStat4Ctx {int dummy; } ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (struct ValueNewStat4Ctx*) ; 
 int /*<<< orphan*/ * sqlite3ValueNew (int /*<<< orphan*/ *) ; 

__attribute__((used)) static sqlite3_value *valueNew(sqlite3 *db, struct ValueNewStat4Ctx *p){
#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
  if( p ){
    UnpackedRecord *pRec = p->ppRec[0];

    if( pRec==0 ){
      Index *pIdx = p->pIdx;      /* Index being probed */
      int nByte;                  /* Bytes of space to allocate */
      int i;                      /* Counter variable */
      int nCol = pIdx->nColumn;   /* Number of index columns including rowid */
  
      nByte = sizeof(Mem) * nCol + ROUND8(sizeof(UnpackedRecord));
      pRec = (UnpackedRecord*)sqlite3DbMallocZero(db, nByte);
      if( pRec ){
        pRec->pKeyInfo = sqlite3KeyInfoOfIndex(p->pParse, pIdx);
        if( pRec->pKeyInfo ){
          assert( pRec->pKeyInfo->nAllField==nCol );
          assert( pRec->pKeyInfo->enc==ENC(db) );
          pRec->aMem = (Mem *)((u8*)pRec + ROUND8(sizeof(UnpackedRecord)));
          for(i=0; i<nCol; i++){
            pRec->aMem[i].flags = MEM_Null;
            pRec->aMem[i].db = db;
          }
        }else{
          sqlite3DbFreeNN(db, pRec);
          pRec = 0;
        }
      }
      if( pRec==0 ) return 0;
      p->ppRec[0] = pRec;
    }
  
    pRec->nField = p->iVal+1;
    return &pRec->aMem[p->iVal];
  }
#else
  UNUSED_PARAMETER(p);
#endif /* defined(SQLITE_ENABLE_STAT3_OR_STAT4) */
  return sqlite3ValueNew(db);
}