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
typedef  int /*<<< orphan*/  sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_value ;
struct TYPE_5__ {int /*<<< orphan*/  pTokenizer; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ fulltext_vtab ;
typedef  int /*<<< orphan*/  HashElem ;
typedef  int /*<<< orphan*/  Hash ;
typedef  int /*<<< orphan*/  DocList ;

/* Variables and functions */
 int /*<<< orphan*/  HashClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HashData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HashFirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HashKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HashKeysize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HashNext (int /*<<< orphan*/ *) ; 
 int SQLITE_OK ; 
 int build_terms (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int content_insert (TYPE_1__*,int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  docListDelete (int /*<<< orphan*/ *) ; 
 int index_insert_term (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_last_insert_rowid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int index_insert(fulltext_vtab *v,
                        sqlite3_value *pRequestRowid, const char *zText,
                        sqlite_int64 *piRowid){
  Hash terms;  /* maps term string -> PosList */
  HashElem *e;

  int rc = content_insert(v, pRequestRowid, zText, -1);
  if( rc!=SQLITE_OK ) return rc;
  *piRowid = sqlite3_last_insert_rowid(v->db);

  if( !zText ) return SQLITE_OK;   /* nothing to index */

  rc = build_terms(&terms, v->pTokenizer, zText, *piRowid);
  if( rc!=SQLITE_OK ) return rc;

  for(e=HashFirst(&terms); e; e=HashNext(e)){
    DocList *p = HashData(e);
    rc = index_insert_term(v, HashKey(e), HashKeysize(e), *piRowid, p);
    if( rc!=SQLITE_OK ) break;
  }

  for(e=HashFirst(&terms); e; e=HashNext(e)){
    DocList *p = HashData(e);
    docListDelete(p);
  }
  HashClear(&terms);
  return rc;
}