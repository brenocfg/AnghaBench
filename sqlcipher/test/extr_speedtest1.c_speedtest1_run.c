#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_2__ {int nResult; char* zResult; int /*<<< orphan*/ * pStmt; int /*<<< orphan*/  db; scalar_t__ bReprepare; scalar_t__ bSqlOnly; } ;

/* Variables and functions */
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 TYPE_1__ g ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  speedtest1_shrink_memory () ; 
 int sqlite3_column_count (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_prepare_v2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_sql (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char const*) ; 

void speedtest1_run(void){
  int i, n, len;
  if( g.bSqlOnly ) return;
  assert( g.pStmt );
  g.nResult = 0;
  while( sqlite3_step(g.pStmt)==SQLITE_ROW ){
    n = sqlite3_column_count(g.pStmt);
    for(i=0; i<n; i++){
      const char *z = (const char*)sqlite3_column_text(g.pStmt, i);
      if( z==0 ) z = "nil";
      len = (int)strlen(z);
      if( g.nResult+len<sizeof(g.zResult)-2 ){
        if( g.nResult>0 ) g.zResult[g.nResult++] = ' ';
        memcpy(g.zResult + g.nResult, z, len+1);
        g.nResult += len;
      }
    }
  }
#if SQLITE_VERSION_NUMBER>=3006001
  if( g.bReprepare ){
    sqlite3_stmt *pNew;
    sqlite3_prepare_v2(g.db, sqlite3_sql(g.pStmt), -1, &pNew, 0);
    sqlite3_finalize(g.pStmt);
    g.pStmt = pNew;
  }else
#endif
  {
    sqlite3_reset(g.pStmt);
  }
  speedtest1_shrink_memory();
}