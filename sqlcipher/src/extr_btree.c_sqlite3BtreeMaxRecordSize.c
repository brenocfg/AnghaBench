#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int sqlite3_int64 ;
struct TYPE_6__ {scalar_t__ eState; TYPE_1__* pBt; } ;
struct TYPE_5__ {int pageSize; scalar_t__ nPage; } ;
typedef  TYPE_2__ BtCursor ;

/* Variables and functions */
 scalar_t__ CURSOR_VALID ; 
 int /*<<< orphan*/  assert (int) ; 
 int cursorHoldsMutex (TYPE_2__*) ; 

sqlite3_int64 sqlite3BtreeMaxRecordSize(BtCursor *pCur){
  assert( cursorHoldsMutex(pCur) );
  assert( pCur->eState==CURSOR_VALID );
  return pCur->pBt->pageSize * (sqlite3_int64)pCur->pBt->nPage;
}