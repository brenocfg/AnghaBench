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
struct TYPE_4__ {scalar_t__ eType; int n; int /*<<< orphan*/  jnFlags; } ;
typedef  TYPE_1__ JsonNode ;

/* Variables and functions */
 int /*<<< orphan*/  JNODE_REMOVE ; 
#define  JSON_NULL 129 
#define  JSON_OBJECT 128 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ jsonNodeSize (TYPE_1__*) ; 

__attribute__((used)) static void jsonRemoveAllNulls(JsonNode *pNode){
  int i, n;
  assert( pNode->eType==JSON_OBJECT );
  n = pNode->n;
  for(i=2; i<=n; i += jsonNodeSize(&pNode[i])+1){
    switch( pNode[i].eType ){
      case JSON_NULL:
        pNode[i].jnFlags |= JNODE_REMOVE;
        break;
      case JSON_OBJECT:
        jsonRemoveAllNulls(&pNode[i]);
        break;
    }
  }
}