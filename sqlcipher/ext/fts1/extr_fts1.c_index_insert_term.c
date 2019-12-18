#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sqlite_int64 ;
typedef  int /*<<< orphan*/  fulltext_vtab ;
struct TYPE_12__ {scalar_t__ nData; } ;
typedef  TYPE_1__ DocList ;

/* Variables and functions */
 scalar_t__ CHUNK_MAX ; 
 int /*<<< orphan*/  DL_DEFAULT ; 
 int SQLITE_DONE ; 
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  docListAccumulate (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  docListDestroy (TYPE_1__*) ; 
 int /*<<< orphan*/  docListInit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  docListUpdate (TYPE_1__*,TYPE_1__*) ; 
 int term_delete (int /*<<< orphan*/ *,scalar_t__) ; 
 int term_insert (int /*<<< orphan*/ *,scalar_t__*,char const*,int,int,TYPE_1__*) ; 
 int term_select (int /*<<< orphan*/ *,char const*,int,int,scalar_t__*,TYPE_1__*) ; 
 int term_update (int /*<<< orphan*/ *,scalar_t__,TYPE_1__*) ; 

__attribute__((used)) static int index_insert_term(fulltext_vtab *v, const char *pTerm, int nTerm,
                             DocList *d){
  sqlite_int64 iIndexRow;
  DocList doclist;
  int iSegment = 0, rc;

  rc = term_select(v, pTerm, nTerm, iSegment, &iIndexRow, &doclist);
  if( rc==SQLITE_DONE ){
    docListInit(&doclist, DL_DEFAULT, 0, 0);
    docListUpdate(&doclist, d);
    /* TODO(shess) Consider length(doclist)>CHUNK_MAX? */
    rc = term_insert(v, NULL, pTerm, nTerm, iSegment, &doclist);
    goto err;
  }
  if( rc!=SQLITE_ROW ) return SQLITE_ERROR;

  docListUpdate(&doclist, d);
  if( doclist.nData<=CHUNK_MAX ){
    rc = term_update(v, iIndexRow, &doclist);
    goto err;
  }

  /* Doclist doesn't fit, delete what's there, and accumulate
  ** forward.
  */
  rc = term_delete(v, iIndexRow);
  if( rc!=SQLITE_OK ) goto err;

  /* Try to insert the doclist into a higher segment bucket.  On
  ** failure, accumulate existing doclist with the doclist from that
  ** bucket, and put results in the next bucket.
  */
  iSegment++;
  while( (rc=term_insert(v, &iIndexRow, pTerm, nTerm, iSegment,
                         &doclist))!=SQLITE_OK ){
    sqlite_int64 iSegmentRow;
    DocList old;
    int rc2;

    /* Retain old error in case the term_insert() error was really an
    ** error rather than a bounced insert.
    */
    rc2 = term_select(v, pTerm, nTerm, iSegment, &iSegmentRow, &old);
    if( rc2!=SQLITE_ROW ) goto err;

    rc = term_delete(v, iSegmentRow);
    if( rc!=SQLITE_OK ) goto err;

    /* Reusing lowest-number deleted row keeps the index smaller. */
    if( iSegmentRow<iIndexRow ) iIndexRow = iSegmentRow;

    /* doclist contains the newer data, so accumulate it over old.
    ** Then steal accumulated data for doclist.
    */
    docListAccumulate(&old, &doclist);
    docListDestroy(&doclist);
    doclist = old;

    iSegment++;
  }

 err:
  docListDestroy(&doclist);
  return rc;
}