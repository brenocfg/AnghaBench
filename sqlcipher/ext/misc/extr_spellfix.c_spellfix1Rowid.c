#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
struct TYPE_4__ {size_t iRow; TYPE_1__* a; scalar_t__ pFullScan; } ;
typedef  TYPE_2__ spellfix1_cursor ;
struct TYPE_3__ {int /*<<< orphan*/  iRowid; } ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  sqlite3_column_int64 (scalar_t__,int) ; 

__attribute__((used)) static int spellfix1Rowid(sqlite3_vtab_cursor *cur, sqlite_int64 *pRowid){
  spellfix1_cursor *pCur = (spellfix1_cursor*)cur;
  if( pCur->pFullScan ){
    *pRowid = sqlite3_column_int64(pCur->pFullScan, 4);
  }else{
    *pRowid = pCur->a[pCur->iRow].iRowid;
  }
  return SQLITE_OK;
}