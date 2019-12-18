#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct SrcList_item {int iCursor; void* zDatabase; void* zName; } ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_15__ {scalar_t__ z; } ;
typedef  TYPE_1__ Token ;
struct TYPE_17__ {int /*<<< orphan*/ * db; } ;
struct TYPE_16__ {int nAlloc; int nSrc; struct SrcList_item* a; } ;
typedef  TYPE_2__ SrcList ;
typedef  TYPE_3__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (struct SrcList_item*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* sqlite3DbMallocRawNN (int /*<<< orphan*/ *,int) ; 
 void* sqlite3NameFromToken (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3SrcListDelete (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* sqlite3SrcListEnlarge (TYPE_3__*,TYPE_2__*,int,int) ; 

SrcList *sqlite3SrcListAppend(
  Parse *pParse,      /* Parsing context, in which errors are reported */
  SrcList *pList,     /* Append to this SrcList. NULL creates a new SrcList */
  Token *pTable,      /* Table to append */
  Token *pDatabase    /* Database of the table */
){
  struct SrcList_item *pItem;
  sqlite3 *db;
  assert( pDatabase==0 || pTable!=0 );  /* Cannot have C without B */
  assert( pParse!=0 );
  assert( pParse->db!=0 );
  db = pParse->db;
  if( pList==0 ){
    pList = sqlite3DbMallocRawNN(pParse->db, sizeof(SrcList) );
    if( pList==0 ) return 0;
    pList->nAlloc = 1;
    pList->nSrc = 1;
    memset(&pList->a[0], 0, sizeof(pList->a[0]));
    pList->a[0].iCursor = -1;
  }else{
    SrcList *pNew = sqlite3SrcListEnlarge(pParse, pList, 1, pList->nSrc);
    if( pNew==0 ){
      sqlite3SrcListDelete(db, pList);
      return 0;
    }else{
      pList = pNew;
    }
  }
  pItem = &pList->a[pList->nSrc-1];
  if( pDatabase && pDatabase->z==0 ){
    pDatabase = 0;
  }
  if( pDatabase ){
    pItem->zName = sqlite3NameFromToken(db, pDatabase);
    pItem->zDatabase = sqlite3NameFromToken(db, pTable);
  }else{
    pItem->zName = sqlite3NameFromToken(db, pTable);
    pItem->zDatabase = 0;
  }
  return pList;
}