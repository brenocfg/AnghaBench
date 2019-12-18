#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_8__ {TYPE_2__* pRule; int /*<<< orphan*/  zCostTab; int /*<<< orphan*/  zClassName; int /*<<< orphan*/  zDb; } ;
typedef  TYPE_1__ amatch_vtab ;
struct TYPE_9__ {struct TYPE_9__* pNext; } ;
typedef  TYPE_2__ amatch_rule ;
typedef  int /*<<< orphan*/  a ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int amatchLoadOneRule (TYPE_1__*,int /*<<< orphan*/ *,TYPE_2__**,char**) ; 
 void* amatchMergeRules (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3_column_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amatchLoadRules(
  sqlite3 *db,                    /* Database handle */
  amatch_vtab *p,                 /* Virtual amatch table to configure */
  char **pzErr                    /* OUT: Error message */
){
  int rc = SQLITE_OK;             /* Return code */
  char *zSql;                     /* SELECT used to read from rules table */
  amatch_rule *pHead = 0;

  zSql = sqlite3_mprintf("SELECT * FROM %Q.%Q", p->zDb, p->zCostTab);
  if( zSql==0 ){
    rc = SQLITE_NOMEM;
  }else{
    int rc2;                      /* finalize() return code */
    sqlite3_stmt *pStmt = 0;
    rc = sqlite3_prepare_v2(db, zSql, -1, &pStmt, 0);
    if( rc!=SQLITE_OK ){
      *pzErr = sqlite3_mprintf("%s: %s", p->zClassName, sqlite3_errmsg(db));
    }else if( sqlite3_column_count(pStmt)!=4 ){
      *pzErr = sqlite3_mprintf("%s: %s has %d columns, expected 4",
          p->zClassName, p->zCostTab, sqlite3_column_count(pStmt)
      );
      rc = SQLITE_ERROR;
    }else{
      while( rc==SQLITE_OK && SQLITE_ROW==sqlite3_step(pStmt) ){
        amatch_rule *pRule = 0;
        rc = amatchLoadOneRule(p, pStmt, &pRule, pzErr);
        if( pRule ){
          pRule->pNext = pHead;
          pHead = pRule;
        }
      }
    }
    rc2 = sqlite3_finalize(pStmt);
    if( rc==SQLITE_OK ) rc = rc2;
  }
  sqlite3_free(zSql);

  /* All rules are now in a singly linked list starting at pHead. This
  ** block sorts them by cost and then sets amatch_vtab.pRule to point to 
  ** point to the head of the sorted list.
  */
  if( rc==SQLITE_OK ){
    unsigned int i;
    amatch_rule *pX;
    amatch_rule *a[15];
    for(i=0; i<sizeof(a)/sizeof(a[0]); i++) a[i] = 0;
    while( (pX = pHead)!=0 ){
      pHead = pX->pNext;
      pX->pNext = 0;
      for(i=0; a[i] && i<sizeof(a)/sizeof(a[0])-1; i++){
        pX = amatchMergeRules(a[i], pX);
        a[i] = 0;
      }
      a[i] = amatchMergeRules(a[i], pX);
    }
    for(pX=a[0], i=1; i<sizeof(a)/sizeof(a[0]); i++){
      pX = amatchMergeRules(a[i], pX);
    }
    p->pRule = amatchMergeRules(p->pRule, pX);
  }else{
    /* An error has occurred. Setting p->pRule to point to the head of the
    ** allocated list ensures that the list will be cleaned up in this case.
    */
    assert( p->pRule==0 );
    p->pRule = pHead;
  }

  return rc;
}