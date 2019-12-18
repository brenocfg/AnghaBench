#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_11__ {size_t iReplace; } ;
struct TYPE_14__ {int jnFlags; TYPE_2__ u; } ;
struct TYPE_10__ {int iReplace; } ;
struct TYPE_13__ {TYPE_1__ u; int /*<<< orphan*/  jnFlags; } ;
struct TYPE_12__ {TYPE_5__* aNode; scalar_t__ nErr; int /*<<< orphan*/  nNode; } ;
typedef  TYPE_3__ JsonParse ;
typedef  TYPE_4__ JsonNode ;

/* Variables and functions */
 int JNODE_REPLACE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_4__* jsonLookup (TYPE_3__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ jsonParse (TYPE_3__*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  jsonParseReset (TYPE_3__*) ; 
 int /*<<< orphan*/  jsonReturnJson (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  jsonWrongNumArgs (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sqlite3_result_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void jsonReplaceFunc(
  sqlite3_context *ctx,
  int argc,
  sqlite3_value **argv
){
  JsonParse x;          /* The parse */
  JsonNode *pNode;
  const char *zPath;
  u32 i;

  if( argc<1 ) return;
  if( (argc&1)==0 ) {
    jsonWrongNumArgs(ctx, "replace");
    return;
  }
  if( jsonParse(&x, ctx, (const char*)sqlite3_value_text(argv[0])) ) return;
  assert( x.nNode );
  for(i=1; i<(u32)argc; i+=2){
    zPath = (const char*)sqlite3_value_text(argv[i]);
    pNode = jsonLookup(&x, zPath, 0, ctx);
    if( x.nErr ) goto replace_err;
    if( pNode ){
      pNode->jnFlags |= (u8)JNODE_REPLACE;
      pNode->u.iReplace = i + 1;
    }
  }
  if( x.aNode[0].jnFlags & JNODE_REPLACE ){
    sqlite3_result_value(ctx, argv[x.aNode[0].u.iReplace]);
  }else{
    jsonReturnJson(x.aNode, ctx, argv);
  }
replace_err:
  jsonParseReset(&x);
}