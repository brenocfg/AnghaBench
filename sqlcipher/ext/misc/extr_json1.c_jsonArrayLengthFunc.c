#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  scalar_t__ sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_8__ {scalar_t__ eType; int jnFlags; size_t n; } ;
struct TYPE_7__ {int nNode; TYPE_2__* aNode; } ;
typedef  TYPE_1__ JsonParse ;
typedef  TYPE_2__ JsonNode ;

/* Variables and functions */
 int JNODE_APPEND ; 
 scalar_t__ JSON_ARRAY ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* jsonLookup (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ jsonNodeSize (TYPE_2__*) ; 
 TYPE_1__* jsonParseCached (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_int64 (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void jsonArrayLengthFunc(
  sqlite3_context *ctx,
  int argc,
  sqlite3_value **argv
){
  JsonParse *p;          /* The parse */
  sqlite3_int64 n = 0;
  u32 i;
  JsonNode *pNode;

  p = jsonParseCached(ctx, argv, ctx);
  if( p==0 ) return;
  assert( p->nNode );
  if( argc==2 ){
    const char *zPath = (const char*)sqlite3_value_text(argv[1]);
    pNode = jsonLookup(p, zPath, 0, ctx);
  }else{
    pNode = p->aNode;
  }
  if( pNode==0 ){
    return;
  }
  if( pNode->eType==JSON_ARRAY ){
    assert( (pNode->jnFlags & JNODE_APPEND)==0 );
    for(i=1; i<=pNode->n; n++){
      i += jsonNodeSize(&pNode[i]);
    }
  }
  sqlite3_result_int64(ctx, n);
}