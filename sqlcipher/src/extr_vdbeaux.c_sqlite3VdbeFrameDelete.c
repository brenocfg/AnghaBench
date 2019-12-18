#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t nChildMem; int nChildCsr; TYPE_2__* v; int /*<<< orphan*/  pAuxData; } ;
typedef  TYPE_1__ VdbeFrame ;
typedef  int /*<<< orphan*/  VdbeCursor ;
struct TYPE_8__ {int /*<<< orphan*/  db; } ;
typedef  int /*<<< orphan*/  Mem ;

/* Variables and functions */
 int /*<<< orphan*/ * VdbeFrameMem (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  releaseMemArray (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3VdbeDeleteAuxData (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeFrameIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3VdbeFreeCursor (TYPE_2__*,int /*<<< orphan*/ *) ; 

void sqlite3VdbeFrameDelete(VdbeFrame *p){
  int i;
  Mem *aMem = VdbeFrameMem(p);
  VdbeCursor **apCsr = (VdbeCursor **)&aMem[p->nChildMem];
  assert( sqlite3VdbeFrameIsValid(p) );
  for(i=0; i<p->nChildCsr; i++){
    sqlite3VdbeFreeCursor(p->v, apCsr[i]);
  }
  releaseMemArray(aMem, p->nChildMem);
  sqlite3VdbeDeleteAuxData(p->v->db, &p->pAuxData, -1, 0);
  sqlite3DbFree(p->v->db, p);
}