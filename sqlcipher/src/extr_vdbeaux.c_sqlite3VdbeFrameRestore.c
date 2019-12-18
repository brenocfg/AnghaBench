#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int pc; scalar_t__ pAuxData; int /*<<< orphan*/  nDbChange; int /*<<< orphan*/  nChange; int /*<<< orphan*/  lastRowid; int /*<<< orphan*/  nCursor; int /*<<< orphan*/  apCsr; int /*<<< orphan*/  nMem; int /*<<< orphan*/  aMem; int /*<<< orphan*/  nOp; int /*<<< orphan*/  aOp; int /*<<< orphan*/  anExec; TYPE_2__* v; } ;
typedef  TYPE_1__ VdbeFrame ;
struct TYPE_7__ {scalar_t__ pAuxData; TYPE_4__* db; int /*<<< orphan*/  nChange; int /*<<< orphan*/  nCursor; int /*<<< orphan*/  apCsr; int /*<<< orphan*/  nMem; int /*<<< orphan*/  aMem; int /*<<< orphan*/  nOp; int /*<<< orphan*/  aOp; int /*<<< orphan*/  anExec; } ;
typedef  TYPE_2__ Vdbe ;
struct TYPE_8__ {int /*<<< orphan*/  nChange; int /*<<< orphan*/  lastRowid; } ;

/* Variables and functions */
 int /*<<< orphan*/  closeCursorsInFrame (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3VdbeDeleteAuxData (TYPE_4__*,scalar_t__*,int,int /*<<< orphan*/ ) ; 

int sqlite3VdbeFrameRestore(VdbeFrame *pFrame){
  Vdbe *v = pFrame->v;
  closeCursorsInFrame(v);
#ifdef SQLITE_ENABLE_STMT_SCANSTATUS
  v->anExec = pFrame->anExec;
#endif
  v->aOp = pFrame->aOp;
  v->nOp = pFrame->nOp;
  v->aMem = pFrame->aMem;
  v->nMem = pFrame->nMem;
  v->apCsr = pFrame->apCsr;
  v->nCursor = pFrame->nCursor;
  v->db->lastRowid = pFrame->lastRowid;
  v->nChange = pFrame->nChange;
  v->db->nChange = pFrame->nDbChange;
  sqlite3VdbeDeleteAuxData(v->db, &v->pAuxData, -1, 0);
  v->pAuxData = pFrame->pAuxData;
  pFrame->pAuxData = 0;
  return pFrame->pc;
}