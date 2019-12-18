#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  fulltext_vtab ;
struct TYPE_9__ {int /*<<< orphan*/  nData; } ;
typedef  int /*<<< orphan*/  DocListMerge ;
typedef  TYPE_1__ DocList ;

/* Variables and functions */
 int /*<<< orphan*/  DL_POSITIONS_OFFSETS ; 
 int SQLITE_DONE ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  docListDestroy (TYPE_1__*) ; 
 int /*<<< orphan*/  docListInit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mergeBlock (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mergeInit (int /*<<< orphan*/ *,TYPE_1__*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_column_blob (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_column_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 
 int term_select_doclist (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int query_merge(fulltext_vtab *v, sqlite3_stmt **pSelect,
                       const char *zTerm,
                       DocList *pIn, int iOffset, DocList *out){
  int rc;
  DocListMerge merge;

  if( pIn!=NULL && !pIn->nData ){
    /* If [pIn] is already empty, there's no point in reading the
     * posting list to AND it in; return immediately. */
      return SQLITE_OK;
  }

  rc = term_select_doclist(v, zTerm, -1, pSelect);
  if( rc!=SQLITE_ROW && rc!=SQLITE_DONE ) return rc;

  mergeInit(&merge, pIn, iOffset, out);
  while( rc==SQLITE_ROW ){
    DocList block;
    docListInit(&block, DL_POSITIONS_OFFSETS,
                sqlite3_column_blob(*pSelect, 0),
                sqlite3_column_bytes(*pSelect, 0));
    mergeBlock(&merge, &block);
    docListDestroy(&block);

    rc = sqlite3_step(*pSelect);
    if( rc!=SQLITE_ROW && rc!=SQLITE_DONE ){
      return rc;
    }
  }
  
  return SQLITE_OK;
}