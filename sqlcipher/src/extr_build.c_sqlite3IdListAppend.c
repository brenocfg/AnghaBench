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
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  Token ;
struct TYPE_13__ {scalar_t__ zName; } ;
struct TYPE_12__ {TYPE_9__* a; int /*<<< orphan*/  nId; } ;
struct TYPE_11__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ Parse ;
typedef  TYPE_2__ IdList ;

/* Variables and functions */
 scalar_t__ IN_RENAME_OBJECT ; 
 TYPE_9__* sqlite3ArrayAllocate (int /*<<< orphan*/ *,TYPE_9__*,int,int /*<<< orphan*/ *,int*) ; 
 TYPE_2__* sqlite3DbMallocZero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3IdListDelete (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ sqlite3NameFromToken (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3RenameTokenMap (TYPE_1__*,void*,int /*<<< orphan*/ *) ; 

IdList *sqlite3IdListAppend(Parse *pParse, IdList *pList, Token *pToken){
  sqlite3 *db = pParse->db;
  int i;
  if( pList==0 ){
    pList = sqlite3DbMallocZero(db, sizeof(IdList) );
    if( pList==0 ) return 0;
  }
  pList->a = sqlite3ArrayAllocate(
      db,
      pList->a,
      sizeof(pList->a[0]),
      &pList->nId,
      &i
  );
  if( i<0 ){
    sqlite3IdListDelete(db, pList);
    return 0;
  }
  pList->a[i].zName = sqlite3NameFromToken(db, pToken);
  if( IN_RENAME_OBJECT && pList->a[i].zName ){
    sqlite3RenameTokenMap(pParse, (void*)pList->a[i].zName, pToken);
  }
  return pList;
}