#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vdbe ;
typedef  int /*<<< orphan*/  Token ;
struct TYPE_5__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  OP_Savepoint ; 
 int /*<<< orphan*/  P4_DYNAMIC ; 
 int /*<<< orphan*/  SAVEPOINT_BEGIN ; 
 int SAVEPOINT_RELEASE ; 
 int SAVEPOINT_ROLLBACK ; 
 int /*<<< orphan*/  SQLITE_SAVEPOINT ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3AuthCheck (TYPE_1__*,int /*<<< orphan*/ ,char const* const,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_1__*) ; 
 char* sqlite3NameFromToken (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void sqlite3Savepoint(Parse *pParse, int op, Token *pName){
  char *zName = sqlite3NameFromToken(pParse->db, pName);
  if( zName ){
    Vdbe *v = sqlite3GetVdbe(pParse);
#ifndef SQLITE_OMIT_AUTHORIZATION
    static const char * const az[] = { "BEGIN", "RELEASE", "ROLLBACK" };
    assert( !SAVEPOINT_BEGIN && SAVEPOINT_RELEASE==1 && SAVEPOINT_ROLLBACK==2 );
#endif
    if( !v || sqlite3AuthCheck(pParse, SQLITE_SAVEPOINT, az[op], zName, 0) ){
      sqlite3DbFree(pParse->db, zName);
      return;
    }
    sqlite3VdbeAddOp4(v, OP_Savepoint, op, 0, 0, zName, P4_DYNAMIC);
  }
}