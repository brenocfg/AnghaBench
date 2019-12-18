#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nParm; struct TYPE_7__* pNext; struct TYPE_7__* pPrev; int /*<<< orphan*/ * apParm; } ;
struct TYPE_6__ {scalar_t__ maxStmt; scalar_t__ nStmt; TYPE_2__* stmtLast; TYPE_2__* stmtList; } ;
typedef  TYPE_1__ SqliteDb ;
typedef  TYPE_2__ SqlPreparedStmt ;

/* Variables and functions */
 int /*<<< orphan*/  Tcl_DecrRefCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dbFreeStmt (TYPE_2__*) ; 

__attribute__((used)) static void dbReleaseStmt(
  SqliteDb *pDb,                  /* Database handle */
  SqlPreparedStmt *pPreStmt,      /* Prepared statement handle to release */
  int discard                     /* True to delete (not cache) the pPreStmt */
){
  int i;

  /* Free the bound string and blob parameters */
  for(i=0; i<pPreStmt->nParm; i++){
    Tcl_DecrRefCount(pPreStmt->apParm[i]);
  }
  pPreStmt->nParm = 0;

  if( pDb->maxStmt<=0 || discard ){
    /* If the cache is turned off, deallocated the statement */
    dbFreeStmt(pPreStmt);
  }else{
    /* Add the prepared statement to the beginning of the cache list. */
    pPreStmt->pNext = pDb->stmtList;
    pPreStmt->pPrev = 0;
    if( pDb->stmtList ){
     pDb->stmtList->pPrev = pPreStmt;
    }
    pDb->stmtList = pPreStmt;
    if( pDb->stmtLast==0 ){
      assert( pDb->nStmt==0 );
      pDb->stmtLast = pPreStmt;
    }else{
      assert( pDb->nStmt>0 );
    }
    pDb->nStmt++;

    /* If we have too many statement in cache, remove the surplus from
    ** the end of the cache list.  */
    while( pDb->nStmt>pDb->maxStmt ){
      SqlPreparedStmt *pLast = pDb->stmtLast;
      pDb->stmtLast = pLast->pPrev;
      pDb->stmtLast->pNext = 0;
      pDb->nStmt--;
      dbFreeStmt(pLast);
    }
  }
}