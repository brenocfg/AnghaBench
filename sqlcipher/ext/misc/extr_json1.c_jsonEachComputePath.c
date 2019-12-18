#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_6__ {size_t* aUp; TYPE_3__* aNode; } ;
struct TYPE_9__ {TYPE_1__ sParse; } ;
struct TYPE_7__ {scalar_t__ zJContent; int /*<<< orphan*/  iKey; } ;
struct TYPE_8__ {scalar_t__ eType; int jnFlags; int n; TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  JsonString ;
typedef  TYPE_3__ JsonNode ;
typedef  TYPE_4__ JsonEachCursor ;

/* Variables and functions */
 int JNODE_LABEL ; 
 scalar_t__ JSON_ARRAY ; 
 scalar_t__ JSON_OBJECT ; 
 scalar_t__ JSON_STRING ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  jsonAppendChar (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  jsonPrintf (int,int /*<<< orphan*/ *,char*,int,...) ; 

__attribute__((used)) static void jsonEachComputePath(
  JsonEachCursor *p,       /* The cursor */
  JsonString *pStr,        /* Write the path here */
  u32 i                    /* Path to this element */
){
  JsonNode *pNode, *pUp;
  u32 iUp;
  if( i==0 ){
    jsonAppendChar(pStr, '$');
    return;
  }
  iUp = p->sParse.aUp[i];
  jsonEachComputePath(p, pStr, iUp);
  pNode = &p->sParse.aNode[i];
  pUp = &p->sParse.aNode[iUp];
  if( pUp->eType==JSON_ARRAY ){
    jsonPrintf(30, pStr, "[%d]", pUp->u.iKey);
  }else{
    assert( pUp->eType==JSON_OBJECT );
    if( (pNode->jnFlags & JNODE_LABEL)==0 ) pNode--;
    assert( pNode->eType==JSON_STRING );
    assert( pNode->jnFlags & JNODE_LABEL );
    jsonPrintf(pNode->n+1, pStr, ".%.*s", pNode->n-2, pNode->u.zJContent+1);
  }
}