#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ i64 ;
struct TYPE_6__ {scalar_t__ bRev; } ;
typedef  TYPE_1__ Fts5Iter ;
typedef  int /*<<< orphan*/  Fts5Index ;

/* Variables and functions */
 scalar_t__ fts5MultiIterEof (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fts5MultiIterNext (int /*<<< orphan*/ *,TYPE_1__*,int,scalar_t__) ; 
 scalar_t__ fts5MultiIterRowid (TYPE_1__*) ; 

__attribute__((used)) static void fts5MultiIterNextFrom(
  Fts5Index *p, 
  Fts5Iter *pIter, 
  i64 iMatch
){
  while( 1 ){
    i64 iRowid;
    fts5MultiIterNext(p, pIter, 1, iMatch);
    if( fts5MultiIterEof(p, pIter) ) break;
    iRowid = fts5MultiIterRowid(pIter);
    if( pIter->bRev==0 && iRowid>=iMatch ) break;
    if( pIter->bRev!=0 && iRowid<=iMatch ) break;
  }
}