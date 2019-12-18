#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_7__ {int /*<<< orphan*/  orconf; int /*<<< orphan*/ * pWhere; } ;
typedef  TYPE_1__ TriggerStep ;
typedef  int /*<<< orphan*/  Token ;
struct TYPE_8__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_2__ Parse ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EXPRDUP_REDUCE ; 
 scalar_t__ IN_RENAME_OBJECT ; 
 int /*<<< orphan*/  OE_Default ; 
 int /*<<< orphan*/  TK_DELETE ; 
 int /*<<< orphan*/  sqlite3ExprDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3ExprDup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* triggerStepAllocate (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,char const*) ; 

TriggerStep *sqlite3TriggerDeleteStep(
  Parse *pParse,          /* Parser */
  Token *pTableName,      /* The table from which rows are deleted */
  Expr *pWhere,           /* The WHERE clause */
  const char *zStart,     /* Start of SQL text */
  const char *zEnd        /* End of SQL text */
){
  sqlite3 *db = pParse->db;
  TriggerStep *pTriggerStep;

  pTriggerStep = triggerStepAllocate(pParse, TK_DELETE, pTableName,zStart,zEnd);
  if( pTriggerStep ){
    if( IN_RENAME_OBJECT ){
      pTriggerStep->pWhere = pWhere;
      pWhere = 0;
    }else{
      pTriggerStep->pWhere = sqlite3ExprDup(db, pWhere, EXPRDUP_REDUCE);
    }
    pTriggerStep->orconf = OE_Default;
  }
  sqlite3ExprDelete(db, pWhere);
  return pTriggerStep;
}