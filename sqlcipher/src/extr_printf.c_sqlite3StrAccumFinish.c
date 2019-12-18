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
struct TYPE_5__ {char* zText; size_t nChar; scalar_t__ mxAlloc; } ;
typedef  TYPE_1__ StrAccum ;

/* Variables and functions */
 int /*<<< orphan*/  isMalloced (TYPE_1__*) ; 
 char* strAccumFinishRealloc (TYPE_1__*) ; 

char *sqlite3StrAccumFinish(StrAccum *p){
  if( p->zText ){
    p->zText[p->nChar] = 0;
    if( p->mxAlloc>0 && !isMalloced(p) ){
      return strAccumFinishRealloc(p);
    }
  }
  return p->zText;
}