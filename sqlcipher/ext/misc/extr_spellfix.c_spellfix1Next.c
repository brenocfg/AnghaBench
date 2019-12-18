#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
struct TYPE_2__ {scalar_t__ iRow; scalar_t__ nRow; scalar_t__ pFullScan; } ;
typedef  TYPE_1__ spellfix1_cursor ;

/* Variables and functions */
 int SQLITE_DONE ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int sqlite3_step (scalar_t__) ; 

__attribute__((used)) static int spellfix1Next(sqlite3_vtab_cursor *cur){
  spellfix1_cursor *pCur = (spellfix1_cursor *)cur;
  int rc = SQLITE_OK;
  if( pCur->iRow < pCur->nRow ){
    if( pCur->pFullScan ){
      rc = sqlite3_step(pCur->pFullScan);
      if( rc!=SQLITE_ROW ) pCur->iRow = pCur->nRow;
      if( rc==SQLITE_ROW || rc==SQLITE_DONE ) rc = SQLITE_OK;
    }else{
      pCur->iRow++;
    }
  }
  return rc;
}