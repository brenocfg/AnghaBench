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
struct TYPE_11__ {int notIndexed; int isIndexedBy; scalar_t__ isTabFunc; } ;
struct TYPE_10__ {int /*<<< orphan*/  zIndexedBy; } ;
struct SrcList_item {TYPE_2__ fg; TYPE_1__ u1; } ;
struct TYPE_12__ {int n; int /*<<< orphan*/  z; } ;
typedef  TYPE_3__ Token ;
struct TYPE_14__ {int /*<<< orphan*/  db; } ;
struct TYPE_13__ {int nSrc; struct SrcList_item* a; } ;
typedef  TYPE_4__ SrcList ;
typedef  TYPE_5__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3NameFromToken (int /*<<< orphan*/ ,TYPE_3__*) ; 

void sqlite3SrcListIndexedBy(Parse *pParse, SrcList *p, Token *pIndexedBy){
  assert( pIndexedBy!=0 );
  if( p && pIndexedBy->n>0 ){
    struct SrcList_item *pItem;
    assert( p->nSrc>0 );
    pItem = &p->a[p->nSrc-1];
    assert( pItem->fg.notIndexed==0 );
    assert( pItem->fg.isIndexedBy==0 );
    assert( pItem->fg.isTabFunc==0 );
    if( pIndexedBy->n==1 && !pIndexedBy->z ){
      /* A "NOT INDEXED" clause was supplied. See parse.y 
      ** construct "indexed_opt" for details. */
      pItem->fg.notIndexed = 1;
    }else{
      pItem->u1.zIndexedBy = sqlite3NameFromToken(pParse->db, pIndexedBy);
      pItem->fg.isIndexedBy = 1;
    }
  }
}