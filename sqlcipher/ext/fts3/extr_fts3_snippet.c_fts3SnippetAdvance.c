#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  fts3GetDeltaPosition (char**,int*) ; 

__attribute__((used)) static void fts3SnippetAdvance(char **ppIter, int *piIter, int iNext){
  char *pIter = *ppIter;
  if( pIter ){
    int iIter = *piIter;

    while( iIter<iNext ){
      if( 0==(*pIter & 0xFE) ){
        iIter = -1;
        pIter = 0;
        break;
      }
      fts3GetDeltaPosition(&pIter, &iIter);
    }

    *piIter = iIter;
    *ppIter = pIter;
  }
}