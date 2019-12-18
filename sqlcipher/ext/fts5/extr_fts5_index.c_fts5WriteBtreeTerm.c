#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_10__ {scalar_t__ rc; } ;
struct TYPE_8__ {int /*<<< orphan*/  pgno; } ;
struct TYPE_9__ {TYPE_1__ writer; int /*<<< orphan*/  iBtPage; int /*<<< orphan*/  btterm; } ;
typedef  TYPE_2__ Fts5SegWriter ;
typedef  TYPE_3__ Fts5Index ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  fts5BufferSet (scalar_t__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fts5WriteFlushBtree (TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static void fts5WriteBtreeTerm(
  Fts5Index *p,                   /* FTS5 backend object */
  Fts5SegWriter *pWriter,         /* Writer object */
  int nTerm, const u8 *pTerm      /* First term on new page */
){
  fts5WriteFlushBtree(p, pWriter);
  if( p->rc==SQLITE_OK ){
    fts5BufferSet(&p->rc, &pWriter->btterm, nTerm, pTerm);
    pWriter->iBtPage = pWriter->writer.pgno;
  }
}