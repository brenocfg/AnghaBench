#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char u8 ;
typedef  int sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  Tcl_WideInt ;
struct TYPE_28__ {scalar_t__ bytes; TYPE_2__* typePtr; } ;
typedef  TYPE_3__ Tcl_Obj ;
struct TYPE_29__ {int eType; int /*<<< orphan*/  interp; int /*<<< orphan*/  useEvalObjv; TYPE_1__* pDb; TYPE_3__* pScript; } ;
struct TYPE_27__ {char* name; } ;
struct TYPE_26__ {char* zNull; } ;
typedef  TYPE_4__ SqlFunc ;

/* Variables and functions */
#define  SQLITE_BLOB 131 
#define  SQLITE_FLOAT 130 
#define  SQLITE_INTEGER 129 
#define  SQLITE_NULL 128 
 int SQLITE_TEXT ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  TCL_EVAL_DIRECT ; 
 int /*<<< orphan*/  TCL_OK ; 
 int TCL_RETURN ; 
 int /*<<< orphan*/  Tcl_DecrRefCount (TYPE_3__*) ; 
 int Tcl_EvalObjEx (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 unsigned char* Tcl_GetByteArrayFromObj (TYPE_3__*,int*) ; 
 int /*<<< orphan*/  Tcl_GetDoubleFromObj (int /*<<< orphan*/ ,TYPE_3__*,double*) ; 
 TYPE_3__* Tcl_GetObjResult (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_GetString (TYPE_3__*) ; 
 scalar_t__ Tcl_GetStringFromObj (TYPE_3__*,int*) ; 
 int /*<<< orphan*/  Tcl_GetStringResult (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_GetWideIntFromObj (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_IncrRefCount (TYPE_3__*) ; 
 int Tcl_ListObjAppendElement (int /*<<< orphan*/ ,TYPE_3__*,TYPE_3__*) ; 
 scalar_t__ Tcl_ListObjGetElements (int /*<<< orphan*/ ,TYPE_3__*,int*,TYPE_3__***) ; 
 TYPE_3__* Tcl_NewByteArrayObj (int /*<<< orphan*/ ,int) ; 
 TYPE_3__* Tcl_NewDoubleObj (double) ; 
 TYPE_3__* Tcl_NewIntObj (int) ; 
 TYPE_3__* Tcl_NewListObj (int,TYPE_3__**) ; 
 TYPE_3__* Tcl_NewStringObj (char*,int) ; 
 TYPE_3__* Tcl_NewWideIntObj (int) ; 
 int /*<<< orphan*/  sqlite3_result_blob (int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_double (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_result_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 TYPE_4__* sqlite3_user_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_blob (int /*<<< orphan*/ *) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 double sqlite3_value_double (int /*<<< orphan*/ *) ; 
 int sqlite3_value_int64 (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 
 int sqlite3_value_type (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void tclSqlFunc(sqlite3_context *context, int argc, sqlite3_value**argv){
  SqlFunc *p = sqlite3_user_data(context);
  Tcl_Obj *pCmd;
  int i;
  int rc;

  if( argc==0 ){
    /* If there are no arguments to the function, call Tcl_EvalObjEx on the
    ** script object directly.  This allows the TCL compiler to generate
    ** bytecode for the command on the first invocation and thus make
    ** subsequent invocations much faster. */
    pCmd = p->pScript;
    Tcl_IncrRefCount(pCmd);
    rc = Tcl_EvalObjEx(p->interp, pCmd, 0);
    Tcl_DecrRefCount(pCmd);
  }else{
    /* If there are arguments to the function, make a shallow copy of the
    ** script object, lappend the arguments, then evaluate the copy.
    **
    ** By "shallow" copy, we mean only the outer list Tcl_Obj is duplicated.
    ** The new Tcl_Obj contains pointers to the original list elements.
    ** That way, when Tcl_EvalObjv() is run and shimmers the first element
    ** of the list to tclCmdNameType, that alternate representation will
    ** be preserved and reused on the next invocation.
    */
    Tcl_Obj **aArg;
    int nArg;
    if( Tcl_ListObjGetElements(p->interp, p->pScript, &nArg, &aArg) ){
      sqlite3_result_error(context, Tcl_GetStringResult(p->interp), -1);
      return;
    }
    pCmd = Tcl_NewListObj(nArg, aArg);
    Tcl_IncrRefCount(pCmd);
    for(i=0; i<argc; i++){
      sqlite3_value *pIn = argv[i];
      Tcl_Obj *pVal;

      /* Set pVal to contain the i'th column of this row. */
      switch( sqlite3_value_type(pIn) ){
        case SQLITE_BLOB: {
          int bytes = sqlite3_value_bytes(pIn);
          pVal = Tcl_NewByteArrayObj(sqlite3_value_blob(pIn), bytes);
          break;
        }
        case SQLITE_INTEGER: {
          sqlite_int64 v = sqlite3_value_int64(pIn);
          if( v>=-2147483647 && v<=2147483647 ){
            pVal = Tcl_NewIntObj((int)v);
          }else{
            pVal = Tcl_NewWideIntObj(v);
          }
          break;
        }
        case SQLITE_FLOAT: {
          double r = sqlite3_value_double(pIn);
          pVal = Tcl_NewDoubleObj(r);
          break;
        }
        case SQLITE_NULL: {
          pVal = Tcl_NewStringObj(p->pDb->zNull, -1);
          break;
        }
        default: {
          int bytes = sqlite3_value_bytes(pIn);
          pVal = Tcl_NewStringObj((char *)sqlite3_value_text(pIn), bytes);
          break;
        }
      }
      rc = Tcl_ListObjAppendElement(p->interp, pCmd, pVal);
      if( rc ){
        Tcl_DecrRefCount(pCmd);
        sqlite3_result_error(context, Tcl_GetStringResult(p->interp), -1);
        return;
      }
    }
    if( !p->useEvalObjv ){
      /* Tcl_EvalObjEx() will automatically call Tcl_EvalObjv() if pCmd
      ** is a list without a string representation.  To prevent this from
      ** happening, make sure pCmd has a valid string representation */
      Tcl_GetString(pCmd);
    }
    rc = Tcl_EvalObjEx(p->interp, pCmd, TCL_EVAL_DIRECT);
    Tcl_DecrRefCount(pCmd);
  }

  if( rc && rc!=TCL_RETURN ){
    sqlite3_result_error(context, Tcl_GetStringResult(p->interp), -1);
  }else{
    Tcl_Obj *pVar = Tcl_GetObjResult(p->interp);
    int n;
    u8 *data;
    const char *zType = (pVar->typePtr ? pVar->typePtr->name : "");
    char c = zType[0];
    int eType = p->eType;

    if( eType==SQLITE_NULL ){
      if( c=='b' && strcmp(zType,"bytearray")==0 && pVar->bytes==0 ){
        /* Only return a BLOB type if the Tcl variable is a bytearray and
        ** has no string representation. */
        eType = SQLITE_BLOB;
      }else if( (c=='b' && strcmp(zType,"boolean")==0)
             || (c=='w' && strcmp(zType,"wideInt")==0)
             || (c=='i' && strcmp(zType,"int")==0) 
      ){
        eType = SQLITE_INTEGER;
      }else if( c=='d' && strcmp(zType,"double")==0 ){
        eType = SQLITE_FLOAT;
      }else{
        eType = SQLITE_TEXT;
      }
    }

    switch( eType ){
      case SQLITE_BLOB: {
        data = Tcl_GetByteArrayFromObj(pVar, &n);
        sqlite3_result_blob(context, data, n, SQLITE_TRANSIENT);
        break;
      }
      case SQLITE_INTEGER: {
        Tcl_WideInt v;
        if( TCL_OK==Tcl_GetWideIntFromObj(0, pVar, &v) ){
          sqlite3_result_int64(context, v);
          break;
        }
        /* fall-through */
      }
      case SQLITE_FLOAT: {
        double r;
        if( TCL_OK==Tcl_GetDoubleFromObj(0, pVar, &r) ){
          sqlite3_result_double(context, r);
          break;
        }
        /* fall-through */
      }
      default: {
        data = (unsigned char *)Tcl_GetStringFromObj(pVar, &n);
        sqlite3_result_text(context, (char *)data, n, SQLITE_TRANSIENT);
        break;
      }
    }

  }
}