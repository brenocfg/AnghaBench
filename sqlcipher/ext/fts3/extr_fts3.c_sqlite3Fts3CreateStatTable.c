#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bHasStat; int /*<<< orphan*/  zName; int /*<<< orphan*/  zDb; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ Fts3Table ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  fts3DbExec (int*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sqlite3Fts3CreateStatTable(int *pRc, Fts3Table *p){
  fts3DbExec(pRc, p->db, 
      "CREATE TABLE IF NOT EXISTS %Q.'%q_stat'"
          "(id INTEGER PRIMARY KEY, value BLOB);",
      p->zDb, p->zName
  );
  if( (*pRc)==SQLITE_OK ) p->bHasStat = 1;
}