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
struct TYPE_7__ {scalar_t__ magic; int nOp; int nMem; scalar_t__ db; int pc; int cacheCtr; int minWriteFileFormat; TYPE_2__* aOp; scalar_t__ nFkConstraint; scalar_t__ iStatement; scalar_t__ nChange; int /*<<< orphan*/  errorAction; int /*<<< orphan*/  rc; TYPE_1__* aMem; } ;
typedef  TYPE_3__ Vdbe ;
struct TYPE_6__ {scalar_t__ cycles; scalar_t__ cnt; } ;
struct TYPE_5__ {scalar_t__ db; } ;

/* Variables and functions */
 int /*<<< orphan*/  OE_Abort ; 
 int /*<<< orphan*/  SQLITE_OK ; 
 scalar_t__ VDBE_MAGIC_INIT ; 
 scalar_t__ VDBE_MAGIC_RESET ; 
 scalar_t__ VDBE_MAGIC_RUN ; 
 int /*<<< orphan*/  assert (int) ; 

void sqlite3VdbeRewind(Vdbe *p){
#if defined(SQLITE_DEBUG) || defined(VDBE_PROFILE)
  int i;
#endif
  assert( p!=0 );
  assert( p->magic==VDBE_MAGIC_INIT || p->magic==VDBE_MAGIC_RESET );

  /* There should be at least one opcode.
  */
  assert( p->nOp>0 );

  /* Set the magic to VDBE_MAGIC_RUN sooner rather than later. */
  p->magic = VDBE_MAGIC_RUN;

#ifdef SQLITE_DEBUG
  for(i=0; i<p->nMem; i++){
    assert( p->aMem[i].db==p->db );
  }
#endif
  p->pc = -1;
  p->rc = SQLITE_OK;
  p->errorAction = OE_Abort;
  p->nChange = 0;
  p->cacheCtr = 1;
  p->minWriteFileFormat = 255;
  p->iStatement = 0;
  p->nFkConstraint = 0;
#ifdef VDBE_PROFILE
  for(i=0; i<p->nOp; i++){
    p->aOp[i].cnt = 0;
    p->aOp[i].cycles = 0;
  }
#endif
}