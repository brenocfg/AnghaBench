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
typedef  scalar_t__ i64 ;
struct TYPE_4__ {scalar_t__ nTotalRow; } ;
typedef  TYPE_1__ Fts5Storage ;

/* Variables and functions */
 int FTS5_CORRUPT ; 
 int SQLITE_OK ; 
 int fts5StorageLoadTotals (TYPE_1__*,int /*<<< orphan*/ ) ; 

int sqlite3Fts5StorageRowCount(Fts5Storage *p, i64 *pnRow){
  int rc = fts5StorageLoadTotals(p, 0);
  if( rc==SQLITE_OK ){
    /* nTotalRow being zero does not necessarily indicate a corrupt 
    ** database - it might be that the FTS5 table really does contain zero
    ** rows. However this function is only called from the xRowCount() API,
    ** and there is no way for that API to be invoked if the table contains
    ** no rows. Hence the FTS5_CORRUPT return.  */
    *pnRow = p->nTotalRow;
    if( p->nTotalRow<=0 ) rc = FTS5_CORRUPT;
  }
  return rc;
}