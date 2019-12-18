#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_9__ {int /*<<< orphan*/  p; int /*<<< orphan*/  n; } ;
struct TYPE_8__ {int /*<<< orphan*/  pIndex; int /*<<< orphan*/ * aTotalSize; int /*<<< orphan*/  nTotalRow; TYPE_1__* pConfig; } ;
struct TYPE_7__ {int nCol; } ;
typedef  TYPE_2__ Fts5Storage ;
typedef  TYPE_3__ Fts5Buffer ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3Fts5BufferAppendVarint (int*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int sqlite3Fts5IndexSetAverages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fts5StorageSaveTotals(Fts5Storage *p){
  int nCol = p->pConfig->nCol;
  int i;
  Fts5Buffer buf;
  int rc = SQLITE_OK;
  memset(&buf, 0, sizeof(buf));

  sqlite3Fts5BufferAppendVarint(&rc, &buf, p->nTotalRow);
  for(i=0; i<nCol; i++){
    sqlite3Fts5BufferAppendVarint(&rc, &buf, p->aTotalSize[i]);
  }
  if( rc==SQLITE_OK ){
    rc = sqlite3Fts5IndexSetAverages(p->pIndex, buf.p, buf.n);
  }
  sqlite3_free(buf.p);

  return rc;
}