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
struct TYPE_5__ {int /*<<< orphan*/  pCursor; } ;
struct TYPE_6__ {scalar_t__ eCurType; TYPE_1__ uc; } ;
typedef  TYPE_2__ VdbeCursor ;

/* Variables and functions */
 scalar_t__ CURTYPE_BTREE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int handleMovedCursor (TYPE_2__*) ; 
 scalar_t__ sqlite3BtreeCursorHasMoved (int /*<<< orphan*/ ) ; 

int sqlite3VdbeCursorRestore(VdbeCursor *p){
  assert( p->eCurType==CURTYPE_BTREE );
  if( sqlite3BtreeCursorHasMoved(p->uc.pCursor) ){
    return handleMovedCursor(p);
  }
  return SQLITE_OK;
}