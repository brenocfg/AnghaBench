#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_16__ {scalar_t__ rc; TYPE_1__* pConfig; } ;
struct TYPE_11__ {scalar_t__ n; } ;
struct TYPE_13__ {scalar_t__ n; } ;
struct TYPE_15__ {TYPE_10__ buf; TYPE_2__ pgidx; } ;
struct TYPE_14__ {TYPE_4__ writer; } ;
struct TYPE_12__ {scalar_t__ pgsz; } ;
typedef  TYPE_3__ Fts5SegWriter ;
typedef  TYPE_4__ Fts5PageWriter ;
typedef  TYPE_5__ Fts5Index ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5BufferAppendBlob (scalar_t__*,TYPE_10__*,int,int /*<<< orphan*/  const*) ; 
 scalar_t__ fts5GetVarint (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts5WriteFlushLeaf (TYPE_5__*,TYPE_3__*) ; 

__attribute__((used)) static void fts5WriteAppendPoslistData(
  Fts5Index *p, 
  Fts5SegWriter *pWriter, 
  const u8 *aData, 
  int nData
){
  Fts5PageWriter *pPage = &pWriter->writer;
  const u8 *a = aData;
  int n = nData;
  
  assert( p->pConfig->pgsz>0 );
  while( p->rc==SQLITE_OK 
     && (pPage->buf.n + pPage->pgidx.n + n)>=p->pConfig->pgsz 
  ){
    int nReq = p->pConfig->pgsz - pPage->buf.n - pPage->pgidx.n;
    int nCopy = 0;
    while( nCopy<nReq ){
      i64 dummy;
      nCopy += fts5GetVarint(&a[nCopy], (u64*)&dummy);
    }
    fts5BufferAppendBlob(&p->rc, &pPage->buf, nCopy, a);
    a += nCopy;
    n -= nCopy;
    fts5WriteFlushLeaf(p, pWriter);
  }
  if( n>0 ){
    fts5BufferAppendBlob(&p->rc, &pPage->buf, n, a);
  }
}