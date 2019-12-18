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
struct TYPE_7__ {int /*<<< orphan*/  root; int /*<<< orphan*/  oldroot; } ;
struct TYPE_8__ {TYPE_1__ treehdr; } ;
typedef  TYPE_2__ lsm_db ;
struct TYPE_9__ {int iNode; int /*<<< orphan*/ * pRoot; TYPE_2__* pDb; } ;
typedef  TYPE_3__ TreeCursor ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void treeCursorInit(lsm_db *pDb, int bOld, TreeCursor *pCsr){
  memset(pCsr, 0, sizeof(TreeCursor));
  pCsr->pDb = pDb;
  if( bOld ){
    pCsr->pRoot = &pDb->treehdr.oldroot;
  }else{
    pCsr->pRoot = &pDb->treehdr.root;
  }
  pCsr->iNode = -1;
}