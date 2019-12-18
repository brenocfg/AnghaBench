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
struct TYPE_3__ {scalar_t__ pList2; scalar_t__ pList1; } ;
typedef  TYPE_1__ tclvar_cursor ;
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  Tcl_DecrRefCount (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 

__attribute__((used)) static int tclvarClose(sqlite3_vtab_cursor *cur){
  tclvar_cursor *pCur = (tclvar_cursor *)cur;
  if( pCur->pList1 ){
    Tcl_DecrRefCount(pCur->pList1);
  }
  if( pCur->pList2 ){
    Tcl_DecrRefCount(pCur->pList2);
  }
  sqlite3_free(pCur);
  return SQLITE_OK;
}