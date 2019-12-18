#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite_int64 ;
typedef  int /*<<< orphan*/  fulltext_vtab ;
struct TYPE_13__ {scalar_t__ nData; } ;
typedef  TYPE_1__ DocList ;

/* Variables and functions */
 scalar_t__ CHUNK_MAX ; 
 int /*<<< orphan*/  DL_POSITIONS_OFFSETS ; 
 int SQLITE_DONE ; 
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  docListDestroy (TYPE_1__*) ; 
 int /*<<< orphan*/  docListInit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ docListSplit (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ docListUpdate (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  firstDocid (TYPE_1__*) ; 
 int term_chunk_select (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int term_insert (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int term_select (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int term_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int index_insert_term(fulltext_vtab *v, const char *zTerm, int nTerm,
                             sqlite_int64 iDocid, DocList *p){
  sqlite_int64 iFirst;
  sqlite_int64 iIndexRow;
  DocList doclist;

  int rc = term_chunk_select(v, zTerm, nTerm, iDocid, &iFirst);
  if( rc==SQLITE_DONE ){
    docListInit(&doclist, DL_POSITIONS_OFFSETS, 0, 0);
    if( docListUpdate(&doclist, iDocid, p) ){
      rc = term_insert(v, zTerm, nTerm, iDocid, &doclist);
      docListDestroy(&doclist);
      return rc;
    }
    return SQLITE_OK;
  }
  if( rc!=SQLITE_ROW ) return SQLITE_ERROR;

  /* This word is in the index; add this document ID to its blob. */

  rc = term_select(v, zTerm, nTerm, iFirst, &iIndexRow, &doclist);
  if( rc!=SQLITE_OK ) return rc;

  if( docListUpdate(&doclist, iDocid, p) ){
    /* If the blob is too big, split it in half. */
    if( doclist.nData>CHUNK_MAX ){
      DocList half;
      if( docListSplit(&doclist, &half) ){
        rc = term_insert(v, zTerm, nTerm, firstDocid(&half), &half);
        docListDestroy(&half);
        if( rc!=SQLITE_OK ) goto err;
      }
    }
    rc = term_update(v, iIndexRow, &doclist);
  }

err:
  docListDestroy(&doclist);
  return rc;
}