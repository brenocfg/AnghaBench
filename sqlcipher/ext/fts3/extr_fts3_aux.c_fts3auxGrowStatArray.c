#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct Fts3auxColstats {int dummy; } ;
struct TYPE_3__ {int nStat; struct Fts3auxColstats* aStat; } ;
typedef  TYPE_1__ Fts3auxCursor ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  memset (struct Fts3auxColstats*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3_realloc64 (struct Fts3auxColstats*,int) ; 

__attribute__((used)) static int fts3auxGrowStatArray(Fts3auxCursor *pCsr, int nSize){
  if( nSize>pCsr->nStat ){
    struct Fts3auxColstats *aNew;
    aNew = (struct Fts3auxColstats *)sqlite3_realloc64(pCsr->aStat, 
        sizeof(struct Fts3auxColstats) * nSize
    );
    if( aNew==0 ) return SQLITE_NOMEM;
    memset(&aNew[pCsr->nStat], 0, 
        sizeof(struct Fts3auxColstats) * (nSize - pCsr->nStat)
    );
    pCsr->aStat = aNew;
    pCsr->nStat = nSize;
  }
  return SQLITE_OK;
}