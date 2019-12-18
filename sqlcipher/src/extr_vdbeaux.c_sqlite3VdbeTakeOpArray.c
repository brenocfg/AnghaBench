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
typedef  int /*<<< orphan*/  VdbeOp ;
struct TYPE_6__ {int nOp; int /*<<< orphan*/ * aOp; int /*<<< orphan*/  btreeMask; TYPE_1__* db; } ;
typedef  TYPE_2__ Vdbe ;
struct TYPE_5__ {int /*<<< orphan*/  mallocFailed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DbMaskAllZero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resolveP2Values (TYPE_2__*,int*) ; 

VdbeOp *sqlite3VdbeTakeOpArray(Vdbe *p, int *pnOp, int *pnMaxArg){
  VdbeOp *aOp = p->aOp;
  assert( aOp && !p->db->mallocFailed );

  /* Check that sqlite3VdbeUsesBtree() was not called on this VM */
  assert( DbMaskAllZero(p->btreeMask) );

  resolveP2Values(p, pnMaxArg);
  *pnOp = p->nOp;
  p->aOp = 0;
  return aOp;
}