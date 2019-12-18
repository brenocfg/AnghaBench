#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_10__ {scalar_t__ pPartition; scalar_t__ pOrderBy; scalar_t__ bImplicitFrame; scalar_t__ zBase; } ;
typedef  TYPE_1__ Window ;
struct TYPE_11__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_2__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (TYPE_2__*,char*,char const*,scalar_t__) ; 
 void* sqlite3ExprListDup (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* windowFind (TYPE_2__*,TYPE_1__*,scalar_t__) ; 

void sqlite3WindowChain(Parse *pParse, Window *pWin, Window *pList){
  if( pWin->zBase ){
    sqlite3 *db = pParse->db;
    Window *pExist = windowFind(pParse, pList, pWin->zBase);
    if( pExist ){
      const char *zErr = 0;
      /* Check for errors */
      if( pWin->pPartition ){
        zErr = "PARTITION clause";
      }else if( pExist->pOrderBy && pWin->pOrderBy ){
        zErr = "ORDER BY clause";
      }else if( pExist->bImplicitFrame==0 ){
        zErr = "frame specification";
      }
      if( zErr ){
        sqlite3ErrorMsg(pParse, 
            "cannot override %s of window: %s", zErr, pWin->zBase
        );
      }else{
        pWin->pPartition = sqlite3ExprListDup(db, pExist->pPartition, 0);
        if( pExist->pOrderBy ){
          assert( pWin->pOrderBy==0 );
          pWin->pOrderBy = sqlite3ExprListDup(db, pExist->pOrderBy, 0);
        }
        sqlite3DbFree(db, pWin->zBase);
        pWin->zBase = 0;
      }
    }
  }
}