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
typedef  int /*<<< orphan*/  yDbMask ;
struct TYPE_7__ {int /*<<< orphan*/  lockMask; TYPE_2__* db; int /*<<< orphan*/  btreeMask; } ;
typedef  TYPE_3__ Vdbe ;
struct TYPE_6__ {int nDb; TYPE_1__* aDb; } ;
struct TYPE_5__ {int /*<<< orphan*/  pBt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DbMaskSet (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3BtreeSharable (int /*<<< orphan*/ ) ; 

void sqlite3VdbeUsesBtree(Vdbe *p, int i){
  assert( i>=0 && i<p->db->nDb && i<(int)sizeof(yDbMask)*8 );
  assert( i<(int)sizeof(p->btreeMask)*8 );
  DbMaskSet(p->btreeMask, i);
  if( i!=1 && sqlite3BtreeSharable(p->db->aDb[i].pBt) ){
    DbMaskSet(p->lockMask, i);
  }
}