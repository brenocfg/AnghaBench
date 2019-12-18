#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_5__ {int nColumn; } ;
typedef  TYPE_1__ fulltext_vtab ;
typedef  int /*<<< orphan*/  DocList ;

/* Variables and functions */
 int /*<<< orphan*/  DL_DEFAULT ; 
 int SQLITE_DONE ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  TERM_SELECT_ALL_STMT ; 
 int /*<<< orphan*/  docListAccumulate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  docListDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  docListDiscardEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  docListInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  docListRestrictColumn (int /*<<< orphan*/ *,int) ; 
 int sql_get_statement (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int sql_step_statement (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int sqlite3_bind_text (int /*<<< orphan*/ *,int,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_column_blob (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_column_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int term_select_all(
  fulltext_vtab *v,     /* The fulltext index we are querying against */
  int iColumn,          /* If <nColumn, only look at the iColumn-th column */
  const char *pTerm,    /* The term whose posting lists we want */
  int nTerm,            /* Number of bytes in pTerm */
  DocList *out          /* Write the resulting doclist here */
){
  DocList doclist;
  sqlite3_stmt *s;
  int rc = sql_get_statement(v, TERM_SELECT_ALL_STMT, &s);
  if( rc!=SQLITE_OK ) return rc;

  rc = sqlite3_bind_text(s, 1, pTerm, nTerm, SQLITE_STATIC);
  if( rc!=SQLITE_OK ) return rc;

  docListInit(&doclist, DL_DEFAULT, 0, 0);

  /* TODO(shess) Handle schema and busy errors. */
  while( (rc=sql_step_statement(v, TERM_SELECT_ALL_STMT, &s))==SQLITE_ROW ){
    DocList old;

    /* TODO(shess) If we processed doclists from oldest to newest, we
    ** could skip the malloc() involved with the following call.  For
    ** now, I'd rather keep this logic similar to index_insert_term().
    ** We could additionally drop elements when we see deletes, but
    ** that would require a distinct version of docListAccumulate().
    */
    docListInit(&old, DL_DEFAULT,
                sqlite3_column_blob(s, 0), sqlite3_column_bytes(s, 0));

    if( iColumn<v->nColumn ){   /* querying a single column */
      docListRestrictColumn(&old, iColumn);
    }

    /* doclist contains the newer data, so write it over old.  Then
    ** steal accumulated result for doclist.
    */
    docListAccumulate(&old, &doclist);
    docListDestroy(&doclist);
    doclist = old;
  }
  if( rc!=SQLITE_DONE ){
    docListDestroy(&doclist);
    return rc;
  }

  docListDiscardEmpty(&doclist);
  *out = doclist;
  return SQLITE_OK;
}