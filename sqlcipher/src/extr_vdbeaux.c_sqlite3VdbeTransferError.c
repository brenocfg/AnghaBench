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
struct TYPE_5__ {scalar_t__ pErr; int errCode; int /*<<< orphan*/  bBenignMalloc; } ;
typedef  TYPE_1__ sqlite3 ;
struct TYPE_6__ {int rc; int /*<<< orphan*/  zErrMsg; TYPE_1__* db; } ;
typedef  TYPE_2__ Vdbe ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  SQLITE_UTF8 ; 
 int /*<<< orphan*/  sqlite3BeginBenignMalloc () ; 
 int /*<<< orphan*/  sqlite3EndBenignMalloc () ; 
 scalar_t__ sqlite3ValueNew (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3ValueSetNull (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3ValueSetStr (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sqlite3VdbeTransferError(Vdbe *p){
  sqlite3 *db = p->db;
  int rc = p->rc;
  if( p->zErrMsg ){
    db->bBenignMalloc++;
    sqlite3BeginBenignMalloc();
    if( db->pErr==0 ) db->pErr = sqlite3ValueNew(db);
    sqlite3ValueSetStr(db->pErr, -1, p->zErrMsg, SQLITE_UTF8, SQLITE_TRANSIENT);
    sqlite3EndBenignMalloc();
    db->bBenignMalloc--;
  }else if( db->pErr ){
    sqlite3ValueSetNull(db->pErr);
  }
  db->errCode = rc;
  return rc;
}