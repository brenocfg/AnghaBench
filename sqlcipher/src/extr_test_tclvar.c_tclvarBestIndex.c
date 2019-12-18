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
struct sqlite3_index_constraint_usage {int argvIndex; int omit; } ;
struct sqlite3_index_constraint {scalar_t__ op; int iColumn; scalar_t__ usable; } ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_5__ {int nConstraint; char* idxStr; int needToFreeIdxStr; struct sqlite3_index_constraint_usage* aConstraintUsage; struct sqlite3_index_constraint* aConstraint; } ;
typedef  TYPE_2__ sqlite3_index_info ;

/* Variables and functions */
 scalar_t__ SQLITE_INDEX_CONSTRAINT_EQ ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_GLOB ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_LIKE ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_MATCH ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_REGEXP ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  TCLVAR_NAME_EQ ; 
 int /*<<< orphan*/  TCLVAR_NAME_MATCH ; 
 int /*<<< orphan*/  TCLVAR_VALUE_GLOB ; 
 int /*<<< orphan*/  TCLVAR_VALUE_LIKE ; 
 int /*<<< orphan*/  TCLVAR_VALUE_REGEXP ; 
 char* sqlite3_malloc (int) ; 
 scalar_t__ tclvarAddToIdxstr (char*,int /*<<< orphan*/ ) ; 
 void* tclvarSetOmit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tclvarBestIndex(sqlite3_vtab *tab, sqlite3_index_info *pIdxInfo){
  tclvar_vtab *pTab = (tclvar_vtab*)tab;
  int ii;
  char *zStr = sqlite3_malloc(32);
  int iStr = 0;

  if( zStr==0 ) return SQLITE_NOMEM;
  zStr[0] = '\0';

  for(ii=0; ii<pIdxInfo->nConstraint; ii++){
    struct sqlite3_index_constraint const *pCons = &pIdxInfo->aConstraint[ii];
    struct sqlite3_index_constraint_usage *pUsage;
    
    pUsage = &pIdxInfo->aConstraintUsage[ii];
    if( pCons->usable ){
      /* name = ? */
      if( pCons->op==SQLITE_INDEX_CONSTRAINT_EQ && pCons->iColumn==0 ){
        if( 0==tclvarAddToIdxstr(zStr, TCLVAR_NAME_EQ) ){
          pUsage->argvIndex = ++iStr;
          pUsage->omit = 0;
        }
      }

      /* name MATCH ? */
      if( pCons->op==SQLITE_INDEX_CONSTRAINT_MATCH && pCons->iColumn==0 ){
        if( 0==tclvarAddToIdxstr(zStr, TCLVAR_NAME_MATCH) ){
          pUsage->argvIndex = ++iStr;
          pUsage->omit = 1;
        }
      }

      /* value GLOB ? */
      if( pCons->op==SQLITE_INDEX_CONSTRAINT_GLOB && pCons->iColumn==2 ){
        if( 0==tclvarAddToIdxstr(zStr, TCLVAR_VALUE_GLOB) ){
          pUsage->argvIndex = ++iStr;
          pUsage->omit = tclvarSetOmit(pTab->interp);
        }
      }

      /* value REGEXP ? */
      if( pCons->op==SQLITE_INDEX_CONSTRAINT_REGEXP && pCons->iColumn==2 ){
        if( 0==tclvarAddToIdxstr(zStr, TCLVAR_VALUE_REGEXP) ){
          pUsage->argvIndex = ++iStr;
          pUsage->omit = tclvarSetOmit(pTab->interp);
        }
      }

      /* value LIKE ? */
      if( pCons->op==SQLITE_INDEX_CONSTRAINT_LIKE && pCons->iColumn==2 ){
        if( 0==tclvarAddToIdxstr(zStr, TCLVAR_VALUE_LIKE) ){
          pUsage->argvIndex = ++iStr;
          pUsage->omit = tclvarSetOmit(pTab->interp);
        }
      }
    }
  }
  pIdxInfo->idxStr = zStr;
  pIdxInfo->needToFreeIdxStr = 1;

  return SQLITE_OK;
}