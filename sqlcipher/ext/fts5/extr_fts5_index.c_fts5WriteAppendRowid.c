#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
typedef  scalar_t__ i64 ;
struct TYPE_18__ {scalar_t__ rc; TYPE_2__* pConfig; } ;
struct TYPE_13__ {scalar_t__ n; int /*<<< orphan*/  p; } ;
struct TYPE_14__ {scalar_t__ n; } ;
struct TYPE_17__ {TYPE_12__ buf; TYPE_1__ pgidx; } ;
struct TYPE_16__ {scalar_t__ iPrevRowid; scalar_t__ bFirstRowidInPage; scalar_t__ bFirstRowidInDoclist; TYPE_4__ writer; } ;
struct TYPE_15__ {scalar_t__ pgsz; } ;
typedef  TYPE_3__ Fts5SegWriter ;
typedef  TYPE_4__ Fts5PageWriter ;
typedef  TYPE_5__ Fts5Index ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert_nc (int) ; 
 int /*<<< orphan*/  fts5BufferAppendVarint (scalar_t__*,TYPE_12__*,scalar_t__) ; 
 int /*<<< orphan*/  fts5PutU16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fts5WriteDlidxAppend (TYPE_5__*,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  fts5WriteFlushLeaf (TYPE_5__*,TYPE_3__*) ; 

__attribute__((used)) static void fts5WriteAppendRowid(
  Fts5Index *p, 
  Fts5SegWriter *pWriter,
  i64 iRowid
){
  if( p->rc==SQLITE_OK ){
    Fts5PageWriter *pPage = &pWriter->writer;

    if( (pPage->buf.n + pPage->pgidx.n)>=p->pConfig->pgsz ){
      fts5WriteFlushLeaf(p, pWriter);
    }

    /* If this is to be the first rowid written to the page, set the 
    ** rowid-pointer in the page-header. Also append a value to the dlidx
    ** buffer, in case a doclist-index is required.  */
    if( pWriter->bFirstRowidInPage ){
      fts5PutU16(pPage->buf.p, (u16)pPage->buf.n);
      fts5WriteDlidxAppend(p, pWriter, iRowid);
    }

    /* Write the rowid. */
    if( pWriter->bFirstRowidInDoclist || pWriter->bFirstRowidInPage ){
      fts5BufferAppendVarint(&p->rc, &pPage->buf, iRowid);
    }else{
      assert_nc( p->rc || iRowid>pWriter->iPrevRowid );
      fts5BufferAppendVarint(&p->rc, &pPage->buf, iRowid - pWriter->iPrevRowid);
    }
    pWriter->iPrevRowid = iRowid;
    pWriter->bFirstRowidInDoclist = 0;
    pWriter->bFirstRowidInPage = 0;
  }
}