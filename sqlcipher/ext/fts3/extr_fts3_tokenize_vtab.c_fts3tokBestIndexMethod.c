#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_7__ {int nConstraint; int idxNum; int estimatedCost; TYPE_2__* aConstraintUsage; TYPE_1__* aConstraint; } ;
typedef  TYPE_3__ sqlite3_index_info ;
struct TYPE_6__ {int argvIndex; int omit; } ;
struct TYPE_5__ {scalar_t__ iColumn; scalar_t__ op; scalar_t__ usable; } ;

/* Variables and functions */
 scalar_t__ SQLITE_INDEX_CONSTRAINT_EQ ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int fts3tokBestIndexMethod(
  sqlite3_vtab *pVTab, 
  sqlite3_index_info *pInfo
){
  int i;
  UNUSED_PARAMETER(pVTab);

  for(i=0; i<pInfo->nConstraint; i++){
    if( pInfo->aConstraint[i].usable 
     && pInfo->aConstraint[i].iColumn==0 
     && pInfo->aConstraint[i].op==SQLITE_INDEX_CONSTRAINT_EQ 
    ){
      pInfo->idxNum = 1;
      pInfo->aConstraintUsage[i].argvIndex = 1;
      pInfo->aConstraintUsage[i].omit = 1;
      pInfo->estimatedCost = 1;
      return SQLITE_OK;
    }
  }

  pInfo->idxNum = 0;
  assert( pInfo->estimatedCost>1000000.0 );

  return SQLITE_OK;
}