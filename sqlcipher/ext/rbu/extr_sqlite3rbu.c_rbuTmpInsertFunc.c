#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ eType; int /*<<< orphan*/  pTmpInsert; scalar_t__ nIndex; } ;
struct TYPE_5__ {TYPE_1__ objiter; int /*<<< orphan*/  nPhaseOneStep; } ;
typedef  TYPE_2__ sqlite3rbu ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 scalar_t__ RBU_PK_EXTERNAL ; 
 scalar_t__ RBU_PK_NONE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3_bind_value (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int sqlite3_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_error_code (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_step (int /*<<< orphan*/ ) ; 
 TYPE_2__* sqlite3_user_data (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_int (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rbuTmpInsertFunc(
  sqlite3_context *pCtx, 
  int nVal,
  sqlite3_value **apVal
){
  sqlite3rbu *p = sqlite3_user_data(pCtx);
  int rc = SQLITE_OK;
  int i;

  assert( sqlite3_value_int(apVal[0])!=0
      || p->objiter.eType==RBU_PK_EXTERNAL 
      || p->objiter.eType==RBU_PK_NONE 
  );
  if( sqlite3_value_int(apVal[0])!=0 ){
    p->nPhaseOneStep += p->objiter.nIndex;
  }

  for(i=0; rc==SQLITE_OK && i<nVal; i++){
    rc = sqlite3_bind_value(p->objiter.pTmpInsert, i+1, apVal[i]);
  }
  if( rc==SQLITE_OK ){
    sqlite3_step(p->objiter.pTmpInsert);
    rc = sqlite3_reset(p->objiter.pTmpInsert);
  }

  if( rc!=SQLITE_OK ){
    sqlite3_result_error_code(pCtx, rc);
  }
}