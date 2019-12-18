#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_7__ {TYPE_2__* aFirst; TYPE_1__* aSeg; } ;
struct TYPE_6__ {size_t iFirst; } ;
struct TYPE_5__ {int /*<<< orphan*/  iRowid; int /*<<< orphan*/  pLeaf; } ;
typedef  TYPE_3__ Fts5Iter ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static i64 fts5MultiIterRowid(Fts5Iter *pIter){
  assert( pIter->aSeg[ pIter->aFirst[1].iFirst ].pLeaf );
  return pIter->aSeg[ pIter->aFirst[1].iFirst ].iRowid;
}