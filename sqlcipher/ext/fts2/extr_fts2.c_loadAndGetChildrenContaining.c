#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  fulltext_vtab ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_SELECT_STMT ; 
 int SQLITE_DONE ; 
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  getChildrenContaining (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sql_get_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int sqlite3_bind_int64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_column_blob (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_column_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int loadAndGetChildrenContaining(
  fulltext_vtab *v,
  sqlite_int64 iBlockid,
  const char *pTerm, int nTerm, int isPrefix,
  sqlite_int64 *piStartChild, sqlite_int64 *piEndChild
){
  sqlite3_stmt *s = NULL;
  int rc;

  assert( iBlockid!=0 );
  assert( pTerm!=NULL );
  assert( nTerm!=0 );        /* TODO(shess) Why not allow this? */
  assert( piStartChild!=NULL );
  assert( piEndChild!=NULL );

  rc = sql_get_statement(v, BLOCK_SELECT_STMT, &s);
  if( rc!=SQLITE_OK ) return rc;

  rc = sqlite3_bind_int64(s, 1, iBlockid);
  if( rc!=SQLITE_OK ) return rc;

  rc = sqlite3_step(s);
  if( rc==SQLITE_DONE ) return SQLITE_ERROR;
  if( rc!=SQLITE_ROW ) return rc;

  getChildrenContaining(sqlite3_column_blob(s, 0), sqlite3_column_bytes(s, 0),
                        pTerm, nTerm, isPrefix, piStartChild, piEndChild);

  /* We expect only one row.  We must execute another sqlite3_step()
   * to complete the iteration; otherwise the table will remain
   * locked. */
  rc = sqlite3_step(s);
  if( rc==SQLITE_ROW ) return SQLITE_ERROR;
  if( rc!=SQLITE_DONE ) return rc;

  return SQLITE_OK;
}