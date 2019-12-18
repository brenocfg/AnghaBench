#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sqlite_int64 ;
struct TYPE_4__ {scalar_t__ iPrevDocid; scalar_t__ nPendingData; int /*<<< orphan*/  pendingTerms; } ;
typedef  TYPE_1__ fulltext_vtab ;

/* Variables and functions */
 int /*<<< orphan*/  FTS2_HASH_STRING ; 
 int SQLITE_OK ; 
 int flushPendingTerms (TYPE_1__*) ; 
 int /*<<< orphan*/  fts2HashInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ kPendingThreshold ; 

__attribute__((used)) static int initPendingTerms(fulltext_vtab *v, sqlite_int64 iDocid){
  /* TODO(shess) Explore whether partially flushing the buffer on
  ** forced-flush would provide better performance.  I suspect that if
  ** we ordered the doclists by size and flushed the largest until the
  ** buffer was half empty, that would let the less frequent terms
  ** generate longer doclists.
  */
  if( iDocid<=v->iPrevDocid || v->nPendingData>kPendingThreshold ){
    int rc = flushPendingTerms(v);
    if( rc!=SQLITE_OK ) return rc;
  }
  if( v->nPendingData<0 ){
    fts2HashInit(&v->pendingTerms, FTS2_HASH_STRING, 1);
    v->nPendingData = 0;
  }
  v->iPrevDocid = iDocid;
  return SQLITE_OK;
}