#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  interp; } ;
typedef  TYPE_1__ tclvar_vtab ;
typedef  int /*<<< orphan*/  sqlite_int64 ;
struct TYPE_5__ {void* zErrMsg; } ;
typedef  TYPE_2__ sqlite3_vtab ;
typedef  int /*<<< orphan*/  sqlite3_value ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 scalar_t__ SQLITE_NULL ; 
 int SQLITE_OK ; 
 scalar_t__ SQLITE_TEXT ; 
 int /*<<< orphan*/  TCL_GLOBAL_ONLY ; 
 int /*<<< orphan*/  Tcl_SetVar (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_UnsetVar (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 void* sqlite3_mprintf (char*) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_type (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static int tclvarUpdate(
  sqlite3_vtab *tab,
  int argc,
  sqlite3_value **argv,
  sqlite_int64 *pRowid
){
  tclvar_vtab *pTab = (tclvar_vtab*)tab;
  if( argc==1 ){
    /* A DELETE operation.  The variable to be deleted is stored in argv[0] */
    const char *zVar = (const char*)sqlite3_value_text(argv[0]);
    Tcl_UnsetVar(pTab->interp, zVar, TCL_GLOBAL_ONLY);
    return SQLITE_OK;
  }
  if( sqlite3_value_type(argv[0])==SQLITE_NULL ){
    /* An INSERT operation */
    const char *zValue = (const char*)sqlite3_value_text(argv[4]);
    const char *zName;
    if( sqlite3_value_type(argv[5])!=SQLITE_TEXT ){
      tab->zErrMsg = sqlite3_mprintf("the 'fullname' column must be TEXT");
      return SQLITE_ERROR;
    }
    zName = (const char*)sqlite3_value_text(argv[5]);
    if( zValue ){
      Tcl_SetVar(pTab->interp, zName, zValue, TCL_GLOBAL_ONLY);
    }else{
      Tcl_UnsetVar(pTab->interp, zName, TCL_GLOBAL_ONLY);
    }
    return SQLITE_OK;
  }
  if( sqlite3_value_type(argv[0])==SQLITE_TEXT
   && sqlite3_value_type(argv[1])==SQLITE_TEXT
  ){
    /* An UPDATE operation */
    const char *zOldName = (const char*)sqlite3_value_text(argv[0]);
    const char *zNewName = (const char*)sqlite3_value_text(argv[1]);
    const char *zValue = (const char*)sqlite3_value_text(argv[4]);

    if( strcmp(zOldName, zNewName)!=0 || zValue==0 ){
      Tcl_UnsetVar(pTab->interp, zOldName, TCL_GLOBAL_ONLY);
    }
    if( zValue!=0 ){
      Tcl_SetVar(pTab->interp, zNewName, zValue, TCL_GLOBAL_ONLY);
    }
    return SQLITE_OK;
  }
  tab->zErrMsg = sqlite3_mprintf("prohibited TCL variable change");
  return SQLITE_ERROR;
}