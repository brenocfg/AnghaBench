#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_9__ {scalar_t__ pPayload; scalar_t__ nLocal; scalar_t__ nPayload; int /*<<< orphan*/  nKey; scalar_t__ nSize; } ;
struct TYPE_8__ {scalar_t__ leaf; int childPtrSize; TYPE_1__* pBt; } ;
struct TYPE_7__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ MemPage ;
typedef  TYPE_3__ CellInfo ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ getVarint (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btreeParseCellPtrNoPayload(
  MemPage *pPage,         /* Page containing the cell */
  u8 *pCell,              /* Pointer to the cell text. */
  CellInfo *pInfo         /* Fill in this structure */
){
  assert( sqlite3_mutex_held(pPage->pBt->mutex) );
  assert( pPage->leaf==0 );
  assert( pPage->childPtrSize==4 );
#ifndef SQLITE_DEBUG
  UNUSED_PARAMETER(pPage);
#endif
  pInfo->nSize = 4 + getVarint(&pCell[4], (u64*)&pInfo->nKey);
  pInfo->nPayload = 0;
  pInfo->nLocal = 0;
  pInfo->pPayload = 0;
  return;
}