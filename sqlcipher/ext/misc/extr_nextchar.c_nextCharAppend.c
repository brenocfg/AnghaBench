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
struct TYPE_3__ {int nUsed; unsigned int* aResult; int nAlloc; int mallocFailed; } ;
typedef  TYPE_1__ nextCharContext ;

/* Variables and functions */
 unsigned int* sqlite3_realloc64 (unsigned int*,int) ; 

__attribute__((used)) static void nextCharAppend(nextCharContext *p, unsigned c){
  int i;
  for(i=0; i<p->nUsed; i++){
    if( p->aResult[i]==c ) return;
  }
  if( p->nUsed+1 > p->nAlloc ){
    unsigned int *aNew;
    int n = p->nAlloc*2 + 30;
    aNew = sqlite3_realloc64(p->aResult, n*sizeof(unsigned int));
    if( aNew==0 ){
      p->mallocFailed = 1;
      return;
    }else{
      p->aResult = aNew;
      p->nAlloc = n;
    }
  }
  p->aResult[p->nUsed++] = c;
}