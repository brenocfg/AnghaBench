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
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_5__ {scalar_t__ zBuf; int /*<<< orphan*/ * pCtx; } ;
typedef  TYPE_1__ JsonString ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAM (int) ; 
 int /*<<< orphan*/  jsonAppendChar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  jsonAppendValue (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsonInit (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_aggregate_context (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void jsonArrayStep(
  sqlite3_context *ctx,
  int argc,
  sqlite3_value **argv
){
  JsonString *pStr;
  UNUSED_PARAM(argc);
  pStr = (JsonString*)sqlite3_aggregate_context(ctx, sizeof(*pStr));
  if( pStr ){
    if( pStr->zBuf==0 ){
      jsonInit(pStr, ctx);
      jsonAppendChar(pStr, '[');
    }else{
      jsonAppendChar(pStr, ',');
      pStr->pCtx = ctx;
    }
    jsonAppendValue(pStr, argv[0]);
  }
}