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
struct TYPE_5__ {int /*<<< orphan*/ * interp; } ;
typedef  TYPE_1__ tclvar_vtab ;
struct TYPE_6__ {int /*<<< orphan*/  i2; int /*<<< orphan*/  pList2; int /*<<< orphan*/  i1; int /*<<< orphan*/  pList1; } ;
typedef  TYPE_2__ tclvar_cursor ;
struct TYPE_7__ {scalar_t__ pVtab; } ;
typedef  TYPE_3__ sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  Tcl_Obj ;
typedef  int /*<<< orphan*/  Tcl_Interp ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  TCL_GLOBAL_ONLY ; 
 char const* Tcl_GetString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Tcl_GetVar2Ex (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_ListObjIndex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sqlite3_free ; 
 char* sqlite3_mprintf (char*,char const*,char const*) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tclvarColumn(sqlite3_vtab_cursor *cur, sqlite3_context *ctx, int i){
  Tcl_Obj *p1;
  Tcl_Obj *p2;
  const char *z1; 
  const char *z2 = "";
  tclvar_cursor *pCur = (tclvar_cursor*)cur;
  Tcl_Interp *interp = ((tclvar_vtab *)cur->pVtab)->interp;

  Tcl_ListObjIndex(interp, pCur->pList1, pCur->i1, &p1);
  Tcl_ListObjIndex(interp, pCur->pList2, pCur->i2, &p2);
  z1 = Tcl_GetString(p1);
  if( p2 ){
    z2 = Tcl_GetString(p2);
  }
  switch (i) {
    case 0: {
      sqlite3_result_text(ctx, z1, -1, SQLITE_TRANSIENT);
      break;
    }
    case 1: {
      sqlite3_result_text(ctx, z2, -1, SQLITE_TRANSIENT);
      break;
    }
    case 2: {
      Tcl_Obj *pVal = Tcl_GetVar2Ex(interp, z1, *z2?z2:0, TCL_GLOBAL_ONLY);
      sqlite3_result_text(ctx, Tcl_GetString(pVal), -1, SQLITE_TRANSIENT);
      break;
    }
    case 3: {
      char *z3;
      if( p2 ){
        z3 = sqlite3_mprintf("%s(%s)", z1, z2);
        sqlite3_result_text(ctx, z3, -1, sqlite3_free);
      }else{
        sqlite3_result_text(ctx, z1, -1, SQLITE_TRANSIENT);
      }
      break;
    }
  }
  return SQLITE_OK;
}