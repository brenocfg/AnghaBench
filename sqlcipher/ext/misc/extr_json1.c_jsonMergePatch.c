#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_10__ {char* zJContent; int iAppend; TYPE_3__* pPatch; } ;
struct TYPE_12__ {scalar_t__ eType; int jnFlags; size_t n; TYPE_1__ u; } ;
struct TYPE_11__ {size_t nNode; TYPE_3__* aNode; scalar_t__ oom; } ;
typedef  TYPE_2__ JsonParse ;
typedef  TYPE_3__ JsonNode ;

/* Variables and functions */
 int JNODE_APPEND ; 
 int JNODE_LABEL ; 
 int JNODE_PATCH ; 
 int JNODE_RAW ; 
 int JNODE_REMOVE ; 
 scalar_t__ JSON_NULL ; 
 scalar_t__ JSON_OBJECT ; 
 scalar_t__ JSON_STRING ; 
 scalar_t__ JSON_TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ jsonNodeSize (TYPE_3__*) ; 
 int jsonParseAddNode (TYPE_2__*,scalar_t__,size_t,char const*) ; 
 int /*<<< orphan*/  jsonRemoveAllNulls (TYPE_3__*) ; 
 scalar_t__ strncmp (char*,char const*,size_t) ; 

__attribute__((used)) static JsonNode *jsonMergePatch(
  JsonParse *pParse,   /* The JSON parser that contains the TARGET */
  u32 iTarget,         /* Node of the TARGET in pParse */
  JsonNode *pPatch     /* The PATCH */
){
  u32 i, j;
  u32 iRoot;
  JsonNode *pTarget;
  if( pPatch->eType!=JSON_OBJECT ){
    return pPatch;
  }
  assert( iTarget>=0 && iTarget<pParse->nNode );
  pTarget = &pParse->aNode[iTarget];
  assert( (pPatch->jnFlags & JNODE_APPEND)==0 );
  if( pTarget->eType!=JSON_OBJECT ){
    jsonRemoveAllNulls(pPatch);
    return pPatch;
  }
  iRoot = iTarget;
  for(i=1; i<pPatch->n; i += jsonNodeSize(&pPatch[i+1])+1){
    u32 nKey;
    const char *zKey;
    assert( pPatch[i].eType==JSON_STRING );
    assert( pPatch[i].jnFlags & JNODE_LABEL );
    nKey = pPatch[i].n;
    zKey = pPatch[i].u.zJContent;
    assert( (pPatch[i].jnFlags & JNODE_RAW)==0 );
    for(j=1; j<pTarget->n; j += jsonNodeSize(&pTarget[j+1])+1 ){
      assert( pTarget[j].eType==JSON_STRING );
      assert( pTarget[j].jnFlags & JNODE_LABEL );
      assert( (pPatch[i].jnFlags & JNODE_RAW)==0 );
      if( pTarget[j].n==nKey && strncmp(pTarget[j].u.zJContent,zKey,nKey)==0 ){
        if( pTarget[j+1].jnFlags & (JNODE_REMOVE|JNODE_PATCH) ) break;
        if( pPatch[i+1].eType==JSON_NULL ){
          pTarget[j+1].jnFlags |= JNODE_REMOVE;
        }else{
          JsonNode *pNew = jsonMergePatch(pParse, iTarget+j+1, &pPatch[i+1]);
          if( pNew==0 ) return 0;
          pTarget = &pParse->aNode[iTarget];
          if( pNew!=&pTarget[j+1] ){
            pTarget[j+1].u.pPatch = pNew;
            pTarget[j+1].jnFlags |= JNODE_PATCH;
          }
        }
        break;
      }
    }
    if( j>=pTarget->n && pPatch[i+1].eType!=JSON_NULL ){
      int iStart, iPatch;
      iStart = jsonParseAddNode(pParse, JSON_OBJECT, 2, 0);
      jsonParseAddNode(pParse, JSON_STRING, nKey, zKey);
      iPatch = jsonParseAddNode(pParse, JSON_TRUE, 0, 0);
      if( pParse->oom ) return 0;
      jsonRemoveAllNulls(pPatch);
      pTarget = &pParse->aNode[iTarget];
      pParse->aNode[iRoot].jnFlags |= JNODE_APPEND;
      pParse->aNode[iRoot].u.iAppend = iStart - iRoot;
      iRoot = iStart;
      pParse->aNode[iPatch].jnFlags |= JNODE_PATCH;
      pParse->aNode[iPatch].u.pPatch = &pPatch[i+1];
    }
  }
  return pTarget;
}