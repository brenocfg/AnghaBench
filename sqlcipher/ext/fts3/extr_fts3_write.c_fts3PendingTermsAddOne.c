#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  nPendingData; int /*<<< orphan*/  iPrevDocid; } ;
struct TYPE_8__ {scalar_t__ nData; } ;
typedef  TYPE_1__ PendingList ;
typedef  TYPE_2__ Fts3Table ;
typedef  int /*<<< orphan*/  Fts3HashElem ;
typedef  int /*<<< orphan*/  Fts3Hash ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ fts3HashFind (int /*<<< orphan*/ *,char const*,int) ; 
 TYPE_1__* fts3HashInsert (int /*<<< orphan*/ *,char const*,int,TYPE_1__*) ; 
 scalar_t__ fts3PendingListAppend (TYPE_1__**,int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 

__attribute__((used)) static int fts3PendingTermsAddOne(
  Fts3Table *p,
  int iCol,
  int iPos,
  Fts3Hash *pHash,                /* Pending terms hash table to add entry to */
  const char *zToken,
  int nToken
){
  PendingList *pList;
  int rc = SQLITE_OK;

  pList = (PendingList *)fts3HashFind(pHash, zToken, nToken);
  if( pList ){
    p->nPendingData -= (pList->nData + nToken + sizeof(Fts3HashElem));
  }
  if( fts3PendingListAppend(&pList, p->iPrevDocid, iCol, iPos, &rc) ){
    if( pList==fts3HashInsert(pHash, zToken, nToken, pList) ){
      /* Malloc failed while inserting the new entry. This can only 
      ** happen if there was no previous entry for this token.
      */
      assert( 0==fts3HashFind(pHash, zToken, nToken) );
      sqlite3_free(pList);
      rc = SQLITE_NOMEM;
    }
  }
  if( rc==SQLITE_OK ){
    p->nPendingData += (pList->nData + nToken + sizeof(Fts3HashElem));
  }
  return rc;
}