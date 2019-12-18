#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_4__ {int /*<<< orphan*/  nErr; } ;
typedef  TYPE_1__ JsonParse ;
typedef  int /*<<< orphan*/  JsonNode ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * jsonLookupStep (TYPE_1__*,int /*<<< orphan*/ ,char const*,int*,char const**) ; 
 char* jsonPathSyntaxError (char const*) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_error_nomem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static JsonNode *jsonLookup(
  JsonParse *pParse,      /* The JSON to search */
  const char *zPath,      /* The path to search */
  int *pApnd,             /* Append nodes to complete path if not NULL */
  sqlite3_context *pCtx   /* Report errors here, if not NULL */
){
  const char *zErr = 0;
  JsonNode *pNode = 0;
  char *zMsg;

  if( zPath==0 ) return 0;
  if( zPath[0]!='$' ){
    zErr = zPath;
    goto lookup_err;
  }
  zPath++;
  pNode = jsonLookupStep(pParse, 0, zPath, pApnd, &zErr);
  if( zErr==0 ) return pNode;

lookup_err:
  pParse->nErr++;
  assert( zErr!=0 && pCtx!=0 );
  zMsg = jsonPathSyntaxError(zErr);
  if( zMsg ){
    sqlite3_result_error(pCtx, zMsg, -1);
    sqlite3_free(zMsg);
  }else{
    sqlite3_result_error_nomem(pCtx);
  }
  return 0;
}