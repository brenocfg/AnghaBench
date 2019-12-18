#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ i64 ;
struct TYPE_5__ {scalar_t__ iRowid; } ;
typedef  TYPE_1__ Fts5IndexIter ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3Fts5IterEof (TYPE_1__*) ; 
 int sqlite3Fts5IterNextFrom (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static int fts5ExprAdvanceto(
  Fts5IndexIter *pIter,           /* Iterator to advance */
  int bDesc,                      /* True if iterator is "rowid DESC" */
  i64 *piLast,                    /* IN/OUT: Lastest rowid seen so far */
  int *pRc,                       /* OUT: Error code */
  int *pbEof                      /* OUT: Set to true if EOF */
){
  i64 iLast = *piLast;
  i64 iRowid;

  iRowid = pIter->iRowid;
  if( (bDesc==0 && iLast>iRowid) || (bDesc && iLast<iRowid) ){
    int rc = sqlite3Fts5IterNextFrom(pIter, iLast);
    if( rc || sqlite3Fts5IterEof(pIter) ){
      *pRc = rc;
      *pbEof = 1;
      return 1;
    }
    iRowid = pIter->iRowid;
    assert( (bDesc==0 && iRowid>=iLast) || (bDesc==1 && iRowid<=iLast) );
  }
  *piLast = iRowid;

  return 0;
}