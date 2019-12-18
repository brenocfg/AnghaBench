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
struct TYPE_4__ {int flags; int* aTree; int /*<<< orphan*/ * apTreeCsr; } ;
typedef  TYPE_1__ MultiCursor ;

/* Variables and functions */
 int CURSOR_DATA_TREE0 ; 
 int CURSOR_DATA_TREE1 ; 
 int CURSOR_SEEK_EQ ; 
 int lsmTreeCursorValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multiCursorGetKey (TYPE_1__*,int,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 

int lsmMCursorValid(MultiCursor *pCsr){
  int res = 0;
  if( pCsr->flags & CURSOR_SEEK_EQ ){
    res = 1;
  }else if( pCsr->aTree ){
    int iKey = pCsr->aTree[1];
    if( iKey==CURSOR_DATA_TREE0 || iKey==CURSOR_DATA_TREE1 ){
      res = lsmTreeCursorValid(pCsr->apTreeCsr[iKey-CURSOR_DATA_TREE0]);
    }else{
      void *pKey; 
      multiCursorGetKey(pCsr, iKey, 0, &pKey, 0);
      res = pKey!=0;
    }
  }
  return res;
}