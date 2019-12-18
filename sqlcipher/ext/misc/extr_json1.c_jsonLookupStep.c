#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_11__ {size_t iAppend; } ;
struct TYPE_13__ {scalar_t__ eType; size_t n; int jnFlags; TYPE_1__ u; } ;
struct TYPE_12__ {TYPE_3__* aNode; scalar_t__ oom; } ;
typedef  TYPE_2__ JsonParse ;
typedef  TYPE_3__ JsonNode ;

/* Variables and functions */
 int JNODE_APPEND ; 
 int JNODE_RAW ; 
 int JNODE_REMOVE ; 
 scalar_t__ JSON_ARRAY ; 
 scalar_t__ JSON_OBJECT ; 
 scalar_t__ JSON_STRING ; 
 scalar_t__ jsonLabelCompare (TYPE_3__*,char const*,size_t) ; 
 TYPE_3__* jsonLookupAppend (TYPE_2__*,char const*,int*,char const**) ; 
 scalar_t__ jsonNodeSize (TYPE_3__*) ; 
 size_t jsonParseAddNode (TYPE_2__*,scalar_t__,int,char const*) ; 
 scalar_t__ safe_isdigit (char const) ; 

__attribute__((used)) static JsonNode *jsonLookupStep(
  JsonParse *pParse,      /* The JSON to search */
  u32 iRoot,              /* Begin the search at this node */
  const char *zPath,      /* The path to search */
  int *pApnd,             /* Append nodes to complete path if not NULL */
  const char **pzErr      /* Make *pzErr point to any syntax error in zPath */
){
  u32 i, j, nKey;
  const char *zKey;
  JsonNode *pRoot = &pParse->aNode[iRoot];
  if( zPath[0]==0 ) return pRoot;
  if( zPath[0]=='.' ){
    if( pRoot->eType!=JSON_OBJECT ) return 0;
    zPath++;
    if( zPath[0]=='"' ){
      zKey = zPath + 1;
      for(i=1; zPath[i] && zPath[i]!='"'; i++){}
      nKey = i-1;
      if( zPath[i] ){
        i++;
      }else{
        *pzErr = zPath;
        return 0;
      }
    }else{
      zKey = zPath;
      for(i=0; zPath[i] && zPath[i]!='.' && zPath[i]!='['; i++){}
      nKey = i;
    }
    if( nKey==0 ){
      *pzErr = zPath;
      return 0;
    }
    j = 1;
    for(;;){
      while( j<=pRoot->n ){
        if( jsonLabelCompare(pRoot+j, zKey, nKey) ){
          return jsonLookupStep(pParse, iRoot+j+1, &zPath[i], pApnd, pzErr);
        }
        j++;
        j += jsonNodeSize(&pRoot[j]);
      }
      if( (pRoot->jnFlags & JNODE_APPEND)==0 ) break;
      iRoot += pRoot->u.iAppend;
      pRoot = &pParse->aNode[iRoot];
      j = 1;
    }
    if( pApnd ){
      u32 iStart, iLabel;
      JsonNode *pNode;
      iStart = jsonParseAddNode(pParse, JSON_OBJECT, 2, 0);
      iLabel = jsonParseAddNode(pParse, JSON_STRING, i, zPath);
      zPath += i;
      pNode = jsonLookupAppend(pParse, zPath, pApnd, pzErr);
      if( pParse->oom ) return 0;
      if( pNode ){
        pRoot = &pParse->aNode[iRoot];
        pRoot->u.iAppend = iStart - iRoot;
        pRoot->jnFlags |= JNODE_APPEND;
        pParse->aNode[iLabel].jnFlags |= JNODE_RAW;
      }
      return pNode;
    }
  }else if( zPath[0]=='[' && safe_isdigit(zPath[1]) ){
    if( pRoot->eType!=JSON_ARRAY ) return 0;
    i = 0;
    j = 1;
    while( safe_isdigit(zPath[j]) ){
      i = i*10 + zPath[j] - '0';
      j++;
    }
    if( zPath[j]!=']' ){
      *pzErr = zPath;
      return 0;
    }
    zPath += j + 1;
    j = 1;
    for(;;){
      while( j<=pRoot->n && (i>0 || (pRoot[j].jnFlags & JNODE_REMOVE)!=0) ){
        if( (pRoot[j].jnFlags & JNODE_REMOVE)==0 ) i--;
        j += jsonNodeSize(&pRoot[j]);
      }
      if( (pRoot->jnFlags & JNODE_APPEND)==0 ) break;
      iRoot += pRoot->u.iAppend;
      pRoot = &pParse->aNode[iRoot];
      j = 1;
    }
    if( j<=pRoot->n ){
      return jsonLookupStep(pParse, iRoot+j, zPath, pApnd, pzErr);
    }
    if( i==0 && pApnd ){
      u32 iStart;
      JsonNode *pNode;
      iStart = jsonParseAddNode(pParse, JSON_ARRAY, 1, 0);
      pNode = jsonLookupAppend(pParse, zPath, pApnd, pzErr);
      if( pParse->oom ) return 0;
      if( pNode ){
        pRoot = &pParse->aNode[iRoot];
        pRoot->u.iAppend = iStart - iRoot;
        pRoot->jnFlags |= JNODE_APPEND;
      }
      return pNode;
    }
  }else{
    *pzErr = zPath;
  }
  return 0;
}