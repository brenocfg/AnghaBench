#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  nHeight; int /*<<< orphan*/  iRoot; } ;
struct TYPE_7__ {int /*<<< orphan*/  iNextShmid; int /*<<< orphan*/  nChunk; int /*<<< orphan*/  iWrite; TYPE_2__ root; } ;
struct TYPE_9__ {int /*<<< orphan*/  rollback; TYPE_1__ treehdr; } ;
typedef  TYPE_3__ lsm_db ;
struct TYPE_10__ {int /*<<< orphan*/  iRollback; int /*<<< orphan*/  iNextShmid; int /*<<< orphan*/  nChunk; int /*<<< orphan*/  iWrite; int /*<<< orphan*/  nHeight; int /*<<< orphan*/  iRoot; } ;
typedef  TYPE_4__ TreeMark ;

/* Variables and functions */
 int /*<<< orphan*/  intArraySize (int /*<<< orphan*/ *) ; 

void lsmTreeMark(lsm_db *pDb, TreeMark *pMark){
  pMark->iRoot = pDb->treehdr.root.iRoot;
  pMark->nHeight = pDb->treehdr.root.nHeight;
  pMark->iWrite = pDb->treehdr.iWrite;
  pMark->nChunk = pDb->treehdr.nChunk;
  pMark->iNextShmid = pDb->treehdr.iNextShmid;
  pMark->iRollback = intArraySize(&pDb->rollback);
}