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
struct TYPE_5__ {scalar_t__ oom; int /*<<< orphan*/  aNode; } ;
typedef  TYPE_1__ JsonParse ;
typedef  int /*<<< orphan*/  JsonNode ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAM (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * jsonMergePatch (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jsonParse (TYPE_1__*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  jsonParseReset (TYPE_1__*) ; 
 int /*<<< orphan*/  jsonReturnJson (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_error_nomem (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void jsonPatchFunc(
  sqlite3_context *ctx,
  int argc,
  sqlite3_value **argv
){
  JsonParse x;     /* The JSON that is being patched */
  JsonParse y;     /* The patch */
  JsonNode *pResult;   /* The result of the merge */

  UNUSED_PARAM(argc);
  if( jsonParse(&x, ctx, (const char*)sqlite3_value_text(argv[0])) ) return;
  if( jsonParse(&y, ctx, (const char*)sqlite3_value_text(argv[1])) ){
    jsonParseReset(&x);
    return;
  }
  pResult = jsonMergePatch(&x, 0, y.aNode);
  assert( pResult!=0 || x.oom );
  if( pResult ){
    jsonReturnJson(pResult, ctx, 0);
  }else{
    sqlite3_result_error_nomem(ctx);
  }
  jsonParseReset(&x);
  jsonParseReset(&y);
}