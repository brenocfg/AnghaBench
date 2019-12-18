#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* aDb; int /*<<< orphan*/  autoCommit; } ;
typedef  TYPE_2__ sqlite3 ;
struct TYPE_9__ {TYPE_2__* db; } ;
struct TYPE_7__ {scalar_t__ pBt; } ;
typedef  TYPE_3__ Parse ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  sqlite3BtreeClose (scalar_t__) ; 
 scalar_t__ sqlite3BtreeIsInReadTrans (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  sqlite3ResetAllSchemasOfConnection (TYPE_2__*) ; 

__attribute__((used)) static int invalidateTempStorage(Parse *pParse){
  sqlite3 *db = pParse->db;
  if( db->aDb[1].pBt!=0 ){
    if( !db->autoCommit || sqlite3BtreeIsInReadTrans(db->aDb[1].pBt) ){
      sqlite3ErrorMsg(pParse, "temporary storage cannot be changed "
        "from within a transaction");
      return SQLITE_ERROR;
    }
    sqlite3BtreeClose(db->aDb[1].pBt);
    db->aDb[1].pBt = 0;
    sqlite3ResetAllSchemasOfConnection(db);
  }
  return SQLITE_OK;
}