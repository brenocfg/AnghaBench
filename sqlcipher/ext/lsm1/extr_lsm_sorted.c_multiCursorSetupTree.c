#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nTree; } ;
typedef  TYPE_1__ MultiCursor ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  assertCursorTree (TYPE_1__*) ; 
 scalar_t__ mcursorLocationOk (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int multiCursorAdvance (TYPE_1__*,int) ; 
 int multiCursorAllocTree (TYPE_1__*) ; 
 int /*<<< orphan*/  multiCursorCacheKey (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  multiCursorDoCompare (TYPE_1__*,int,int) ; 

__attribute__((used)) static int multiCursorSetupTree(MultiCursor *pCsr, int bRev){
  int rc;

  rc = multiCursorAllocTree(pCsr);
  if( rc==LSM_OK ){
    int i;
    for(i=pCsr->nTree-1; i>0; i--){
      multiCursorDoCompare(pCsr, i, bRev);
    }
  }

  assertCursorTree(pCsr);
  multiCursorCacheKey(pCsr, &rc);

  if( rc==LSM_OK && mcursorLocationOk(pCsr, 0)==0 ){
    rc = multiCursorAdvance(pCsr, bRev);
  }
  return rc;
}