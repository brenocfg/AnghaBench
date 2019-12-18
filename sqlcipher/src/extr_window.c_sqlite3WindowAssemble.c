#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  zBase; int /*<<< orphan*/ * pOrderBy; int /*<<< orphan*/ * pPartition; } ;
typedef  TYPE_1__ Window ;
struct TYPE_9__ {int /*<<< orphan*/  n; int /*<<< orphan*/  z; } ;
typedef  TYPE_2__ Token ;
struct TYPE_10__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_3__ Parse ;
typedef  int /*<<< orphan*/  ExprList ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3DbStrNDup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprListDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

Window *sqlite3WindowAssemble(
  Parse *pParse, 
  Window *pWin, 
  ExprList *pPartition, 
  ExprList *pOrderBy, 
  Token *pBase
){
  if( pWin ){
    pWin->pPartition = pPartition;
    pWin->pOrderBy = pOrderBy;
    if( pBase ){
      pWin->zBase = sqlite3DbStrNDup(pParse->db, pBase->z, pBase->n);
    }
  }else{
    sqlite3ExprListDelete(pParse->db, pPartition);
    sqlite3ExprListDelete(pParse->db, pOrderBy);
  }
  return pWin;
}