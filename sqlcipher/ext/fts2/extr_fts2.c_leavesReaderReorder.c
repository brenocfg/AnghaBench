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
typedef  int /*<<< orphan*/  LeavesReader ;

/* Variables and functions */
 scalar_t__ leavesReaderCmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void leavesReaderReorder(LeavesReader *pLr, int nLr){
  while( nLr>1 && leavesReaderCmp(pLr, pLr+1)>0 ){
    LeavesReader tmp = pLr[0];
    pLr[0] = pLr[1];
    pLr[1] = tmp;
    nLr--;
    pLr++;
  }
}