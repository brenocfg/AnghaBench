#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ nPage; scalar_t__ pHasContent; } ;
typedef  scalar_t__ Pgno ;
typedef  TYPE_1__ BtShared ;

/* Variables and functions */
 int SQLITE_NOMEM_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3BitvecCreate (scalar_t__) ; 
 int sqlite3BitvecSet (scalar_t__,scalar_t__) ; 
 scalar_t__ sqlite3BitvecSize (scalar_t__) ; 

__attribute__((used)) static int btreeSetHasContent(BtShared *pBt, Pgno pgno){
  int rc = SQLITE_OK;
  if( !pBt->pHasContent ){
    assert( pgno<=pBt->nPage );
    pBt->pHasContent = sqlite3BitvecCreate(pBt->nPage);
    if( !pBt->pHasContent ){
      rc = SQLITE_NOMEM_BKPT;
    }
  }
  if( rc==SQLITE_OK && pgno<=sqlite3BitvecSize(pBt->pHasContent) ){
    rc = sqlite3BitvecSet(pBt->pHasContent, pgno);
  }
  return rc;
}