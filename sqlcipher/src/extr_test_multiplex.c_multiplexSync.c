#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* pMethods; } ;
typedef  TYPE_3__ sqlite3_file ;
struct TYPE_11__ {int nReal; TYPE_2__* aReal; } ;
typedef  TYPE_4__ multiplexGroup ;
struct TYPE_12__ {TYPE_4__* pGroup; } ;
typedef  TYPE_5__ multiplexConn ;
struct TYPE_9__ {TYPE_3__* p; } ;
struct TYPE_8__ {int (* xSync ) (TYPE_3__*,int) ;} ;

/* Variables and functions */
 int SQLITE_OK ; 
 int stub1 (TYPE_3__*,int) ; 

__attribute__((used)) static int multiplexSync(sqlite3_file *pConn, int flags){
  multiplexConn *p = (multiplexConn*)pConn;
  multiplexGroup *pGroup = p->pGroup;
  int rc = SQLITE_OK;
  int i;
  for(i=0; i<pGroup->nReal; i++){
    sqlite3_file *pSubOpen = pGroup->aReal[i].p;
    if( pSubOpen ){
      int rc2 = pSubOpen->pMethods->xSync(pSubOpen, flags);
      if( rc2!=SQLITE_OK ) rc = rc2;
    }
  }
  return rc;
}