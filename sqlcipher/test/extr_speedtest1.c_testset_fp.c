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
struct TYPE_2__ {int szTest; int /*<<< orphan*/  pStmt; int /*<<< orphan*/  zNN; } ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_STATIC ; 
 TYPE_1__ g ; 
 int /*<<< orphan*/  isTemp (int) ; 
 int /*<<< orphan*/  speedtest1_begin_test (int,char*,...) ; 
 int /*<<< orphan*/  speedtest1_end_test () ; 
 int /*<<< orphan*/  speedtest1_exec (char*,...) ; 
 int /*<<< orphan*/  speedtest1_prepare (char*,...) ; 
 int /*<<< orphan*/  speedtest1_random_ascii_fp (char*) ; 
 int /*<<< orphan*/  speedtest1_run () ; 
 int /*<<< orphan*/  sqlite3_bind_text (int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ ) ; 

void testset_fp(void){
  int n;
  int i;
  char zFP1[100];
  char zFP2[100];
  
  n = g.szTest*5000;
  speedtest1_begin_test(100, "Fill a table with %d FP values", n*2);
  speedtest1_exec("BEGIN");
  speedtest1_exec("CREATE%s TABLE t1(a REAL %s, b REAL %s);",
                  isTemp(1), g.zNN, g.zNN);
  speedtest1_prepare("INSERT INTO t1 VALUES(?1,?2); -- %d times", n);
  for(i=1; i<=n; i++){
    speedtest1_random_ascii_fp(zFP1);
    speedtest1_random_ascii_fp(zFP2);
    sqlite3_bind_text(g.pStmt, 1, zFP1, -1, SQLITE_STATIC);
    sqlite3_bind_text(g.pStmt, 2, zFP2, -1, SQLITE_STATIC);
    speedtest1_run();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();

  n = g.szTest/25 + 2;
  speedtest1_begin_test(110, "%d range queries", n);
  speedtest1_prepare("SELECT sum(b) FROM t1 WHERE a BETWEEN ?1 AND ?2");
  for(i=1; i<=n; i++){
    speedtest1_random_ascii_fp(zFP1);
    speedtest1_random_ascii_fp(zFP2);
    sqlite3_bind_text(g.pStmt, 1, zFP1, -1, SQLITE_STATIC);
    sqlite3_bind_text(g.pStmt, 2, zFP2, -1, SQLITE_STATIC);
    speedtest1_run();
  }
  speedtest1_end_test();

  speedtest1_begin_test(120, "CREATE INDEX three times");
  speedtest1_exec("BEGIN;");
  speedtest1_exec("CREATE INDEX t1a ON t1(a);");
  speedtest1_exec("CREATE INDEX t1b ON t1(b);");
  speedtest1_exec("CREATE INDEX t1ab ON t1(a,b);");
  speedtest1_exec("COMMIT;");
  speedtest1_end_test();

  n = g.szTest/3 + 2;
  speedtest1_begin_test(130, "%d indexed range queries", n);
  speedtest1_prepare("SELECT sum(b) FROM t1 WHERE a BETWEEN ?1 AND ?2");
  for(i=1; i<=n; i++){
    speedtest1_random_ascii_fp(zFP1);
    speedtest1_random_ascii_fp(zFP2);
    sqlite3_bind_text(g.pStmt, 1, zFP1, -1, SQLITE_STATIC);
    sqlite3_bind_text(g.pStmt, 2, zFP2, -1, SQLITE_STATIC);
    speedtest1_run();
  }
  speedtest1_end_test();
}