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
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_4__ {scalar_t__ nErr; } ;
typedef  int /*<<< orphan*/  JsonString ;
typedef  TYPE_1__ JsonParse ;
typedef  int /*<<< orphan*/  JsonNode ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_SUBTYPE ; 
 int /*<<< orphan*/  jsonAppendChar (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  jsonAppendRaw (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  jsonAppendSeparator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsonInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsonLookup (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* jsonParseCached (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsonRenderNode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonReset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsonResult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsonReturn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_subtype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void jsonExtractFunc(
  sqlite3_context *ctx,
  int argc,
  sqlite3_value **argv
){
  JsonParse *p;          /* The parse */
  JsonNode *pNode;
  const char *zPath;
  JsonString jx;
  int i;

  if( argc<2 ) return;
  p = jsonParseCached(ctx, argv, ctx);
  if( p==0 ) return;
  jsonInit(&jx, ctx);
  jsonAppendChar(&jx, '[');
  for(i=1; i<argc; i++){
    zPath = (const char*)sqlite3_value_text(argv[i]);
    pNode = jsonLookup(p, zPath, 0, ctx);
    if( p->nErr ) break;
    if( argc>2 ){
      jsonAppendSeparator(&jx);
      if( pNode ){
        jsonRenderNode(pNode, &jx, 0);
      }else{
        jsonAppendRaw(&jx, "null", 4);
      }
    }else if( pNode ){
      jsonReturn(pNode, ctx, 0);
    }
  }
  if( argc>2 && i==argc ){
    jsonAppendChar(&jx, ']');
    jsonResult(&jx);
    sqlite3_result_subtype(ctx, JSON_SUBTYPE);
  }
  jsonReset(&jx);
}