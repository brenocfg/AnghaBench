#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char* zName; TYPE_1__* aCol; } ;
typedef  TYPE_2__ Table ;
struct TYPE_14__ {int /*<<< orphan*/ * aLimit; } ;
struct TYPE_13__ {int nKeyCol; size_t* aiColumn; int /*<<< orphan*/  zName; scalar_t__ aColExpr; TYPE_2__* pTable; } ;
struct TYPE_12__ {TYPE_7__* db; } ;
struct TYPE_10__ {char* zName; } ;
typedef  int /*<<< orphan*/  StrAccum ;
typedef  TYPE_3__ Parse ;
typedef  TYPE_4__ Index ;

/* Variables and functions */
 scalar_t__ IsPrimaryKeyIndex (TYPE_4__*) ; 
 int /*<<< orphan*/  P4_DYNAMIC ; 
 int /*<<< orphan*/  P5_ConstraintUnique ; 
 int /*<<< orphan*/  SQLITE_CONSTRAINT_PRIMARYKEY ; 
 int /*<<< orphan*/  SQLITE_CONSTRAINT_UNIQUE ; 
 size_t SQLITE_LIMIT_LENGTH ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3HaltConstraint (TYPE_3__*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* sqlite3StrAccumFinish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3StrAccumInit (int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_str_append (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_str_appendall (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sqlite3_str_appendf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void sqlite3UniqueConstraint(
  Parse *pParse,    /* Parsing context */
  int onError,      /* Constraint type */
  Index *pIdx       /* The index that triggers the constraint */
){
  char *zErr;
  int j;
  StrAccum errMsg;
  Table *pTab = pIdx->pTable;

  sqlite3StrAccumInit(&errMsg, pParse->db, 0, 0, 
                      pParse->db->aLimit[SQLITE_LIMIT_LENGTH]);
  if( pIdx->aColExpr ){
    sqlite3_str_appendf(&errMsg, "index '%q'", pIdx->zName);
  }else{
    for(j=0; j<pIdx->nKeyCol; j++){
      char *zCol;
      assert( pIdx->aiColumn[j]>=0 );
      zCol = pTab->aCol[pIdx->aiColumn[j]].zName;
      if( j ) sqlite3_str_append(&errMsg, ", ", 2);
      sqlite3_str_appendall(&errMsg, pTab->zName);
      sqlite3_str_append(&errMsg, ".", 1);
      sqlite3_str_appendall(&errMsg, zCol);
    }
  }
  zErr = sqlite3StrAccumFinish(&errMsg);
  sqlite3HaltConstraint(pParse, 
    IsPrimaryKeyIndex(pIdx) ? SQLITE_CONSTRAINT_PRIMARYKEY 
                            : SQLITE_CONSTRAINT_UNIQUE,
    onError, zErr, P4_DYNAMIC, P5_ConstraintUnique);
}