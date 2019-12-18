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
struct TYPE_3__ {int nFirstAlloc; int nFirst; int* aFirst; } ;
typedef  TYPE_1__ Fts5SFinder ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 scalar_t__ sqlite3_realloc64 (int*,int) ; 

__attribute__((used)) static int fts5SentenceFinderAdd(Fts5SFinder *p, int iAdd){
  if( p->nFirstAlloc==p->nFirst ){
    int nNew = p->nFirstAlloc ? p->nFirstAlloc*2 : 64;
    int *aNew;

    aNew = (int*)sqlite3_realloc64(p->aFirst, nNew*sizeof(int));
    if( aNew==0 ) return SQLITE_NOMEM;
    p->aFirst = aNew;
    p->nFirstAlloc = nNew;
  }
  p->aFirst[p->nFirst++] = iAdd;
  return SQLITE_OK;
}