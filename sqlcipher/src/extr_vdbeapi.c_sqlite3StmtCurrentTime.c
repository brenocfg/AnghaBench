#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sqlite3_int64 ;
struct TYPE_9__ {TYPE_2__* pOut; TYPE_3__* pVdbe; } ;
typedef  TYPE_4__ sqlite3_context ;
struct TYPE_8__ {scalar_t__ iCurrentTime; } ;
struct TYPE_7__ {TYPE_1__* db; } ;
struct TYPE_6__ {int /*<<< orphan*/  pVfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3OsCurrentTimeInt64 (int /*<<< orphan*/ ,scalar_t__*) ; 

sqlite3_int64 sqlite3StmtCurrentTime(sqlite3_context *p){
  int rc;
#ifndef SQLITE_ENABLE_STAT3_OR_STAT4
  sqlite3_int64 *piTime = &p->pVdbe->iCurrentTime;
  assert( p->pVdbe!=0 );
#else
  sqlite3_int64 iTime = 0;
  sqlite3_int64 *piTime = p->pVdbe!=0 ? &p->pVdbe->iCurrentTime : &iTime;
#endif
  if( *piTime==0 ){
    rc = sqlite3OsCurrentTimeInt64(p->pOut->db->pVfs, piTime);
    if( rc ) *piTime = 0;
  }
  return *piTime;
}