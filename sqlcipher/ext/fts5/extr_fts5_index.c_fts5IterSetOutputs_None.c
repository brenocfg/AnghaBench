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
struct TYPE_10__ {int /*<<< orphan*/  nData; int /*<<< orphan*/  iRowid; } ;
struct TYPE_12__ {TYPE_3__ base; TYPE_2__* pIndex; } ;
struct TYPE_11__ {int /*<<< orphan*/  nPos; int /*<<< orphan*/  iRowid; } ;
struct TYPE_9__ {TYPE_1__* pConfig; } ;
struct TYPE_8__ {scalar_t__ eDetail; } ;
typedef  TYPE_4__ Fts5SegIter ;
typedef  TYPE_5__ Fts5Iter ;

/* Variables and functions */
 scalar_t__ FTS5_DETAIL_NONE ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void fts5IterSetOutputs_None(Fts5Iter *pIter, Fts5SegIter *pSeg){
  assert( pIter->pIndex->pConfig->eDetail==FTS5_DETAIL_NONE );
  pIter->base.iRowid = pSeg->iRowid;
  pIter->base.nData = pSeg->nPos;
}