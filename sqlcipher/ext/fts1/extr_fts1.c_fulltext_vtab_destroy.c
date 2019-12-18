#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int nColumn; struct TYPE_8__* azContentColumn; struct TYPE_8__* azColumn; TYPE_3__* pTokenizer; int /*<<< orphan*/ ** pFulltextStatements; } ;
typedef  TYPE_2__ fulltext_vtab ;
struct TYPE_9__ {TYPE_1__* pModule; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* xDestroy ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int MAX_STMT ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_2__) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static void fulltext_vtab_destroy(fulltext_vtab *v){
  int iStmt, i;

  TRACE(("FTS1 Destroy %p\n", v));
  for( iStmt=0; iStmt<MAX_STMT; iStmt++ ){
    if( v->pFulltextStatements[iStmt]!=NULL ){
      sqlite3_finalize(v->pFulltextStatements[iStmt]);
      v->pFulltextStatements[iStmt] = NULL;
    }
  }

  if( v->pTokenizer!=NULL ){
    v->pTokenizer->pModule->xDestroy(v->pTokenizer);
    v->pTokenizer = NULL;
  }
  
  free(v->azColumn);
  for(i = 0; i < v->nColumn; ++i) {
    sqlite3_free(v->azContentColumn[i]);
  }
  free(v->azContentColumn);
  free(v);
}