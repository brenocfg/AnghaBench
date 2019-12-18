#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_6__ {char const* zJContent; } ;
struct TYPE_8__ {TYPE_1__ u; scalar_t__ n; scalar_t__ jnFlags; scalar_t__ eType; } ;
struct TYPE_7__ {size_t nNode; size_t nAlloc; TYPE_3__* aNode; } ;
typedef  TYPE_2__ JsonParse ;
typedef  TYPE_3__ JsonNode ;

/* Variables and functions */
 int jsonParseAddNodeExpand (TYPE_2__*,scalar_t__,scalar_t__,char const*) ; 

__attribute__((used)) static int jsonParseAddNode(
  JsonParse *pParse,        /* Append the node to this object */
  u32 eType,                /* Node type */
  u32 n,                    /* Content size or sub-node count */
  const char *zContent      /* Content */
){
  JsonNode *p;
  if( pParse->nNode>=pParse->nAlloc ){
    return jsonParseAddNodeExpand(pParse, eType, n, zContent);
  }
  p = &pParse->aNode[pParse->nNode];
  p->eType = (u8)eType;
  p->jnFlags = 0;
  p->n = n;
  p->u.zJContent = zContent;
  return pParse->nNode++;
}