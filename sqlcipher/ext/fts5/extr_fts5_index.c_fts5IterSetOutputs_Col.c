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
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  n; int /*<<< orphan*/  p; } ;
struct TYPE_9__ {int /*<<< orphan*/  nData; int /*<<< orphan*/  pData; int /*<<< orphan*/  iRowid; } ;
struct TYPE_11__ {TYPE_5__ poslist; TYPE_1__ base; int /*<<< orphan*/  pColset; int /*<<< orphan*/  pIndex; } ;
struct TYPE_10__ {int /*<<< orphan*/  iRowid; } ;
typedef  TYPE_2__ Fts5SegIter ;
typedef  TYPE_3__ Fts5Iter ;

/* Variables and functions */
 int /*<<< orphan*/  fts5BufferZero (TYPE_5__*) ; 
 int /*<<< orphan*/  fts5SegiterPoslist (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static void fts5IterSetOutputs_Col(Fts5Iter *pIter, Fts5SegIter *pSeg){
  fts5BufferZero(&pIter->poslist);
  fts5SegiterPoslist(pIter->pIndex, pSeg, pIter->pColset, &pIter->poslist);
  pIter->base.iRowid = pSeg->iRowid;
  pIter->base.pData = pIter->poslist.p;
  pIter->base.nData = pIter->poslist.n;
}