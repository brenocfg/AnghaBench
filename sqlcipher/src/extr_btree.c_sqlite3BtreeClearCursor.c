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
struct TYPE_4__ {int /*<<< orphan*/  eState; scalar_t__ pKey; } ;
typedef  TYPE_1__ BtCursor ;

/* Variables and functions */
 int /*<<< orphan*/  CURSOR_INVALID ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cursorHoldsMutex (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_free (scalar_t__) ; 

void sqlite3BtreeClearCursor(BtCursor *pCur){
  assert( cursorHoldsMutex(pCur) );
  sqlite3_free(pCur->pKey);
  pCur->pKey = 0;
  pCur->eState = CURSOR_INVALID;
}