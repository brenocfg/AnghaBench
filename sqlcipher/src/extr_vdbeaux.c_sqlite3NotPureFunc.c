#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t iOp; TYPE_2__* pVdbe; } ;
typedef  TYPE_3__ sqlite3_context ;
struct TYPE_7__ {TYPE_1__* aOp; } ;
struct TYPE_6__ {scalar_t__ opcode; } ;

/* Variables and functions */
 scalar_t__ OP_PureFunc ; 
 int /*<<< orphan*/  sqlite3_result_error (TYPE_3__*,char*,int) ; 

int sqlite3NotPureFunc(sqlite3_context *pCtx){
#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
  if( pCtx->pVdbe==0 ) return 1;
#endif
  if( pCtx->pVdbe->aOp[pCtx->iOp].opcode==OP_PureFunc ){
    sqlite3_result_error(pCtx, 
       "non-deterministic function in index expression or CHECK constraint",
       -1);
    return 0;
  }
  return 1;
}