#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_7__ {size_t eType; } ;
struct TYPE_6__ {TYPE_2__* aNode; } ;
typedef  TYPE_1__ JsonParse ;
typedef  TYPE_2__ JsonNode ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_STATIC ; 
 TYPE_2__* jsonLookup (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* jsonParseCached (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsonType ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void jsonTypeFunc(
  sqlite3_context *ctx,
  int argc,
  sqlite3_value **argv
){
  JsonParse *p;          /* The parse */
  const char *zPath;
  JsonNode *pNode;

  p = jsonParseCached(ctx, argv, ctx);
  if( p==0 ) return;
  if( argc==2 ){
    zPath = (const char*)sqlite3_value_text(argv[1]);
    pNode = jsonLookup(p, zPath, 0, ctx);
  }else{
    pNode = p->aNode;
  }
  if( pNode ){
    sqlite3_result_text(ctx, jsonType[pNode->eType], -1, SQLITE_STATIC);
  }
}