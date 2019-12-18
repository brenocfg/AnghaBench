#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* zErrMsg; } ;
struct TYPE_8__ {TYPE_2__ base; int /*<<< orphan*/  pCmd; int /*<<< orphan*/ * interp; } ;
typedef  TYPE_3__ tcl_vtab ;
typedef  scalar_t__ tRowcnt ;
struct sqlite3_index_orderby {int /*<<< orphan*/  desc; int /*<<< orphan*/  iColumn; } ;
struct sqlite3_index_constraint {int op; int /*<<< orphan*/  usable; int /*<<< orphan*/  iColumn; } ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_9__ {int nConstraint; int nOrderBy; int orderByConsumed; int idxNum; int needToFreeIdxStr; TYPE_1__* aConstraintUsage; scalar_t__ estimatedRows; void* idxStr; int /*<<< orphan*/  estimatedCost; int /*<<< orphan*/  colUsed; struct sqlite3_index_orderby* aOrderBy; struct sqlite3_index_constraint* aConstraint; } ;
typedef  TYPE_4__ sqlite3_index_info ;
typedef  scalar_t__ Tcl_WideInt ;
typedef  int /*<<< orphan*/  Tcl_Obj ;
typedef  int /*<<< orphan*/  Tcl_Interp ;
struct TYPE_6__ {int omit; int /*<<< orphan*/  argvIndex; } ;

/* Variables and functions */
 int SQLITE_ERROR ; 
