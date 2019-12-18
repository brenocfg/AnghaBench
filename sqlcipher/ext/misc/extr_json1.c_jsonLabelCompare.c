#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ zJContent; } ;
struct TYPE_5__ {int jnFlags; scalar_t__ n; TYPE_1__ u; } ;
typedef  TYPE_2__ JsonNode ;

/* Variables and functions */
 int JNODE_RAW ; 
 scalar_t__ strncmp (scalar_t__,char const*,scalar_t__) ; 

__attribute__((used)) static int jsonLabelCompare(JsonNode *pNode, const char *zKey, u32 nKey){
  if( pNode->jnFlags & JNODE_RAW ){
    if( pNode->n!=nKey ) return 0;
    return strncmp(pNode->u.zJContent, zKey, nKey)==0;
  }else{
    if( pNode->n!=nKey+2 ) return 0;
    return strncmp(pNode->u.zJContent+1, zKey, nKey)==0;
  }
}