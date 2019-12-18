#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* pWrite; TYPE_3__* pTable; } ;
typedef  TYPE_1__ sqlite3expert ;
struct TYPE_7__ {char* zName; struct TYPE_7__* pNext; } ;
struct TYPE_6__ {int eOp; struct TYPE_6__* pNext; TYPE_3__* pTab; } ;
typedef  TYPE_2__ IdxWrite ;
typedef  TYPE_3__ IdxTable ;

/* Variables and functions */
 int SQLITE_DELETE ; 
 int SQLITE_INSERT ; 
 int SQLITE_OK ; 
 int SQLITE_UPDATE ; 
 TYPE_2__* idxMalloc (int*,int) ; 
 scalar_t__ sqlite3_stricmp (char const*,char*) ; 

__attribute__((used)) static int idxAuthCallback(
  void *pCtx,
  int eOp,
  const char *z3,
  const char *z4,
  const char *zDb,
  const char *zTrigger
){
  int rc = SQLITE_OK;
  (void)z4;
  (void)zTrigger;
  if( eOp==SQLITE_INSERT || eOp==SQLITE_UPDATE || eOp==SQLITE_DELETE ){
    if( sqlite3_stricmp(zDb, "main")==0 ){
      sqlite3expert *p = (sqlite3expert*)pCtx;
      IdxTable *pTab;
      for(pTab=p->pTable; pTab; pTab=pTab->pNext){
        if( 0==sqlite3_stricmp(z3, pTab->zName) ) break;
      }
      if( pTab ){
        IdxWrite *pWrite;
        for(pWrite=p->pWrite; pWrite; pWrite=pWrite->pNext){
          if( pWrite->pTab==pTab && pWrite->eOp==eOp ) break;
        }
        if( pWrite==0 ){
          pWrite = idxMalloc(&rc, sizeof(IdxWrite));
          if( rc==SQLITE_OK ){
            pWrite->pTab = pTab;
            pWrite->eOp = eOp;
            pWrite->pNext = p->pWrite;
            p->pWrite = pWrite;
          }
        }
      }
    }
  }
  return rc;
}