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
struct TYPE_12__ {scalar_t__ rc; } ;
struct TYPE_10__ {int bEof; } ;
struct TYPE_11__ {TYPE_3__ base; TYPE_2__* aFirst; TYPE_1__* aSeg; } ;
struct TYPE_9__ {size_t iFirst; } ;
struct TYPE_8__ {scalar_t__ pLeaf; } ;
typedef  TYPE_4__ Fts5Iter ;
typedef  TYPE_5__ Fts5Index ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int fts5MultiIterEof(Fts5Index *p, Fts5Iter *pIter){
  assert( p->rc 
      || (pIter->aSeg[ pIter->aFirst[1].iFirst ].pLeaf==0)==pIter->base.bEof 
  );
  return (p->rc || pIter->base.bEof);
}