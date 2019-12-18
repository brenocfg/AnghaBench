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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  scalar_t__ sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int PATH_DIR ; 
 int PATH_TREE ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fatalError (char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 size_t fwrite (void const*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvtest_mkdir (char*) ; 
 int pathType (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ *) ; 
 void* sqlite3_column_blob (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_column_bytes (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char*) ; 
 int sqlite3_open (char*,int /*<<< orphan*/ **) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,int,...) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int exportMain(int argc, char **argv){
  char *zDb;
  char *zDir;
  sqlite3 *db;
  sqlite3_stmt *pStmt;
  int rc;
  int ePathType;
  int nFN;
  char *zFN;
  char *zTail;
  size_t nWrote;
  int i;

  assert( strcmp(argv[1],"export")==0 );
  assert( argc>=3 );
  if( argc<4 ) fatalError("Usage: kvtest export DATABASE DIRECTORY [OPTIONS]");
  zDb = argv[2];
  zDir = argv[3];
  kvtest_mkdir(zDir);
  for(i=4; i<argc; i++){
    const char *z = argv[i];
    if( z[0]=='-' && z[1]=='-' ) z++;
    if( strcmp(z,"-tree")==0 ){
      zFN = sqlite3_mprintf("%s/00", zDir);
      kvtest_mkdir(zFN);
      sqlite3_free(zFN);
      continue;
    }
    fatalError("unknown argument: \"%s\"\n", argv[i]);
  }
  ePathType = pathType(zDir);
  if( ePathType!=PATH_DIR && ePathType!=PATH_TREE ){
    fatalError("object \"%s\" is not a directory", zDir);
  }
  rc = sqlite3_open(zDb, &db);
  if( rc ){
    fatalError("cannot open database \"%s\": %s", zDb, sqlite3_errmsg(db));
  }
  rc = sqlite3_prepare_v2(db, "SELECT k, v FROM kv ORDER BY k", -1, &pStmt, 0);
  if( rc ){
    fatalError("prepare_v2 failed: %s\n", sqlite3_errmsg(db));
  }
  nFN = (int)strlen(zDir);
  zFN = sqlite3_mprintf("%s/00/00/00.extra---------------------", zDir);
  if( zFN==0 ){
    fatalError("malloc failed\n");
  }
  zTail = zFN + nFN + 1;
  while( sqlite3_step(pStmt)==SQLITE_ROW ){
    int iKey = sqlite3_column_int(pStmt, 0);
    sqlite3_int64 nData = sqlite3_column_bytes(pStmt, 1);
    const void *pData = sqlite3_column_blob(pStmt, 1);
    FILE *out;
    if( ePathType==PATH_DIR ){
      sqlite3_snprintf(20, zTail, "%06d", iKey);
    }else{
      sqlite3_snprintf(20, zTail, "%02d", iKey/10000);
      kvtest_mkdir(zFN);
      sqlite3_snprintf(20, zTail, "%02d/%02d", iKey/10000, (iKey/100)%100);
      kvtest_mkdir(zFN);
      sqlite3_snprintf(20, zTail, "%02d/%02d/%02d",
                       iKey/10000, (iKey/100)%100, iKey%100);
    }
    out = fopen(zFN, "wb");      
    nWrote = fwrite(pData, 1, (size_t)nData, out);
    fclose(out);
    printf("\r%s   ", zTail); fflush(stdout);
    if( nWrote!=(size_t)nData ){
      fatalError("Wrote only %d of %d bytes to %s\n",
                  (int)nWrote, nData, zFN);
    }
  }
  sqlite3_finalize(pStmt);
  sqlite3_close(db);
  sqlite3_free(zFN);
  printf("\n");
  return 0;
}