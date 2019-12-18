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
typedef  int /*<<< orphan*/  sqlite_int64 ;
struct TYPE_6__ {int /*<<< orphan*/  pTokenizer; } ;
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
 int build_terms (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int content_delete (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int content_select (TYPE_1__*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  docListDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int index_delete_term (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int index_delete(fulltext_vtab *v, sqlite_int64 iRow){
  char *zText;
  Hash terms;
  HashElem *e;

  int rc = content_select(v, iRow, &zText);
  if( rc!=SQLITE_OK ) return rc;

  rc = build_terms(&terms, v->pTokenizer, zText, iRow);
  free(zText);
  if( rc!=SQLITE_OK ) return rc;

  for(e=HashFirst(&terms); e; e=HashNext(e)){
    rc = index_delete_term(v, HashKey(e), HashKeysize(e), iRow);
    if( rc!=SQLITE_OK ) break;
  }
  for(e=HashFirst(&terms); e; e=HashNext(e)){
    DocList *p = HashData(e);
    docListDelete(p);
  }
  HashClear(&terms);

  return content_delete(v, iRow);
}