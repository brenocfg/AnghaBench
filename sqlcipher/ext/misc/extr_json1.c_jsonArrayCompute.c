#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_3__ {int bErr; int bStatic; char* zBuf; scalar_t__ nUsed; int /*<<< orphan*/ * pCtx; } ;
typedef  TYPE_1__ JsonString ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_SUBTYPE ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  jsonAppendChar (TYPE_1__*,char) ; 
 scalar_t__ sqlite3_aggregate_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free ; 
 int /*<<< orphan*/  sqlite3_result_error_nomem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_subtype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jsonArrayCompute(sqlite3_context *ctx, int isFinal){
  JsonString *pStr;
  pStr = (JsonString*)sqlite3_aggregate_context(ctx, 0);
  if( pStr ){
    pStr->pCtx = ctx;
    jsonAppendChar(pStr, ']');
    if( pStr->bErr ){
      if( pStr->bErr==1 ) sqlite3_result_error_nomem(ctx);
      assert( pStr->bStatic );
    }else if( isFinal ){
      sqlite3_result_text(ctx, pStr->zBuf, (int)pStr->nUsed,
                          pStr->bStatic ? SQLITE_TRANSIENT : sqlite3_free);
      pStr->bStatic = 1;
    }else{
      sqlite3_result_text(ctx, pStr->zBuf, (int)pStr->nUsed, SQLITE_TRANSIENT);
      pStr->nUsed--;
    }
  }else{
    sqlite3_result_text(ctx, "[]", 2, SQLITE_STATIC);
  }
  sqlite3_result_subtype(ctx, JSON_SUBTYPE);
}