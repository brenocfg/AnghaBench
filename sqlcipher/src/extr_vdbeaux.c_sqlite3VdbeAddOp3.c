#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_8__ {scalar_t__ p; } ;
struct TYPE_10__ {int p1; int p2; int p3; scalar_t__ iSrcLine; scalar_t__ cnt; scalar_t__ cycles; scalar_t__ zComment; int /*<<< orphan*/  p4type; TYPE_1__ p4; scalar_t__ p5; scalar_t__ opcode; } ;
typedef  TYPE_3__ VdbeOp ;
struct TYPE_11__ {int nOp; scalar_t__ magic; int nOpAlloc; TYPE_3__* aOp; TYPE_2__* db; } ;
typedef  TYPE_4__ Vdbe ;
struct TYPE_9__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  P4_NOTUSED ; 
 int SQLITE_VdbeAddopTrace ; 
 scalar_t__ VDBE_MAGIC_INIT ; 
 int /*<<< orphan*/  assert (int) ; 
 int growOp3 (TYPE_4__*,int,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbePrintOp (int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 int /*<<< orphan*/  test_addop_breakpoint () ; 

int sqlite3VdbeAddOp3(Vdbe *p, int op, int p1, int p2, int p3){
  int i;
  VdbeOp *pOp;

  i = p->nOp;
  assert( p->magic==VDBE_MAGIC_INIT );
  assert( op>=0 && op<0xff );
  if( p->nOpAlloc<=i ){
    return growOp3(p, op, p1, p2, p3);
  }
  p->nOp++;
  pOp = &p->aOp[i];
  pOp->opcode = (u8)op;
  pOp->p5 = 0;
  pOp->p1 = p1;
  pOp->p2 = p2;
  pOp->p3 = p3;
  pOp->p4.p = 0;
  pOp->p4type = P4_NOTUSED;
#ifdef SQLITE_ENABLE_EXPLAIN_COMMENTS
  pOp->zComment = 0;
#endif
#ifdef SQLITE_DEBUG
  if( p->db->flags & SQLITE_VdbeAddopTrace ){
    sqlite3VdbePrintOp(0, i, &p->aOp[i]);
    test_addop_breakpoint();
  }
#endif
#ifdef VDBE_PROFILE
  pOp->cycles = 0;
  pOp->cnt = 0;
#endif
#ifdef SQLITE_VDBE_COVERAGE
  pOp->iSrcLine = 0;
#endif
  return i;
}