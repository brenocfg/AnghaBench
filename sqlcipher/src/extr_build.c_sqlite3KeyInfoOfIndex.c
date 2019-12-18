#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int nColumn; int nKeyCol; char** azColl; int bNoQuery; int /*<<< orphan*/ * aSortOrder; scalar_t__ uniqNotNull; } ;
struct TYPE_12__ {int /*<<< orphan*/ * aSortOrder; int /*<<< orphan*/ * aColl; } ;
struct TYPE_11__ {scalar_t__ rc; scalar_t__ nErr; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ Parse ;
typedef  TYPE_2__ KeyInfo ;
typedef  TYPE_3__ Index ;

/* Variables and functions */
 scalar_t__ SQLITE_ERROR_MISSING_COLLSEQ ; 
 scalar_t__ SQLITE_ERROR_RETRY ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* sqlite3KeyInfoAlloc (int /*<<< orphan*/ ,int,int) ; 
 int sqlite3KeyInfoIsWriteable (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3KeyInfoUnref (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3LocateCollSeq (TYPE_1__*,char const*) ; 
 char const* sqlite3StrBINARY ; 

KeyInfo *sqlite3KeyInfoOfIndex(Parse *pParse, Index *pIdx){
  int i;
  int nCol = pIdx->nColumn;
  int nKey = pIdx->nKeyCol;
  KeyInfo *pKey;
  if( pParse->nErr ) return 0;
  if( pIdx->uniqNotNull ){
    pKey = sqlite3KeyInfoAlloc(pParse->db, nKey, nCol-nKey);
  }else{
    pKey = sqlite3KeyInfoAlloc(pParse->db, nCol, 0);
  }
  if( pKey ){
    assert( sqlite3KeyInfoIsWriteable(pKey) );
    for(i=0; i<nCol; i++){
      const char *zColl = pIdx->azColl[i];
      pKey->aColl[i] = zColl==sqlite3StrBINARY ? 0 :
                        sqlite3LocateCollSeq(pParse, zColl);
      pKey->aSortOrder[i] = pIdx->aSortOrder[i];
    }
    if( pParse->nErr ){
      assert( pParse->rc==SQLITE_ERROR_MISSING_COLLSEQ );
      if( pIdx->bNoQuery==0 ){
        /* Deactivate the index because it contains an unknown collating
        ** sequence.  The only way to reactive the index is to reload the
        ** schema.  Adding the missing collating sequence later does not
        ** reactive the index.  The application had the chance to register
        ** the missing index using the collation-needed callback.  For
        ** simplicity, SQLite will not give the application a second chance.
        */
        pIdx->bNoQuery = 1;
        pParse->rc = SQLITE_ERROR_RETRY;
      }
      sqlite3KeyInfoUnref(pKey);
      pKey = 0;
    }
  }
  return pKey;
}