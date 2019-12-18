#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  fulltext_vtab ;
struct TYPE_6__ {int nTerms; TYPE_1__* pTerm; } ;
struct TYPE_5__ {int /*<<< orphan*/  zTerm; scalar_t__ is_phrase; } ;
typedef  TYPE_2__ Query ;
typedef  int /*<<< orphan*/  DocList ;

/* Variables and functions */
 int /*<<< orphan*/  DL_DOCIDS ; 
 int /*<<< orphan*/  DL_POSITIONS ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  docListDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * docListNew (int /*<<< orphan*/ ) ; 
 int parse_query (int /*<<< orphan*/ *,char const*,TYPE_2__*) ; 
 int /*<<< orphan*/  query_free (TYPE_2__*) ; 
 int query_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fulltext_query(fulltext_vtab *v, const char *zQuery,
                          DocList **pResult){
  Query q;
  int phrase_start = -1;
  int i;
  sqlite3_stmt *pSelect = NULL;
  DocList *d = NULL;

  int rc = parse_query(v, zQuery, &q);
  if( rc!=SQLITE_OK ) return rc;

  /* Merge terms. */
  for(i = 0 ; i < q.nTerms ; ++i){
    /* In each merge step, we need to generate positions whenever we're
     * processing a phrase which hasn't ended yet. */
    int need_positions = i<q.nTerms-1 && !q.pTerm[i+1].is_phrase;
    DocList *next = docListNew(need_positions ? DL_POSITIONS : DL_DOCIDS);
    if( q.pTerm[i].is_phrase ){
      phrase_start = i;
    }
    rc = query_merge(v, &pSelect, q.pTerm[i].zTerm, d, i - phrase_start, next);
    if( rc!=SQLITE_OK ) break;
    if( d!=NULL ){
      docListDelete(d);
    }
    d = next;
  }

  sqlite3_finalize(pSelect);
  query_free(&q);
  *pResult = d;
  return rc;
}