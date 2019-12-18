#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_6__ {char const* zJson; scalar_t__ iDepth; scalar_t__ oom; } ;
typedef  TYPE_1__ JsonParse ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  jsonParseReset (TYPE_1__*) ; 
 int jsonParseValue (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ safe_isspace (char const) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_error_nomem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int jsonParse(
  JsonParse *pParse,           /* Initialize and fill this JsonParse object */
  sqlite3_context *pCtx,       /* Report errors here */
  const char *zJson            /* Input JSON text to be parsed */
){
  int i;
  memset(pParse, 0, sizeof(*pParse));
  if( zJson==0 ) return 1;
  pParse->zJson = zJson;
  i = jsonParseValue(pParse, 0);
  if( pParse->oom ) i = -1;
  if( i>0 ){
    assert( pParse->iDepth==0 );
    while( safe_isspace(zJson[i]) ) i++;
    if( zJson[i] ) i = -1;
  }
  if( i<=0 ){
    if( pCtx!=0 ){
      if( pParse->oom ){
        sqlite3_result_error_nomem(pCtx);
      }else{
        sqlite3_result_error(pCtx, "malformed JSON", -1);
      }
    }
    jsonParseReset(pParse);
    return 1;
  }
  return 0;
}