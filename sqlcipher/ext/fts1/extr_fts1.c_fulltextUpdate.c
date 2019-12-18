#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int /*<<< orphan*/  sqlite3_value ;
struct TYPE_6__ {int nColumn; } ;
typedef  TYPE_1__ fulltext_vtab ;
typedef  int /*<<< orphan*/  fts1HashElem ;
typedef  int /*<<< orphan*/  fts1Hash ;
typedef  int /*<<< orphan*/  DocList ;

/* Variables and functions */
 int /*<<< orphan*/  FTS1_HASH_STRING ; 
 int SQLITE_ERROR ; 
 scalar_t__ SQLITE_INTEGER ; 
 scalar_t__ SQLITE_NULL ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  docListDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts1HashClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fts1HashData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fts1HashFirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts1HashInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fts1HashKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts1HashKeysize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fts1HashNext (int /*<<< orphan*/ *) ; 
 int index_delete (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int index_insert (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,scalar_t__*,int /*<<< orphan*/ *) ; 
 int index_insert_term (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int index_update (TYPE_1__*,scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_int64 (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fulltextUpdate(sqlite3_vtab *pVtab, int nArg, sqlite3_value **ppArg,
                   sqlite_int64 *pRowid){
  fulltext_vtab *v = (fulltext_vtab *) pVtab;
  fts1Hash terms;   /* maps term string -> PosList */
  int rc;
  fts1HashElem *e;

  TRACE(("FTS1 Update %p\n", pVtab));
  
  fts1HashInit(&terms, FTS1_HASH_STRING, 1);

  if( nArg<2 ){
    rc = index_delete(v, sqlite3_value_int64(ppArg[0]), &terms);
  } else if( sqlite3_value_type(ppArg[0]) != SQLITE_NULL ){
    /* An update:
     * ppArg[0] = old rowid
     * ppArg[1] = new rowid
     * ppArg[2..2+v->nColumn-1] = values
     * ppArg[2+v->nColumn] = value for magic column (we ignore this)
     */
    sqlite_int64 rowid = sqlite3_value_int64(ppArg[0]);
    if( sqlite3_value_type(ppArg[1]) != SQLITE_INTEGER ||
      sqlite3_value_int64(ppArg[1]) != rowid ){
      rc = SQLITE_ERROR;  /* we don't allow changing the rowid */
    } else {
      assert( nArg==2+v->nColumn+1);
      rc = index_update(v, rowid, &ppArg[2], &terms);
    }
  } else {
    /* An insert:
     * ppArg[1] = requested rowid
     * ppArg[2..2+v->nColumn-1] = values
     * ppArg[2+v->nColumn] = value for magic column (we ignore this)
     */
    assert( nArg==2+v->nColumn+1);
    rc = index_insert(v, ppArg[1], &ppArg[2], pRowid, &terms);
  }

  if( rc==SQLITE_OK ){
    /* Write updated doclists to disk. */
    for(e=fts1HashFirst(&terms); e; e=fts1HashNext(e)){
      DocList *p = fts1HashData(e);
      rc = index_insert_term(v, fts1HashKey(e), fts1HashKeysize(e), p);
      if( rc!=SQLITE_OK ) break;
    }
  }

  /* clean up */
  for(e=fts1HashFirst(&terms); e; e=fts1HashNext(e)){
    DocList *p = fts1HashData(e);
    docListDelete(p);
  }
  fts1HashClear(&terms);

  return rc;
}