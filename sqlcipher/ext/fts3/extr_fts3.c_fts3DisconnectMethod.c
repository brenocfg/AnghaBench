#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_7__ {TYPE_1__* pModule; } ;
struct TYPE_6__ {scalar_t__ nPendingData; scalar_t__ pSegments; TYPE_3__* pTokenizer; struct TYPE_6__* zLanguageid; struct TYPE_6__* zContentTbl; struct TYPE_6__* zWriteExprlist; struct TYPE_6__* zReadExprlist; struct TYPE_6__* zSegmentsTbl; int /*<<< orphan*/ * aStmt; int /*<<< orphan*/  pSeekStmt; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* xDestroy ) (TYPE_3__*) ;} ;
typedef  TYPE_2__ Fts3Table ;

/* Variables and functions */
 int SQLITE_OK ; 
 int SizeofArray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static int fts3DisconnectMethod(sqlite3_vtab *pVtab){
  Fts3Table *p = (Fts3Table *)pVtab;
  int i;

  assert( p->nPendingData==0 );
  assert( p->pSegments==0 );

  /* Free any prepared statements held */
  sqlite3_finalize(p->pSeekStmt);
  for(i=0; i<SizeofArray(p->aStmt); i++){
    sqlite3_finalize(p->aStmt[i]);
  }
  sqlite3_free(p->zSegmentsTbl);
  sqlite3_free(p->zReadExprlist);
  sqlite3_free(p->zWriteExprlist);
  sqlite3_free(p->zContentTbl);
  sqlite3_free(p->zLanguageid);

  /* Invoke the tokenizer destructor to free the tokenizer. */
  p->pTokenizer->pModule->xDestroy(p->pTokenizer);

  sqlite3_free(p);
  return SQLITE_OK;
}