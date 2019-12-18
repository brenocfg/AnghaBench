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
struct TYPE_6__ {scalar_t__ rc; } ;
struct TYPE_5__ {TYPE_2__* pIndex; } ;
typedef  TYPE_1__ Fts5Iter ;
typedef  int /*<<< orphan*/  Fts5IndexIter ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts5IndexReturn (TYPE_2__*) ; 
 int /*<<< orphan*/  fts5MultiIterNext (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sqlite3Fts5IterNext(Fts5IndexIter *pIndexIter){
  Fts5Iter *pIter = (Fts5Iter*)pIndexIter;
  assert( pIter->pIndex->rc==SQLITE_OK );
  fts5MultiIterNext(pIter->pIndex, pIter, 0, 0);
  return fts5IndexReturn(pIter->pIndex);
}