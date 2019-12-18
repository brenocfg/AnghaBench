#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * interp; } ;
typedef  TYPE_1__ tclvar_vtab ;
struct TYPE_7__ {int /*<<< orphan*/ * pList1; scalar_t__ i2; scalar_t__ i1; int /*<<< orphan*/ * pList2; } ;
typedef  TYPE_2__ tclvar_cursor ;
struct TYPE_8__ {scalar_t__ pVtab; } ;
typedef  TYPE_3__ sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  Tcl_Obj ;
typedef  int /*<<< orphan*/  Tcl_Interp ;

/* Variables and functions */
#define  TCLVAR_NAME_EQ 132 
#define  TCLVAR_NAME_MATCH 131 
#define  TCLVAR_VALUE_GLOB 130 
#define  TCLVAR_VALUE_LIKE 129 
#define  TCLVAR_VALUE_REGEXP 128 
 int /*<<< orphan*/  TCL_EVAL_GLOBAL ; 
 int /*<<< orphan*/  Tcl_DecrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_EvalObjEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Tcl_GetObjResult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_IncrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_ListObjAppendElement (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Tcl_NewStringObj (char const*,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 
 int tclvarNext (TYPE_3__*) ; 

__attribute__((used)) static int tclvarFilter(
  sqlite3_vtab_cursor *pVtabCursor, 
  int idxNum, const char *idxStr,
  int argc, sqlite3_value **argv
){
  tclvar_cursor *pCur = (tclvar_cursor *)pVtabCursor;
  Tcl_Interp *interp = ((tclvar_vtab *)(pVtabCursor->pVtab))->interp;
  Tcl_Obj *p = Tcl_NewStringObj("tclvar_filter_cmd", -1);

  const char *zEq = "";
  const char *zMatch = "";
  const char *zGlob = "";
  const char *zRegexp = "";
  const char *zLike = "";
  int i;

  for(i=0; idxStr[i]; i++){
    switch( idxStr[i] ){
      case TCLVAR_NAME_EQ:
        zEq = (const char*)sqlite3_value_text(argv[i]);
        break;
      case TCLVAR_NAME_MATCH:
        zMatch = (const char*)sqlite3_value_text(argv[i]);
        break;
      case TCLVAR_VALUE_GLOB:
        zGlob = (const char*)sqlite3_value_text(argv[i]);
        break;
      case TCLVAR_VALUE_REGEXP:
        zRegexp = (const char*)sqlite3_value_text(argv[i]);
        break;
      case TCLVAR_VALUE_LIKE:
        zLike = (const char*)sqlite3_value_text(argv[i]);
        break;
      default:
        assert( 0 );
    }
  }

  Tcl_IncrRefCount(p);
  Tcl_ListObjAppendElement(0, p, Tcl_NewStringObj(zEq, -1));
  Tcl_ListObjAppendElement(0, p, Tcl_NewStringObj(zMatch, -1));
  Tcl_ListObjAppendElement(0, p, Tcl_NewStringObj(zGlob, -1));
  Tcl_ListObjAppendElement(0, p, Tcl_NewStringObj(zRegexp, -1));
  Tcl_ListObjAppendElement(0, p, Tcl_NewStringObj(zLike, -1));

  Tcl_EvalObjEx(interp, p, TCL_EVAL_GLOBAL);
  if( pCur->pList1 ){
    Tcl_DecrRefCount(pCur->pList1);
  }
  if( pCur->pList2 ){
    Tcl_DecrRefCount(pCur->pList2);
    pCur->pList2 = 0;
  }
  pCur->i1 = 0;
  pCur->i2 = 0;
  pCur->pList1 = Tcl_GetObjResult(interp);
  Tcl_IncrRefCount(pCur->pList1);

  Tcl_DecrRefCount(p);
  return tclvarNext(pVtabCursor);
}