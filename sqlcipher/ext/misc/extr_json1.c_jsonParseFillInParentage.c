#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_6__ {int eType; size_t n; } ;
struct TYPE_5__ {size_t* aUp; TYPE_2__* aNode; } ;
typedef  TYPE_1__ JsonParse ;
typedef  TYPE_2__ JsonNode ;

/* Variables and functions */
#define  JSON_ARRAY 129 
#define  JSON_OBJECT 128 
 size_t jsonNodeSize (TYPE_2__*) ; 

__attribute__((used)) static void jsonParseFillInParentage(JsonParse *pParse, u32 i, u32 iParent){
  JsonNode *pNode = &pParse->aNode[i];
  u32 j;
  pParse->aUp[i] = iParent;
  switch( pNode->eType ){
    case JSON_ARRAY: {
      for(j=1; j<=pNode->n; j += jsonNodeSize(pNode+j)){
        jsonParseFillInParentage(pParse, i+j, i);
      }
      break;
    }
    case JSON_OBJECT: {
      for(j=1; j<=pNode->n; j += jsonNodeSize(pNode+j+1)+1){
        pParse->aUp[i+j] = i;
        jsonParseFillInParentage(pParse, i+j+1, i);
      }
      break;
    }
    default: {
      break;
    }
  }
}