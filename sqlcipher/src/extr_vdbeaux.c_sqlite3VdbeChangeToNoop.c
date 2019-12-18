#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ z; int /*<<< orphan*/  p; } ;
struct TYPE_7__ {int /*<<< orphan*/  opcode; TYPE_1__ p4; int /*<<< orphan*/  p4type; } ;
typedef  TYPE_2__ VdbeOp ;
struct TYPE_8__ {int nOp; TYPE_5__* db; TYPE_2__* aOp; } ;
typedef  TYPE_3__ Vdbe ;
struct TYPE_9__ {scalar_t__ mallocFailed; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_Noop ; 
 int /*<<< orphan*/  P4_NOTUSED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  freeP4 (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sqlite3VdbeChangeToNoop(Vdbe *p, int addr){
  VdbeOp *pOp;
  if( p->db->mallocFailed ) return 0;
  assert( addr>=0 && addr<p->nOp );
  pOp = &p->aOp[addr];
  freeP4(p->db, pOp->p4type, pOp->p4.p);
  pOp->p4type = P4_NOTUSED;
  pOp->p4.z = 0;
  pOp->opcode = OP_Noop;
  return 1;
}