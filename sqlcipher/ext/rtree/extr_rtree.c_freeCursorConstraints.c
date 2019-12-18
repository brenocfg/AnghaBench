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
struct TYPE_5__ {int /*<<< orphan*/  pUser; int /*<<< orphan*/  (* xDelUser ) (int /*<<< orphan*/ ) ;struct TYPE_5__* pInfo; } ;
typedef  TYPE_1__ sqlite3_rtree_query_info ;
struct TYPE_6__ {int nConstraint; TYPE_1__* aConstraint; } ;
typedef  TYPE_2__ RtreeCursor ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void freeCursorConstraints(RtreeCursor *pCsr){
  if( pCsr->aConstraint ){
    int i;                        /* Used to iterate through constraint array */
    for(i=0; i<pCsr->nConstraint; i++){
      sqlite3_rtree_query_info *pInfo = pCsr->aConstraint[i].pInfo;
      if( pInfo ){
        if( pInfo->xDelUser ) pInfo->xDelUser(pInfo->pUser);
        sqlite3_free(pInfo);
      }
    }
    sqlite3_free(pCsr->aConstraint);
    pCsr->aConstraint = 0;
  }
}