#define  SQLITE_INDEX_CONSTRAINT_EQ 141 
#define  SQLITE_INDEX_CONSTRAINT_GE 140 
#define  SQLITE_INDEX_CONSTRAINT_GLOB 139 
#define  SQLITE_INDEX_CONSTRAINT_GT 138 
#define  SQLITE_INDEX_CONSTRAINT_IS 137 
#define  SQLITE_INDEX_CONSTRAINT_ISNOT 136 
#define  SQLITE_INDEX_CONSTRAINT_ISNOTNULL 135 
#define  SQLITE_INDEX_CONSTRAINT_ISNULL 134 
#define  SQLITE_INDEX_CONSTRAINT_LE 133 
#define  SQLITE_INDEX_CONSTRAINT_LIKE 132 
#define  SQLITE_INDEX_CONSTRAINT_LT 131 
#define  SQLITE_INDEX_CONSTRAINT_MATCH 130 
#define  SQLITE_INDEX_CONSTRAINT_NE 129 
#define  SQLITE_INDEX_CONSTRAINT_REGEXP 128 
 int SQLITE_OK ; 
 int /*<<< orphan*/  TCL_EVAL_GLOBAL ; 
 int TCL_OK ; 
 int /*<<< orphan*/  Tcl_DecrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Tcl_DuplicateObj (int /*<<< orphan*/ ) ; 
 int Tcl_EvalObjEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int Tcl_GetDoubleFromObj (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int Tcl_GetIntFromObj (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * Tcl_GetObjResult (int /*<<< orphan*/ *) ; 
 char const* Tcl_GetString (int /*<<< orphan*/ *) ; 
 char* Tcl_GetStringResult (int /*<<< orphan*/ *) ; 
 int Tcl_GetWideIntFromObj (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  Tcl_IncrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_ListObjAppendElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int Tcl_ListObjGetElements (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ***) ; 
 int /*<<< orphan*/ * Tcl_NewIntObj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Tcl_NewObj () ; 
 int /*<<< orphan*/ * Tcl_NewStringObj (char const*,int) ; 
 int /*<<< orphan*/ * Tcl_NewWideIntObj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (void*) ; 
 void* sqlite3_mprintf (char*,...) ; 
 scalar_t__ sqlite3_stricmp (char*,char const*) ; 

__attribute__((used)) static int tclBestIndex(sqlite3_vtab *tab, sqlite3_index_info *pIdxInfo){
  tcl_vtab *pTab = (tcl_vtab*)tab;
  Tcl_Interp *interp = pTab->interp;
  Tcl_Obj *pArg;
  Tcl_Obj *pScript;
  int ii;
  int rc = SQLITE_OK;

  pScript = Tcl_DuplicateObj(pTab->pCmd);
  Tcl_IncrRefCount(pScript);
  Tcl_ListObjAppendElement(interp, pScript, Tcl_NewStringObj("xBestIndex", -1));

  pArg = Tcl_NewObj();
  Tcl_IncrRefCount(pArg);
  for(ii=0; ii<pIdxInfo->nConstraint; ii++){
    struct sqlite3_index_constraint const *pCons = &pIdxInfo->aConstraint[ii];
    Tcl_Obj *pElem = Tcl_NewObj();
    const char *zOp = "?";

    Tcl_IncrRefCount(pElem);

    switch( pCons->op ){
      case SQLITE_INDEX_CONSTRAINT_EQ:
        zOp = "eq"; break;
      case SQLITE_INDEX_CONSTRAINT_GT:
        zOp = "gt"; break;
      case SQLITE_INDEX_CONSTRAINT_LE:
        zOp = "le"; break;
      case SQLITE_INDEX_CONSTRAINT_LT:
        zOp = "lt"; break;
      case SQLITE_INDEX_CONSTRAINT_GE:
        zOp = "ge"; break;
      case SQLITE_INDEX_CONSTRAINT_MATCH:
        zOp = "match"; break;
      case SQLITE_INDEX_CONSTRAINT_LIKE:
        zOp = "like"; break;
      case SQLITE_INDEX_CONSTRAINT_GLOB:
        zOp = "glob"; break;
      case SQLITE_INDEX_CONSTRAINT_REGEXP:
        zOp = "regexp"; break;
      case SQLITE_INDEX_CONSTRAINT_NE:
        zOp = "ne"; break;
      case SQLITE_INDEX_CONSTRAINT_ISNOT:
        zOp = "isnot"; break;
      case SQLITE_INDEX_CONSTRAINT_ISNOTNULL:
        zOp = "isnotnull"; break;
      case SQLITE_INDEX_CONSTRAINT_ISNULL:
        zOp = "isnull"; break;
      case SQLITE_INDEX_CONSTRAINT_IS:
        zOp = "is"; break;
    }

    Tcl_ListObjAppendElement(0, pElem, Tcl_NewStringObj("op", -1));
    Tcl_ListObjAppendElement(0, pElem, Tcl_NewStringObj(zOp, -1));
    Tcl_ListObjAppendElement(0, pElem, Tcl_NewStringObj("column", -1));
    Tcl_ListObjAppendElement(0, pElem, Tcl_NewIntObj(pCons->iColumn));
    Tcl_ListObjAppendElement(0, pElem, Tcl_NewStringObj("usable", -1));
    Tcl_ListObjAppendElement(0, pElem, Tcl_NewIntObj(pCons->usable));

    Tcl_ListObjAppendElement(0, pArg, pElem);
    Tcl_DecrRefCount(pElem);
  }

  Tcl_ListObjAppendElement(0, pScript, pArg);
  Tcl_DecrRefCount(pArg);

  pArg = Tcl_NewObj();
  Tcl_IncrRefCount(pArg);
  for(ii=0; ii<pIdxInfo->nOrderBy; ii++){
    struct sqlite3_index_orderby const *pOrder = &pIdxInfo->aOrderBy[ii];
    Tcl_Obj *pElem = Tcl_NewObj();
    Tcl_IncrRefCount(pElem);

    Tcl_ListObjAppendElement(0, pElem, Tcl_NewStringObj("column", -1));
    Tcl_ListObjAppendElement(0, pElem, Tcl_NewIntObj(pOrder->iColumn));
    Tcl_ListObjAppendElement(0, pElem, Tcl_NewStringObj("desc", -1));
    Tcl_ListObjAppendElement(0, pElem, Tcl_NewIntObj(pOrder->desc));

    Tcl_ListObjAppendElement(0, pArg, pElem);
    Tcl_DecrRefCount(pElem);
  }

  Tcl_ListObjAppendElement(0, pScript, pArg);
  Tcl_DecrRefCount(pArg);

  Tcl_ListObjAppendElement(0, pScript, Tcl_NewWideIntObj(pIdxInfo->colUsed));

  rc = Tcl_EvalObjEx(interp, pScript, TCL_EVAL_GLOBAL);
  Tcl_DecrRefCount(pScript);
  if( rc!=TCL_OK ){
    const char *zErr = Tcl_GetStringResult(interp);
    rc = SQLITE_ERROR;
    pTab->base.zErrMsg = sqlite3_mprintf("%s", zErr);
  }else{
    /* Analyze the scripts return value. The return value should be a tcl 
    ** list object with an even number of elements. The first element of each
    ** pair must be one of:
    ** 
    **   "orderby"          (value of orderByConsumed flag)
    **   "cost"             (value of estimatedCost field)
    **   "rows"             (value of estimatedRows field)
    **   "use"              (index of used constraint in aConstraint[])
    **   "idxnum"           (value of idxNum field)
    **   "idxstr"           (value of idxStr field)
    **   "omit"             (index of omitted constraint in aConstraint[])
    */
    Tcl_Obj *pRes = Tcl_GetObjResult(interp);
    Tcl_Obj **apElem = 0;
    int nElem;
    rc = Tcl_ListObjGetElements(interp, pRes, &nElem, &apElem);
    if( rc!=TCL_OK ){
      const char *zErr = Tcl_GetStringResult(interp);
      rc = SQLITE_ERROR;
      pTab->base.zErrMsg = sqlite3_mprintf("%s", zErr);
    }else{
      int iArgv = 1;
      for(ii=0; rc==SQLITE_OK && ii<nElem; ii+=2){
        const char *zCmd = Tcl_GetString(apElem[ii]);
        Tcl_Obj *p = apElem[ii+1];
        if( sqlite3_stricmp("cost", zCmd)==0 ){
          rc = Tcl_GetDoubleFromObj(interp, p, &pIdxInfo->estimatedCost);
        }else
        if( sqlite3_stricmp("orderby", zCmd)==0 ){
          rc = Tcl_GetIntFromObj(interp, p, &pIdxInfo->orderByConsumed);
        }else
        if( sqlite3_stricmp("idxnum", zCmd)==0 ){
          rc = Tcl_GetIntFromObj(interp, p, &pIdxInfo->idxNum);
        }else
        if( sqlite3_stricmp("idxstr", zCmd)==0 ){
          sqlite3_free(pIdxInfo->idxStr);
          pIdxInfo->idxStr = sqlite3_mprintf("%s", Tcl_GetString(p));
          pIdxInfo->needToFreeIdxStr = 1;
        }else
        if( sqlite3_stricmp("rows", zCmd)==0 ){
          Tcl_WideInt x = 0;
          rc = Tcl_GetWideIntFromObj(interp, p, &x);
          pIdxInfo->estimatedRows = (tRowcnt)x;
        }else
        if( sqlite3_stricmp("use", zCmd)==0 
         || sqlite3_stricmp("omit", zCmd)==0 
        ){
          int iCons;
          rc = Tcl_GetIntFromObj(interp, p, &iCons);
          if( rc==SQLITE_OK ){
            if( iCons<0 || iCons>=pIdxInfo->nConstraint ){
              rc = SQLITE_ERROR;
              pTab->base.zErrMsg = sqlite3_mprintf("unexpected: %d", iCons);
            }else{
              int bOmit = (zCmd[0]=='o' || zCmd[0]=='O');
              pIdxInfo->aConstraintUsage[iCons].argvIndex = iArgv++;
              pIdxInfo->aConstraintUsage[iCons].omit = bOmit;
            }
          }
        }else{
          rc = SQLITE_ERROR;
          pTab->base.zErrMsg = sqlite3_mprintf("unexpected: %s", zCmd);
        }
        if( rc!=SQLITE_OK && pTab->base.zErrMsg==0 ){
          const char *zErr = Tcl_GetStringResult(interp);
          pTab->base.zErrMsg = sqlite3_mprintf("%s", zErr);
        }
      }
    }
  }

  return rc;
}