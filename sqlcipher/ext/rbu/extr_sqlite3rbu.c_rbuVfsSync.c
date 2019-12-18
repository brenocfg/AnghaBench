#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_7__ {int openFlags; TYPE_4__* pReal; TYPE_1__* pRbu; } ;
typedef  TYPE_3__ rbu_file ;
struct TYPE_8__ {TYPE_2__* pMethods; } ;
struct TYPE_6__ {int (* xSync ) (TYPE_4__*,int) ;} ;
struct TYPE_5__ {scalar_t__ eStage; } ;

/* Variables and functions */
 scalar_t__ RBU_STAGE_CAPTURE ; 
 int SQLITE_INTERNAL ; 
 int SQLITE_OK ; 
 int SQLITE_OPEN_MAIN_DB ; 
 int stub1 (TYPE_4__*,int) ; 

__attribute__((used)) static int rbuVfsSync(sqlite3_file *pFile, int flags){
  rbu_file *p = (rbu_file *)pFile;
  if( p->pRbu && p->pRbu->eStage==RBU_STAGE_CAPTURE ){
    if( p->openFlags & SQLITE_OPEN_MAIN_DB ){
      return SQLITE_INTERNAL;
    }
    return SQLITE_OK;
  }
  return p->pReal->pMethods->xSync(p->pReal, flags);
}