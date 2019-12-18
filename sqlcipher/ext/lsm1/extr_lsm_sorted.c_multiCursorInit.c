#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  TYPE_1__ MultiCursor ;

/* Variables and functions */
 int CURSOR_IGNORE_DELETE ; 
 int CURSOR_IGNORE_SYSTEM ; 
 int LSM_OK ; 
 int /*<<< orphan*/  TREE_BOTH ; 
 int multiCursorAddAll (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int multiCursorAddTree (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int multiCursorInit(MultiCursor *pCsr, Snapshot *pSnap){
  int rc;
  rc = multiCursorAddAll(pCsr, pSnap);
  if( rc==LSM_OK ){
    rc = multiCursorAddTree(pCsr, pSnap, TREE_BOTH);
  }
  pCsr->flags |= (CURSOR_IGNORE_SYSTEM | CURSOR_IGNORE_DELETE);
  return rc;
}