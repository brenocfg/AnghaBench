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
 int MODE_ALL ; 
 int MODE_COUNT ; 

__attribute__((used)) static int allLoop(
  int iMode,                /* The selected test mode */
  int *piLoopCnt,           /* Iteration loop counter */
  int *piMode2,             /* The test mode to use on the next iteration */
  int *pUseWithoutRowid     /* Whether or not to use --without-rowid */
){
  int i;
  if( iMode!=MODE_ALL ){
    if( *piLoopCnt ) return 0;
    *piMode2 = iMode;
    *piLoopCnt = 1;
    return 1;
  }
  if( (*piLoopCnt)>=MODE_COUNT*2 ) return 0;
  i = (*piLoopCnt)++;
  *pUseWithoutRowid = i&1;
  *piMode2 = i>>1;
  return 1;
}