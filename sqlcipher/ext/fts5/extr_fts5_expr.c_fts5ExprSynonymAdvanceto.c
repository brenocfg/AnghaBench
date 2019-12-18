#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ i64 ;
struct TYPE_7__ {scalar_t__ iRowid; } ;
struct TYPE_6__ {TYPE_2__* pIter; struct TYPE_6__* pSynonym; } ;
typedef  TYPE_1__ Fts5ExprTerm ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ fts5ExprSynonymRowid (TYPE_1__*,int,int*) ; 
 scalar_t__ sqlite3Fts5IterEof (TYPE_2__*) ; 
 int sqlite3Fts5IterNextFrom (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static int fts5ExprSynonymAdvanceto(
  Fts5ExprTerm *pTerm,            /* Term iterator to advance */
  int bDesc,                      /* True if iterator is "rowid DESC" */
  i64 *piLast,                    /* IN/OUT: Lastest rowid seen so far */
  int *pRc                        /* OUT: Error code */
){
  int rc = SQLITE_OK;
  i64 iLast = *piLast;
  Fts5ExprTerm *p;
  int bEof = 0;

  for(p=pTerm; rc==SQLITE_OK && p; p=p->pSynonym){
    if( sqlite3Fts5IterEof(p->pIter)==0 ){
      i64 iRowid = p->pIter->iRowid;
      if( (bDesc==0 && iLast>iRowid) || (bDesc && iLast<iRowid) ){
        rc = sqlite3Fts5IterNextFrom(p->pIter, iLast);
      }
    }
  }

  if( rc!=SQLITE_OK ){
    *pRc = rc;
    bEof = 1;
  }else{
    *piLast = fts5ExprSynonymRowid(pTerm, bDesc, &bEof);
  }
  return bEof;
}