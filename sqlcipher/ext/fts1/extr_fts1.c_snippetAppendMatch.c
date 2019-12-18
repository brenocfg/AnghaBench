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
struct snippetMatch {int iCol; int iTerm; int iStart; int nByte; } ;
struct TYPE_3__ {int nMatch; int nAlloc; struct snippetMatch* aMatch; } ;
typedef  TYPE_1__ Snippet ;

/* Variables and functions */
 struct snippetMatch* realloc (struct snippetMatch*,int) ; 

__attribute__((used)) static void snippetAppendMatch(
  Snippet *p,               /* Append the entry to this snippet */
  int iCol, int iTerm,      /* The column and query term */
  int iStart, int nByte     /* Offset and size of the match */
){
  int i;
  struct snippetMatch *pMatch;
  if( p->nMatch+1>=p->nAlloc ){
    p->nAlloc = p->nAlloc*2 + 10;
    p->aMatch = realloc(p->aMatch, p->nAlloc*sizeof(p->aMatch[0]) );
    if( p->aMatch==0 ){
      p->nMatch = 0;
      p->nAlloc = 0;
      return;
    }
  }
  i = p->nMatch++;
  pMatch = &p->aMatch[i];
  pMatch->iCol = iCol;
  pMatch->iTerm = iTerm;
  pMatch->iStart = iStart;
  pMatch->nByte = nByte;
}