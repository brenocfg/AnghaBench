#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct ExprList_item {int /*<<< orphan*/  sortOrder; int /*<<< orphan*/  pExpr; } ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_12__ {int nExpr; struct ExprList_item* a; } ;
struct TYPE_11__ {int /*<<< orphan*/ * aSortOrder; int /*<<< orphan*/ * aColl; } ;
struct TYPE_10__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ Parse ;
typedef  TYPE_2__ KeyInfo ;
typedef  TYPE_3__ ExprList ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprNNCollSeq (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* sqlite3KeyInfoAlloc (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  sqlite3KeyInfoIsWriteable (TYPE_2__*) ; 

KeyInfo *sqlite3KeyInfoFromExprList(
  Parse *pParse,       /* Parsing context */
  ExprList *pList,     /* Form the KeyInfo object from this ExprList */
  int iStart,          /* Begin with this column of pList */
  int nExtra           /* Add this many extra columns to the end */
){
  int nExpr;
  KeyInfo *pInfo;
  struct ExprList_item *pItem;
  sqlite3 *db = pParse->db;
  int i;

  nExpr = pList->nExpr;
  pInfo = sqlite3KeyInfoAlloc(db, nExpr-iStart, nExtra+1);
  if( pInfo ){
    assert( sqlite3KeyInfoIsWriteable(pInfo) );
    for(i=iStart, pItem=pList->a+iStart; i<nExpr; i++, pItem++){
      pInfo->aColl[i-iStart] = sqlite3ExprNNCollSeq(pParse, pItem->pExpr);
      pInfo->aSortOrder[i-iStart] = pItem->sortOrder;
    }
  }
  return pInfo;
}