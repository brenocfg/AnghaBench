#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ nEmpty; TYPE_2__* aDlidx; } ;
struct TYPE_6__ {scalar_t__ n; } ;
struct TYPE_7__ {TYPE_1__ buf; } ;
typedef  TYPE_3__ Fts5SegWriter ;
typedef  int /*<<< orphan*/  Fts5Index ;

/* Variables and functions */
 scalar_t__ FTS5_MIN_DLIDX_SIZE ; 
 int /*<<< orphan*/  fts5WriteDlidxClear (int /*<<< orphan*/ *,TYPE_3__*,int) ; 

__attribute__((used)) static int fts5WriteFlushDlidx(Fts5Index *p, Fts5SegWriter *pWriter){
  int bFlag = 0;

  /* If there were FTS5_MIN_DLIDX_SIZE or more empty leaf pages written
  ** to the database, also write the doclist-index to disk.  */
  if( pWriter->aDlidx[0].buf.n>0 && pWriter->nEmpty>=FTS5_MIN_DLIDX_SIZE ){
    bFlag = 1;
  }
  fts5WriteDlidxClear(p, pWriter, bFlag);
  pWriter->nEmpty = 0;
  return bFlag;
}