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
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fatalError (char*,...) ; 
 int integerValue (char*) ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int sqlite3_exec (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,int,int,int,int) ; 
 int sqlite3_open (char*,int /*<<< orphan*/ **) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int initMain(int argc, char **argv){
  char *zDb;
  int i, rc;
  int nCount = 1000;
  int sz = 10000;
  int iVariance = 0;
  int pgsz = 4096;
  sqlite3 *db;
  char *zSql;
  char *zErrMsg = 0;

  assert( strcmp(argv[1],"init")==0 );
  assert( argc>=3 );
  zDb = argv[2];
  for(i=3; i<argc; i++){
    char *z = argv[i];
    if( z[0]!='-' ) fatalError("unknown argument: \"%s\"", z);
    if( z[1]=='-' ) z++;
    if( strcmp(z, "-count")==0 ){
      if( i==argc-1 ) fatalError("missing argument on \"%s\"", argv[i]);
      nCount = integerValue(argv[++i]);
      if( nCount<1 ) fatalError("the --count must be positive");
      continue;
    }
    if( strcmp(z, "-size")==0 ){
      if( i==argc-1 ) fatalError("missing argument on \"%s\"", argv[i]);
      sz = integerValue(argv[++i]);
      if( sz<1 ) fatalError("the --size must be positive");
      continue;
    }
    if( strcmp(z, "-variance")==0 ){
      if( i==argc-1 ) fatalError("missing argument on \"%s\"", argv[i]);
      iVariance = integerValue(argv[++i]);
      continue;
    }
    if( strcmp(z, "-pagesize")==0 ){
      if( i==argc-1 ) fatalError("missing argument on \"%s\"", argv[i]);
      pgsz = integerValue(argv[++i]);
      if( pgsz<512 || pgsz>65536 || ((pgsz-1)&pgsz)!=0 ){
        fatalError("the --pagesize must be power of 2 between 512 and 65536");
      }
      continue;
    }
    fatalError("unknown option: \"%s\"", argv[i]);
  }
  rc = sqlite3_open(zDb, &db);
  if( rc ){
    fatalError("cannot open database \"%s\": %s", zDb, sqlite3_errmsg(db));
  }
  zSql = sqlite3_mprintf(
    "DROP TABLE IF EXISTS kv;\n"
    "PRAGMA page_size=%d;\n"
    "VACUUM;\n"
    "BEGIN;\n"
    "CREATE TABLE kv(k INTEGER PRIMARY KEY, v BLOB);\n"
    "WITH RECURSIVE c(x) AS (VALUES(1) UNION ALL SELECT x+1 FROM c WHERE x<%d)"
    " INSERT INTO kv(k,v) SELECT x, randomblob(%d+(random()%%(%d))) FROM c;\n"
    "COMMIT;\n",
    pgsz, nCount, sz, iVariance+1
  );
  rc = sqlite3_exec(db, zSql, 0, 0, &zErrMsg);
  if( rc ) fatalError("database create failed: %s", zErrMsg);
  sqlite3_free(zSql);
  sqlite3_close(db);
  return 0;
}