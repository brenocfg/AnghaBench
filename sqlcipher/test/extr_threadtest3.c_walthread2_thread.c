#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_16__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ Sqlite ;
typedef  TYPE_2__ Error ;

/* Variables and functions */
 int PTR2INT (void*) ; 
 int /*<<< orphan*/  SQLITE_BUSY ; 
 int /*<<< orphan*/  clear_error (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closedb (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ filesize (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  integrity_check (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  opendb (TYPE_2__*,TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_and_free_err (TYPE_2__*) ; 
 int /*<<< orphan*/  sql_script (TYPE_2__*,TYPE_1__*,char const*) ; 
 char* sqlite3_mprintf (char*,int,int) ; 
 int /*<<< orphan*/  test_error (TYPE_2__*,char*,int,int) ; 
 int /*<<< orphan*/  timetostop (TYPE_2__*) ; 

__attribute__((used)) static char *walthread2_thread(int iTid, void *pArg){
  Error err = {0};                /* Error code and message */
  Sqlite db = {0};                /* SQLite database connection */
  int anTrans[2] = {0, 0};        /* Number of WAL and Rollback transactions */
  int iArg = PTR2INT(pArg);

  const char *zJournal = "PRAGMA journal_mode = WAL";
  if( iArg ){ zJournal = "PRAGMA journal_mode = DELETE"; }

  while( !timetostop(&err) ){
    int journal_exists = 0;
    int wal_exists = 0;

    opendb(&err, &db, "test.db", 0);

    sql_script(&err, &db, zJournal);
    clear_error(&err, SQLITE_BUSY);
    sql_script(&err, &db, "BEGIN");
    sql_script(&err, &db, "INSERT INTO t1 VALUES(NULL, randomblob(100))");

    journal_exists = (filesize(&err, "test.db-journal") >= 0);
    wal_exists = (filesize(&err, "test.db-wal") >= 0);
    if( (journal_exists+wal_exists)!=1 ){
      test_error(&err, "File system looks incorrect (%d, %d)", 
          journal_exists, wal_exists
      );
    }
    anTrans[journal_exists]++;

    sql_script(&err, &db, "COMMIT");
    integrity_check(&err, &db);
    closedb(&err, &db);
  }

  print_and_free_err(&err);
  return sqlite3_mprintf("W %d R %d", anTrans[0], anTrans[1]);
}