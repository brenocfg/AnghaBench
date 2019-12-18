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
struct TYPE_4__ {scalar_t__ iPrevDocid; int bPrevDelete; int iPrevLangid; scalar_t__ nPendingData; scalar_t__ nMaxPendingData; } ;
typedef  TYPE_1__ Fts3Table ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3Fts3PendingTermsFlush (TYPE_1__*) ; 

__attribute__((used)) static int fts3PendingTermsDocid(
  Fts3Table *p,                   /* Full-text table handle */
  int bDelete,                    /* True if this op is a delete */
  int iLangid,                    /* Language id of row being written */
  sqlite_int64 iDocid             /* Docid of row being written */
){
  assert( iLangid>=0 );
  assert( bDelete==1 || bDelete==0 );

  /* TODO(shess) Explore whether partially flushing the buffer on
  ** forced-flush would provide better performance.  I suspect that if
  ** we ordered the doclists by size and flushed the largest until the
  ** buffer was half empty, that would let the less frequent terms
  ** generate longer doclists.
  */
  if( iDocid<p->iPrevDocid 
   || (iDocid==p->iPrevDocid && p->bPrevDelete==0)
   || p->iPrevLangid!=iLangid
   || p->nPendingData>p->nMaxPendingData 
  ){
    int rc = sqlite3Fts3PendingTermsFlush(p);
    if( rc!=SQLITE_OK ) return rc;
  }
  p->iPrevDocid = iDocid;
  p->iPrevLangid = iLangid;
  p->bPrevDelete = bDelete;
  return SQLITE_OK;
}