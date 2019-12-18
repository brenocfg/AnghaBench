#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ rc; } ;
struct TYPE_5__ {int nDlidx; int /*<<< orphan*/ * aDlidx; } ;
typedef  TYPE_1__ Fts5SegWriter ;
typedef  TYPE_2__ Fts5Index ;
typedef  int /*<<< orphan*/  Fts5DlidxWriter ;

/* Variables and functions */
 scalar_t__ SQLITE_NOMEM ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ sqlite3_realloc64 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int fts5WriteDlidxGrow(
  Fts5Index *p,
  Fts5SegWriter *pWriter,
  int nLvl
){
  if( p->rc==SQLITE_OK && nLvl>=pWriter->nDlidx ){
    Fts5DlidxWriter *aDlidx = (Fts5DlidxWriter*)sqlite3_realloc64(
        pWriter->aDlidx, sizeof(Fts5DlidxWriter) * nLvl
    );
    if( aDlidx==0 ){
      p->rc = SQLITE_NOMEM;
    }else{
      size_t nByte = sizeof(Fts5DlidxWriter) * (nLvl - pWriter->nDlidx);
      memset(&aDlidx[pWriter->nDlidx], 0, nByte);
      pWriter->aDlidx = aDlidx;
      pWriter->nDlidx = nLvl;
    }
  }
  return p->rc;
}