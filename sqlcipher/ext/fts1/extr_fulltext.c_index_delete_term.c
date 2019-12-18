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
typedef  int /*<<< orphan*/  fulltext_vtab ;
struct TYPE_6__ {scalar_t__ nData; } ;
typedef  TYPE_1__ DocList ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  docListDestroy (TYPE_1__*) ; 
 scalar_t__ docListUpdate (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int term_chunk_select (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int term_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int term_select (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int term_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int index_delete_term(fulltext_vtab *v, const char *zTerm, int nTerm,
                             sqlite_int64 iDocid){
  sqlite_int64 iFirst;
  sqlite_int64 iIndexRow;
  DocList doclist;

  int rc = term_chunk_select(v, zTerm, nTerm, iDocid, &iFirst);
  if( rc!=SQLITE_ROW ) return SQLITE_ERROR;

  rc = term_select(v, zTerm, nTerm, iFirst, &iIndexRow, &doclist);
  if( rc!=SQLITE_OK ) return rc;

  if( docListUpdate(&doclist, iDocid, NULL) ){
    if( doclist.nData>0 ){
      rc = term_update(v, iIndexRow, &doclist);
    } else {  /* empty posting list */
      rc = term_delete(v, iIndexRow);
    }
  }
  docListDestroy(&doclist);
  return rc;
}