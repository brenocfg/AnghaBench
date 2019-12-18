#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int i64 ;
struct TYPE_12__ {scalar_t__ eState; size_t iPage; TYPE_2__** apPage; TYPE_1__* pPage; TYPE_4__* pBtree; } ;
struct TYPE_11__ {TYPE_3__* db; } ;
struct TYPE_10__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_9__ {int nCell; } ;
struct TYPE_8__ {scalar_t__ leaf; int nCell; } ;
typedef  TYPE_5__ BtCursor ;

/* Variables and functions */
 scalar_t__ CURSOR_VALID ; 
 scalar_t__ NEVER (int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cursorOwnsBtShared (TYPE_5__*) ; 
 int /*<<< orphan*/  sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

i64 sqlite3BtreeRowCountEst(BtCursor *pCur){
  i64 n;
  u8 i;

  assert( cursorOwnsBtShared(pCur) );
  assert( sqlite3_mutex_held(pCur->pBtree->db->mutex) );

  /* Currently this interface is only called by the OP_IfSmaller
  ** opcode, and it that case the cursor will always be valid and
  ** will always point to a leaf node. */
  if( NEVER(pCur->eState!=CURSOR_VALID) ) return -1;
  if( NEVER(pCur->pPage->leaf==0) ) return -1;

  n = pCur->pPage->nCell;
  for(i=0; i<pCur->iPage; i++){
    n *= pCur->apPage[i]->nCell;
  }
  return n;
}