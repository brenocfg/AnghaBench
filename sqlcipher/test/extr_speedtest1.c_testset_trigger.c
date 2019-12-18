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
typedef  int /*<<< orphan*/  zNum ;
struct TYPE_2__ {int szTest; int /*<<< orphan*/  pStmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_STATIC ; 
 TYPE_1__ g ; 
 int /*<<< orphan*/  speedtest1_begin_test (int,char*) ; 
 int /*<<< orphan*/  speedtest1_end_test () ; 
 int /*<<< orphan*/  speedtest1_exec (char*) ; 
 int /*<<< orphan*/  speedtest1_numbername (int,char*,int) ; 
 int /*<<< orphan*/  speedtest1_prepare (char*,...) ; 
 int const speedtest1_random () ; 
 int /*<<< orphan*/  speedtest1_run () ; 
 int /*<<< orphan*/  sqlite3_bind_int (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3_bind_text (int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ ) ; 

void testset_trigger(void){
  int jj, ii;
  char zNum[2000];              /* A number name */

  const int NROW  = 500*g.szTest;
  const int NROW2 = 100*g.szTest;

  speedtest1_exec(
      "BEGIN;"
      "CREATE TABLE t1(rowid INTEGER PRIMARY KEY, i INTEGER, t TEXT);"
      "CREATE TABLE t2(rowid INTEGER PRIMARY KEY, i INTEGER, t TEXT);"
      "CREATE TABLE t3(rowid INTEGER PRIMARY KEY, i INTEGER, t TEXT);"
      "CREATE VIEW v1 AS SELECT rowid, i, t FROM t1;"
      "CREATE VIEW v2 AS SELECT rowid, i, t FROM t2;"
      "CREATE VIEW v3 AS SELECT rowid, i, t FROM t3;"
  );
  for(jj=1; jj<=3; jj++){
    speedtest1_prepare("INSERT INTO t%d VALUES(NULL,?1,?2)", jj);
    for(ii=0; ii<NROW; ii++){
      int x1 = speedtest1_random() % NROW;
      speedtest1_numbername(x1, zNum, sizeof(zNum));
      sqlite3_bind_int(g.pStmt, 1, x1);
      sqlite3_bind_text(g.pStmt, 2, zNum, -1, SQLITE_STATIC);
      speedtest1_run();
    }
  }
  speedtest1_exec(
      "CREATE INDEX i1 ON t1(t);"
      "CREATE INDEX i2 ON t2(t);"
      "CREATE INDEX i3 ON t3(t);"
      "COMMIT;"
  );

  speedtest1_begin_test(100, "speed4p-join1");
  speedtest1_prepare(
      "SELECT * FROM t1, t2, t3 WHERE t1.oid = t2.oid AND t2.oid = t3.oid"
  );
  speedtest1_run();
  speedtest1_end_test();

  speedtest1_begin_test(110, "speed4p-join2");
  speedtest1_prepare(
      "SELECT * FROM t1, t2, t3 WHERE t1.t = t2.t AND t2.t = t3.t"
  );
  speedtest1_run();
  speedtest1_end_test();

  speedtest1_begin_test(120, "speed4p-view1");
  for(jj=1; jj<=3; jj++){
    speedtest1_prepare("SELECT * FROM v%d WHERE rowid = ?", jj);
    for(ii=0; ii<NROW2; ii+=3){
      sqlite3_bind_int(g.pStmt, 1, ii*3);
      speedtest1_run();
    }
  }
  speedtest1_end_test();

  speedtest1_begin_test(130, "speed4p-table1");
  for(jj=1; jj<=3; jj++){
    speedtest1_prepare("SELECT * FROM t%d WHERE rowid = ?", jj);
    for(ii=0; ii<NROW2; ii+=3){
      sqlite3_bind_int(g.pStmt, 1, ii*3);
      speedtest1_run();
    }
  }
  speedtest1_end_test();

  speedtest1_begin_test(140, "speed4p-table1");
  for(jj=1; jj<=3; jj++){
    speedtest1_prepare("SELECT * FROM t%d WHERE rowid = ?", jj);
    for(ii=0; ii<NROW2; ii+=3){
      sqlite3_bind_int(g.pStmt, 1, ii*3);
      speedtest1_run();
    }
  }
  speedtest1_end_test();

  speedtest1_begin_test(150, "speed4p-subselect1");
  speedtest1_prepare("SELECT "
      "(SELECT t FROM t1 WHERE rowid = ?1),"
      "(SELECT t FROM t2 WHERE rowid = ?1),"
      "(SELECT t FROM t3 WHERE rowid = ?1)"
  );
  for(jj=0; jj<NROW2; jj++){
    sqlite3_bind_int(g.pStmt, 1, jj*3);
    speedtest1_run();
  }
  speedtest1_end_test();

  speedtest1_begin_test(160, "speed4p-rowid-update");
  speedtest1_exec("BEGIN");
  speedtest1_prepare("UPDATE t1 SET i=i+1 WHERE rowid=?1");
  for(jj=0; jj<NROW2; jj++){
    sqlite3_bind_int(g.pStmt, 1, jj);
    speedtest1_run();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();

  speedtest1_exec("CREATE TABLE t5(t TEXT PRIMARY KEY, i INTEGER);");
  speedtest1_begin_test(170, "speed4p-insert-ignore");
  speedtest1_exec("INSERT OR IGNORE INTO t5 SELECT t, i FROM t1");
  speedtest1_end_test();

  speedtest1_exec(
      "CREATE TABLE log(op TEXT, r INTEGER, i INTEGER, t TEXT);"
      "CREATE TABLE t4(rowid INTEGER PRIMARY KEY, i INTEGER, t TEXT);"
      "CREATE TRIGGER t4_trigger1 AFTER INSERT ON t4 BEGIN"
      "  INSERT INTO log VALUES('INSERT INTO t4', new.rowid, new.i, new.t);"
      "END;"
      "CREATE TRIGGER t4_trigger2 AFTER UPDATE ON t4 BEGIN"
      "  INSERT INTO log VALUES('UPDATE OF t4', new.rowid, new.i, new.t);"
      "END;"
      "CREATE TRIGGER t4_trigger3 AFTER DELETE ON t4 BEGIN"
      "  INSERT INTO log VALUES('DELETE OF t4', old.rowid, old.i, old.t);"
      "END;"
      "BEGIN;"
  );

  speedtest1_begin_test(180, "speed4p-trigger1");
  speedtest1_prepare("INSERT INTO t4 VALUES(NULL, ?1, ?2)");
  for(jj=0; jj<NROW2; jj++){
    speedtest1_numbername(jj, zNum, sizeof(zNum));
    sqlite3_bind_int(g.pStmt, 1, jj);
    sqlite3_bind_text(g.pStmt, 2, zNum, -1, SQLITE_STATIC);
    speedtest1_run();
  }
  speedtest1_end_test();

  /*
  ** Note: Of the queries, only half actually update a row. This property
  ** was copied over from speed4p.test, where it was probably introduced
  ** inadvertantly.
  */
  speedtest1_begin_test(190, "speed4p-trigger2");
  speedtest1_prepare("UPDATE t4 SET i = ?1, t = ?2 WHERE rowid = ?3");
  for(jj=1; jj<=NROW2*2; jj+=2){
    speedtest1_numbername(jj*2, zNum, sizeof(zNum));
    sqlite3_bind_int(g.pStmt, 1, jj*2);
    sqlite3_bind_text(g.pStmt, 2, zNum, -1, SQLITE_STATIC);
    sqlite3_bind_int(g.pStmt, 3, jj);
    speedtest1_run();
  }
  speedtest1_end_test();

  /*
  ** Note: Same again.
  */
  speedtest1_begin_test(200, "speed4p-trigger3");
  speedtest1_prepare("DELETE FROM t4 WHERE rowid = ?1");
  for(jj=1; jj<=NROW2*2; jj+=2){
    sqlite3_bind_int(g.pStmt, 1, jj*2);
    speedtest1_run();
  }
  speedtest1_end_test();
  speedtest1_exec("COMMIT");

  /*
  ** The following block contains the same tests as the above block that
  ** tests triggers, with one crucial difference: no triggers are defined.
  ** So the difference in speed between these tests and the preceding ones
  ** is the amount of time taken to compile and execute the trigger programs.
  */
  speedtest1_exec(
      "DROP TABLE t4;"
      "DROP TABLE log;"
      "VACUUM;"
      "CREATE TABLE t4(rowid INTEGER PRIMARY KEY, i INTEGER, t TEXT);"
      "BEGIN;"
  );
  speedtest1_begin_test(210, "speed4p-notrigger1");
  speedtest1_prepare("INSERT INTO t4 VALUES(NULL, ?1, ?2)");
  for(jj=0; jj<NROW2; jj++){
    speedtest1_numbername(jj, zNum, sizeof(zNum));
    sqlite3_bind_int(g.pStmt, 1, jj);
    sqlite3_bind_text(g.pStmt, 2, zNum, -1, SQLITE_STATIC);
    speedtest1_run();
  }
  speedtest1_end_test();
  speedtest1_begin_test(210, "speed4p-notrigger2");
  speedtest1_prepare("UPDATE t4 SET i = ?1, t = ?2 WHERE rowid = ?3");
  for(jj=1; jj<=NROW2*2; jj+=2){
    speedtest1_numbername(jj*2, zNum, sizeof(zNum));
    sqlite3_bind_int(g.pStmt, 1, jj*2);
    sqlite3_bind_text(g.pStmt, 2, zNum, -1, SQLITE_STATIC);
    sqlite3_bind_int(g.pStmt, 3, jj);
    speedtest1_run();
  }
  speedtest1_end_test();
  speedtest1_begin_test(220, "speed4p-notrigger3");
  speedtest1_prepare("DELETE FROM t4 WHERE rowid = ?1");
  for(jj=1; jj<=NROW2*2; jj+=2){
    sqlite3_bind_int(g.pStmt, 1, jj*2);
    speedtest1_run();
  }
  speedtest1_end_test();
  speedtest1_exec("COMMIT");
}