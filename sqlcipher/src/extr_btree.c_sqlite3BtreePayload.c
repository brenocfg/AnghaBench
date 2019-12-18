#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {scalar_t__ eState; scalar_t__ iPage; scalar_t__ ix; TYPE_1__* pPage; } ;
struct TYPE_6__ {scalar_t__ nCell; } ;
typedef  TYPE_2__ BtCursor ;

/* Variables and functions */
 scalar_t__ CURSOR_VALID ; 
 int accessPayload (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int cursorHoldsMutex (TYPE_2__*) ; 

int sqlite3BtreePayload(BtCursor *pCur, u32 offset, u32 amt, void *pBuf){
  assert( cursorHoldsMutex(pCur) );
  assert( pCur->eState==CURSOR_VALID );
  assert( pCur->iPage>=0 && pCur->pPage );
  assert( pCur->ix<pCur->pPage->nCell );
  return accessPayload(pCur, offset, amt, (unsigned char*)pBuf, 0);
}