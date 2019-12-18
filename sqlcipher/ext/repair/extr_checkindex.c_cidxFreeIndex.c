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
struct TYPE_6__ {int nCol; struct TYPE_6__* zWhere; TYPE_1__* aCol; } ;
struct TYPE_5__ {TYPE_2__* zExpr; } ;
typedef  TYPE_2__ CidxIndex ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 

__attribute__((used)) static void cidxFreeIndex(CidxIndex *pIdx){
  if( pIdx ){
    int i;
    for(i=0; i<pIdx->nCol; i++){
      sqlite3_free(pIdx->aCol[i].zExpr);
    }
    sqlite3_free(pIdx->zWhere);
    sqlite3_free(pIdx);
  }
}