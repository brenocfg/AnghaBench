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
typedef  int i64 ;
struct TYPE_10__ {scalar_t__ rc; int /*<<< orphan*/  pIdxWriter; } ;
struct TYPE_8__ {int /*<<< orphan*/  n; scalar_t__ p; } ;
struct TYPE_9__ {scalar_t__ iBtPage; scalar_t__ nEmpty; TYPE_1__ btterm; } ;
typedef  TYPE_2__ Fts5SegWriter ;
typedef  TYPE_3__ Fts5Index ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts5WriteFlushDlidx (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3_bind_blob (int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_int64 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3_bind_null (int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_step (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fts5WriteFlushBtree(Fts5Index *p, Fts5SegWriter *pWriter){
  int bFlag;

  assert( pWriter->iBtPage || pWriter->nEmpty==0 );
  if( pWriter->iBtPage==0 ) return;
  bFlag = fts5WriteFlushDlidx(p, pWriter);

  if( p->rc==SQLITE_OK ){
    const char *z = (pWriter->btterm.n>0?(const char*)pWriter->btterm.p:"");
    /* The following was already done in fts5WriteInit(): */
    /* sqlite3_bind_int(p->pIdxWriter, 1, pWriter->iSegid); */
    sqlite3_bind_blob(p->pIdxWriter, 2, z, pWriter->btterm.n, SQLITE_STATIC);
    sqlite3_bind_int64(p->pIdxWriter, 3, bFlag + ((i64)pWriter->iBtPage<<1));
    sqlite3_step(p->pIdxWriter);
    p->rc = sqlite3_reset(p->pIdxWriter);
    sqlite3_bind_null(p->pIdxWriter, 2);
  }
  pWriter->iBtPage = 0;
}