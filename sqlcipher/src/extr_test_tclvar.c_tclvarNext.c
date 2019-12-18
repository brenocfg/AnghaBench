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
struct TYPE_7__ {int i1; int /*<<< orphan*/  pList1; } ;
typedef  TYPE_2__ tclvar_cursor ;
struct TYPE_8__ {scalar_t__ pVtab; } ;
typedef  TYPE_3__ sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  Tcl_Obj ;
typedef  int /*<<< orphan*/  Tcl_Interp ;

/* Variables and functions */
 int /*<<< orphan*/  Tcl_ListObjIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  Tcl_ListObjLength (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int next2 (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tclvarNext(sqlite3_vtab_cursor *cur){
  Tcl_Obj *pObj;
  int n = 0;
  int ok = 0;

  tclvar_cursor *pCur = (tclvar_cursor *)cur;
  Tcl_Interp *interp = ((tclvar_vtab *)(cur->pVtab))->interp;

  Tcl_ListObjLength(0, pCur->pList1, &n);
  while( !ok && pCur->i1<n ){
    Tcl_ListObjIndex(0, pCur->pList1, pCur->i1, &pObj);
    ok = next2(interp, pCur, pObj);
    if( !ok ){
      pCur->i1++;
    }
  }

  return 0;
}