#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_5__ {int nTab; } ;
typedef  TYPE_1__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  MASTER_NAME ; 
 int /*<<< orphan*/  MASTER_ROOT ; 
 int /*<<< orphan*/  OP_OpenWrite ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3TableLock (TYPE_1__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4Int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void sqlite3OpenMasterTable(Parse *p, int iDb){
  Vdbe *v = sqlite3GetVdbe(p);
  sqlite3TableLock(p, iDb, MASTER_ROOT, 1, MASTER_NAME);
  sqlite3VdbeAddOp4Int(v, OP_OpenWrite, 0, MASTER_ROOT, iDb, 5);
  if( p->nTab==0 ){
    p->nTab = 1;
  }
}