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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int bEof; int nLeTerm; int /*<<< orphan*/  term; int /*<<< orphan*/  zLeTerm; int /*<<< orphan*/  pIter; } ;
typedef  TYPE_1__ Fts5VocabCursor ;

/* Variables and functions */
 int MIN (int,int) ; 
 int SQLITE_OK ; 
 int memcmp (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  sqlite3Fts5BufferSet (int*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*) ; 
 scalar_t__ sqlite3Fts5IterEof (int /*<<< orphan*/ ) ; 
 char* sqlite3Fts5IterTerm (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int fts5VocabInstanceNewTerm(Fts5VocabCursor *pCsr){
  int rc = SQLITE_OK;
  
  if( sqlite3Fts5IterEof(pCsr->pIter) ){
    pCsr->bEof = 1;
  }else{
    const char *zTerm;
    int nTerm;
    zTerm = sqlite3Fts5IterTerm(pCsr->pIter, &nTerm);
    if( pCsr->nLeTerm>=0 ){
      int nCmp = MIN(nTerm, pCsr->nLeTerm);
      int bCmp = memcmp(pCsr->zLeTerm, zTerm, nCmp);
      if( bCmp<0 || (bCmp==0 && pCsr->nLeTerm<nTerm) ){
        pCsr->bEof = 1;
      }
    }

    sqlite3Fts5BufferSet(&rc, &pCsr->term, nTerm, (const u8*)zTerm);
  }
  return rc;
}