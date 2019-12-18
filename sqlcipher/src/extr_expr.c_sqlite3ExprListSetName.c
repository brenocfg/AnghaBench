#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct ExprList_item {scalar_t__ zName; } ;
struct TYPE_10__ {int /*<<< orphan*/  n; int /*<<< orphan*/  z; } ;
typedef  TYPE_1__ Token ;
struct TYPE_13__ {scalar_t__ mallocFailed; } ;
struct TYPE_12__ {int nExpr; struct ExprList_item* a; } ;
struct TYPE_11__ {TYPE_9__* db; } ;
typedef  TYPE_2__ Parse ;
typedef  TYPE_3__ ExprList ;

/* Variables and functions */
 scalar_t__ IN_RENAME_OBJECT ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3DbStrNDup (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3Dequote (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3RenameTokenMap (TYPE_2__*,void*,TYPE_1__*) ; 

void sqlite3ExprListSetName(
  Parse *pParse,          /* Parsing context */
  ExprList *pList,        /* List to which to add the span. */
  Token *pName,           /* Name to be added */
  int dequote             /* True to cause the name to be dequoted */
){
  assert( pList!=0 || pParse->db->mallocFailed!=0 );
  if( pList ){
    struct ExprList_item *pItem;
    assert( pList->nExpr>0 );
    pItem = &pList->a[pList->nExpr-1];
    assert( pItem->zName==0 );
    pItem->zName = sqlite3DbStrNDup(pParse->db, pName->z, pName->n);
    if( dequote ) sqlite3Dequote(pItem->zName);
    if( IN_RENAME_OBJECT ){
      sqlite3RenameTokenMap(pParse, (void*)pItem->zName, pName);
    }
  }
}