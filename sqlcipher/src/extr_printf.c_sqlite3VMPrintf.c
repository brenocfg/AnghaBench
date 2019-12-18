#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zBase ;
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_9__ {int /*<<< orphan*/ * aLimit; } ;
typedef  TYPE_1__ sqlite3 ;
struct TYPE_10__ {scalar_t__ accError; int /*<<< orphan*/  printfFlags; } ;
typedef  TYPE_2__ StrAccum ;

/* Variables and functions */
 size_t SQLITE_LIMIT_LENGTH ; 
 scalar_t__ SQLITE_NOMEM ; 
 int /*<<< orphan*/  SQLITE_PRINTF_INTERNAL ; 
 int SQLITE_PRINT_BUF_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3OomFault (TYPE_1__*) ; 
 char* sqlite3StrAccumFinish (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3StrAccumInit (TYPE_2__*,TYPE_1__*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_str_vappendf (TYPE_2__*,char const*,int /*<<< orphan*/ ) ; 

char *sqlite3VMPrintf(sqlite3 *db, const char *zFormat, va_list ap){
  char *z;
  char zBase[SQLITE_PRINT_BUF_SIZE];
  StrAccum acc;
  assert( db!=0 );
  sqlite3StrAccumInit(&acc, db, zBase, sizeof(zBase),
                      db->aLimit[SQLITE_LIMIT_LENGTH]);
  acc.printfFlags = SQLITE_PRINTF_INTERNAL;
  sqlite3_str_vappendf(&acc, zFormat, ap);
  z = sqlite3StrAccumFinish(&acc);
  if( acc.accError==SQLITE_NOMEM ){
    sqlite3OomFault(db);
  }
  return z;
}