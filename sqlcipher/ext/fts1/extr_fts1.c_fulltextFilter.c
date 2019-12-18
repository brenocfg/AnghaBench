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
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_value ;
struct TYPE_7__ {int nColumn; int /*<<< orphan*/  zName; int /*<<< orphan*/  zDb; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ fulltext_vtab ;
struct TYPE_9__ {int /*<<< orphan*/ * pDoclist; } ;
struct TYPE_8__ {int iCursorType; TYPE_3__ result; int /*<<< orphan*/  q; int /*<<< orphan*/  pStmt; } ;
typedef  TYPE_2__ fulltext_cursor ;
typedef  int /*<<< orphan*/  DocList ;

/* Variables and functions */
 int QUERY_FULLTEXT ; 
#define  QUERY_GENERIC 129 
#define  QUERY_ROWID 128 
 int SQLITE_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* cursor_vtab (TYPE_2__*) ; 
 int /*<<< orphan*/  docListDelete (int /*<<< orphan*/ *) ; 
 int fulltextNext (int /*<<< orphan*/ *) ; 
 int fulltextQuery (TYPE_1__*,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queryClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readerInit (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int sql_prepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int sqlite3_bind_int64 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char*) ; 
 int /*<<< orphan*/  sqlite3_value_int64 (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fulltextFilter(
  sqlite3_vtab_cursor *pCursor,     /* The cursor used for this query */
  int idxNum, const char *idxStr,   /* Which indexing scheme to use */
  int argc, sqlite3_value **argv    /* Arguments for the indexing scheme */
){
  fulltext_cursor *c = (fulltext_cursor *) pCursor;
  fulltext_vtab *v = cursor_vtab(c);
  int rc;
  char *zSql;

  TRACE(("FTS1 Filter %p\n",pCursor));

  zSql = sqlite3_mprintf("select rowid, * from %%_content %s",
                          idxNum==QUERY_GENERIC ? "" : "where rowid=?");
  sqlite3_finalize(c->pStmt);
  rc = sql_prepare(v->db, v->zDb, v->zName, &c->pStmt, zSql);
  sqlite3_free(zSql);
  if( rc!=SQLITE_OK ) return rc;

  c->iCursorType = idxNum;
  switch( idxNum ){
    case QUERY_GENERIC:
      break;

    case QUERY_ROWID:
      rc = sqlite3_bind_int64(c->pStmt, 1, sqlite3_value_int64(argv[0]));
      if( rc!=SQLITE_OK ) return rc;
      break;

    default:   /* full-text search */
    {
      const char *zQuery = (const char *)sqlite3_value_text(argv[0]);
      DocList *pResult;
      assert( idxNum<=QUERY_FULLTEXT+v->nColumn);
      assert( argc==1 );
      queryClear(&c->q);
      rc = fulltextQuery(v, idxNum-QUERY_FULLTEXT, zQuery, -1, &pResult, &c->q);
      if( rc!=SQLITE_OK ) return rc;
      if( c->result.pDoclist!=NULL ) docListDelete(c->result.pDoclist);
      readerInit(&c->result, pResult);
      break;
    }
  }

  return fulltextNext(pCursor);
}