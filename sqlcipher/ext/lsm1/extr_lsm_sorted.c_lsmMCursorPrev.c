#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ MultiCursor ;

/* Variables and functions */
 int CURSOR_PREV_OK ; 
 int LSM_MISUSE_BKPT ; 
 int multiCursorAdvance (TYPE_1__*,int) ; 

int lsmMCursorPrev(MultiCursor *pCsr){
  if( (pCsr->flags & CURSOR_PREV_OK)==0 ) return LSM_MISUSE_BKPT;
  return multiCursorAdvance(pCsr, 1);
}