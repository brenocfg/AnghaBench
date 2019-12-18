#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_uint64 ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  r ;

/* Variables and functions */
 int /*<<< orphan*/  execExecSql (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  execSql (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rename (char const*,char const*) ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ *) ; 
 char* sqlite3_errstr (int) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*,...) ; 
 int sqlite3_open (char const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sqlite3_randomness (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv){
  sqlite3 *db;                 /* Connection to the database file */
  int rc;                      /* Return code from SQLite interface calls */
  sqlite3_uint64 r;            /* A random number */
  const char *zDbToVacuum;     /* Database to be vacuumed */
  char *zBackupDb;             /* Backup copy of the original database */
  char *zTempDb;               /* Temporary database */
  char *zSql;                  /* An SQL statement */

  if( argc!=2 ){
    fprintf(stderr, "Usage: %s DATABASE\n", argv[0]);
    return 1;
  }

  /* Identify the database file to be vacuumed and open it.
  */
  zDbToVacuum = argv[1];
  printf("-- open database file \"%s\"\n", zDbToVacuum);
  rc = sqlite3_open(zDbToVacuum, &db);
  if( rc ){
    fprintf(stderr, "%s: %s\n", zDbToVacuum, sqlite3_errstr(rc));
    return 1;
  }

  /* Create names for two other files.  zTempDb will be a new database
  ** into which we construct a vacuumed copy of zDbToVacuum.  zBackupDb
  ** will be a new name for zDbToVacuum after it is vacuumed.
  */
  sqlite3_randomness(sizeof(r), &r);
  zTempDb = sqlite3_mprintf("%s-vacuum-%016llx", zDbToVacuum, r);
  zBackupDb = sqlite3_mprintf("%s-backup-%016llx", zDbToVacuum, r);

  /* Attach the zTempDb database to the database connection.
  */
  zSql = sqlite3_mprintf("ATTACH '%q' AS vacuum_db;", zTempDb);
  execSql(db, zSql);
  sqlite3_free(zSql);

  /* TODO:
  ** Set the page_size and auto_vacuum mode for zTempDb here, if desired.
  */

  /* The vacuum will occur inside of a transaction.  Set writable_schema
  ** to ON so that we can directly update the sqlite_master table in the
  ** zTempDb database.
  */
  execSql(db, "PRAGMA writable_schema=ON");
  execSql(db, "BEGIN");


  /* Query the schema of the main database. Create a mirror schema
  ** in the temporary database.
  */
  execExecSql(db, 
      "SELECT 'CREATE TABLE vacuum_db.' || substr(sql,14) "
      "  FROM sqlite_master WHERE type='table' AND name!='sqlite_sequence'"
      "   AND rootpage>0"
  );
  execExecSql(db,
      "SELECT 'CREATE INDEX vacuum_db.' || substr(sql,14)"
      "  FROM sqlite_master WHERE sql LIKE 'CREATE INDEX %'"
  );
  execExecSql(db,
      "SELECT 'CREATE UNIQUE INDEX vacuum_db.' || substr(sql,21) "
      "  FROM sqlite_master WHERE sql LIKE 'CREATE UNIQUE INDEX %'"
  );

  /* Loop through the tables in the main database. For each, do
  ** an "INSERT INTO vacuum_db.xxx SELECT * FROM main.xxx;" to copy
  ** the contents to the temporary database.
  */
  execExecSql(db,
      "SELECT 'INSERT INTO vacuum_db.' || quote(name) "
      "|| ' SELECT * FROM main.' || quote(name) "
      "FROM main.sqlite_master "
      "WHERE type = 'table' AND name!='sqlite_sequence' "
      "  AND rootpage>0"
  );

  /* Copy over the sequence table
  */
  execExecSql(db,
      "SELECT 'DELETE FROM vacuum_db.' || quote(name) "
      "FROM vacuum_db.sqlite_master WHERE name='sqlite_sequence'"
  );
  execExecSql(db,
      "SELECT 'INSERT INTO vacuum_db.' || quote(name) "
      "|| ' SELECT * FROM main.' || quote(name) "
      "FROM vacuum_db.sqlite_master WHERE name=='sqlite_sequence'"
  );

  /* Copy the triggers, views, and virtual tables from the main database
  ** over to the temporary database.  None of these objects has any
  ** associated storage, so all we have to do is copy their entries
  ** from the SQLITE_MASTER table.
  */
  execSql(db,
      "INSERT INTO vacuum_db.sqlite_master "
      "  SELECT type, name, tbl_name, rootpage, sql"
      "    FROM main.sqlite_master"
      "   WHERE type='view' OR type='trigger'"
      "      OR (type='table' AND rootpage=0)"
  );

  /* Commit the transaction and close the database
  */
  execSql(db, "COMMIT");
  printf("-- close database\n");
  sqlite3_close(db);


  /* At this point, zDbToVacuum is unchanged.  zTempDb contains a
  ** vacuumed copy of zDbToVacuum.  Rearrange filenames so that
  ** zTempDb becomes thenew zDbToVacuum.
  */
  printf("-- rename \"%s\" to \"%s\"\n", zDbToVacuum, zBackupDb);
  rename(zDbToVacuum, zBackupDb);
  printf("-- rename \"%s\" to \"%s\"\n", zTempDb, zDbToVacuum);
  rename(zTempDb, zDbToVacuum);

  /* Release allocated memory */
  sqlite3_free(zTempDb);
  sqlite3_free(zBackupDb);
  return 0;
}