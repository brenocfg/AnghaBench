#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* pScan; } ;
typedef  TYPE_1__ sqlite3expert ;
struct TYPE_7__ {scalar_t__ pOrder; struct TYPE_7__* pNextScan; } ;
typedef  TYPE_2__ IdxScan ;

/* Variables and functions */
 int SQLITE_OK ; 
 int idxCreateFromWhere (TYPE_1__*,TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static int idxCreateCandidates(sqlite3expert *p){
  int rc = SQLITE_OK;
  IdxScan *pIter;

  for(pIter=p->pScan; pIter && rc==SQLITE_OK; pIter=pIter->pNextScan){
    rc = idxCreateFromWhere(p, pIter, 0);
    if( rc==SQLITE_OK && pIter->pOrder ){
      rc = idxCreateFromWhere(p, pIter, pIter->pOrder);
    }
  }

  return rc;
}