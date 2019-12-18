#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int isError; TYPE_4__* pOut; TYPE_1__* pVdbe; } ;
typedef  TYPE_2__ sqlite3_context ;
struct TYPE_7__ {int flags; } ;
struct TYPE_5__ {int rcApp; } ;

/* Variables and functions */
 int MEM_Null ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  SQLITE_UTF8 ; 
 int /*<<< orphan*/  sqlite3ErrStr (int) ; 
 int /*<<< orphan*/  sqlite3VdbeMemSetStr (TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sqlite3_result_error_code(sqlite3_context *pCtx, int errCode){
  pCtx->isError = errCode ? errCode : -1;
#ifdef SQLITE_DEBUG
  if( pCtx->pVdbe ) pCtx->pVdbe->rcApp = errCode;
#endif
  if( pCtx->pOut->flags & MEM_Null ){
    sqlite3VdbeMemSetStr(pCtx->pOut, sqlite3ErrStr(errCode), -1, 
                         SQLITE_UTF8, SQLITE_STATIC);
  }
}