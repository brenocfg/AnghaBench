#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {scalar_t__ eState; } ;
typedef  TYPE_1__ BtCursor ;

/* Variables and functions */
 scalar_t__ CURSOR_VALID ; 
 int accessPayload (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int accessPayloadChecked (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cursorOwnsBtShared (TYPE_1__*) ; 

int sqlite3BtreePayloadChecked(BtCursor *pCur, u32 offset, u32 amt, void *pBuf){
  if( pCur->eState==CURSOR_VALID ){
    assert( cursorOwnsBtShared(pCur) );
    return accessPayload(pCur, offset, amt, pBuf, 0);
  }else{
    return accessPayloadChecked(pCur, offset, amt, pBuf);
  }
}