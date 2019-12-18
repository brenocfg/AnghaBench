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
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_OPEN_READONLY ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sqlite3_bind_text (int /*<<< orphan*/ *,int,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ *) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int) ; 
 char* sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 char* sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int sqlite3_exec (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*) ; 
 int sqlite3_open_v2 (char*,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_strnicmp (char const*,char const*,int) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strstr (char const*,char*) ; 
 int strtol (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char **argv){
  sqlite3 *db = 0;          /* The main database */
  sqlite3_stmt *pStmt = 0;  /* a query */
  char *zSql;
  int nErr = 0;
  int rc;
  int bQuiet = 0;
  int i, j;
  const char *zUsing = 0;
  sqlite3_stmt *pIncrCnt = 0;
  int nRow = 0;
  int iProgress = 0;

  for(i=j=1; i<argc; i++){
    const char *z = argv[i];
    if( z[0]=='-' ){
      z++;
      if( z[0]=='-' ) z++;
      if( strcmp(z,"progress")==0 ){
        if( i+1<argc ){
          iProgress = strtol(argv[++i],0,0);
          continue;
        }
        printf("The --progress option requires an argument\n");
        exit(0);
      }
      if( strcmp(z,"q")==0 ){
        bQuiet = 1;
        continue;
      }
      if( strcmp(z,"using")==0 ){
        if( i+1<argc ){
          zUsing = argv[++i];
          continue;
        }
        printf("The --using option requires an argument\n");
        exit(0);
      }
      if( strcmp(z, "help")==0 || strcmp(z, "?")==0 ){
        usage(argv[0]);
      }
      printf("Unknown command-line option: \"%s\"\n", argv[i]);
      exit(0);
    }else{
      if( j<i ) argv[j++] = argv[i];
    }
  }
  argc = j;

  if( argc!=3 ) usage(argv[0]);
  rc = sqlite3_open_v2(argv[1], &db, SQLITE_OPEN_READONLY, 0);
  if( rc ){
    printf("Cannot open \"%s\" for reading: %s\n", argv[1], sqlite3_errmsg(db));
    goto errorOut;
  }
  rc = sqlite3_prepare_v2(db, "SELECT * FROM sqlite_master", -1, &pStmt, 0);
  if( rc ){
    printf("Cannot read the schema from \"%s\" - %s\n", argv[1],
           sqlite3_errmsg(db));
    goto errorOut;
  }
  sqlite3_finalize(pStmt);
  pStmt = 0;
  rc = sqlite3_exec(db, 
     "CREATE TABLE temp.idxu(\n"
     "  tbl TEXT COLLATE nocase,\n"
     "  idx TEXT COLLATE nocase,\n"
     "  cnt INT,\n"
     "  PRIMARY KEY(idx)\n"
     ") WITHOUT ROWID;", 0, 0, 0);
  if( rc ){
    printf("Cannot create the result table - %s\n",
           sqlite3_errmsg(db));
    goto errorOut;
  }
  rc = sqlite3_exec(db,
     "INSERT INTO temp.idxu(tbl,idx,cnt)"
     " SELECT tbl_name, name, 0 FROM sqlite_master"
     " WHERE type='index' AND sql IS NOT NULL", 0, 0, 0);

  /* Open the LOG database */
  zSql = sqlite3_mprintf("ATTACH %Q AS log", argv[2]);
  rc = sqlite3_exec(db, zSql, 0, 0, 0);
  sqlite3_free(zSql);
  if( rc ){
    printf("Cannot open the LOG database \"%s\" - %s\n",
           argv[2], sqlite3_errmsg(db));
    goto errorOut;
  }
  rc = sqlite3_prepare_v2(db,
     "SELECT sql, rowid FROM log.sqllog"
     " WHERE upper(substr(sql,1,5)) NOT IN ('BEGIN','COMMI','ROLLB','PRAGM')",
                          -1, &pStmt, 0);
  if( rc ){
    printf("Cannot read the SQLLOG table in the LOG database \"%s\" - %s\n",
           argv[2], sqlite3_errmsg(db));
    goto errorOut;
  }

  rc = sqlite3_prepare_v2(db,
    "UPDATE temp.idxu SET cnt=cnt+1 WHERE idx=?1",
    -1, &pIncrCnt, 0);
  if( rc ){
    printf("Cannot prepare a statement to increment a counter for "
           "indexes used\n");
    goto errorOut;
  }

  /* Update the counts based on LOG */
  while( sqlite3_step(pStmt)==SQLITE_ROW ){
    const char *zLog = (const char*)sqlite3_column_text(pStmt, 0);
    sqlite3_stmt *pS2;
    if( zLog==0 ) continue;
    zSql = sqlite3_mprintf("EXPLAIN QUERY PLAN %s", zLog);
    rc = sqlite3_prepare_v2(db, zSql, -1, &pS2, 0);
    sqlite3_free(zSql);
    if( rc ){
      if( !bQuiet ){
        printf("Cannot compile LOG entry %d (%s): %s\n",
             sqlite3_column_int(pStmt, 1), zLog, sqlite3_errmsg(db));
        fflush(stdout);
      }
      nErr++;
    }else{
      nRow++;
      if( iProgress>0 && (nRow%iProgress)==0 ){
        printf("%d...\n", nRow);
        fflush(stdout);
      }
      while( sqlite3_step(pS2)==SQLITE_ROW ){
        const char *zExplain = (const char*)sqlite3_column_text(pS2,3);
        const char *z1, *z2;
        int n;
        /* printf("EXPLAIN: %s\n", zExplain); */
        z1 = strstr(zExplain, " USING INDEX ");
        if( z1==0 ) continue;
        z1 += 13;
        for(z2=z1+1; z2[0] && z2[1]!='('; z2++){}
        n = z2 - z1;
        if( zUsing && sqlite3_strnicmp(zUsing, z1, n)==0 ){
          printf("Using %s:\n%s\n", zUsing, zLog);
          fflush(stdout);
        }
        sqlite3_bind_text(pIncrCnt,1,z1,n,SQLITE_STATIC);
        sqlite3_step(pIncrCnt);
        sqlite3_reset(pIncrCnt);
      }
    }
    sqlite3_finalize(pS2);
  }
  sqlite3_finalize(pStmt);

  /* Generate the report */
  rc = sqlite3_prepare_v2(db,
     "SELECT tbl, idx, cnt, "
     "   (SELECT group_concat(name,',') FROM pragma_index_info(idx))"
     " FROM temp.idxu, main.sqlite_master"
     " WHERE temp.idxu.tbl=main.sqlite_master.tbl_name"
     "   AND temp.idxu.idx=main.sqlite_master.name"
     " ORDER BY cnt DESC, tbl, idx",
     -1, &pStmt, 0);
  if( rc ){
    printf("Cannot query the result table - %s\n",
           sqlite3_errmsg(db));
    goto errorOut;
  }
  while( sqlite3_step(pStmt)==SQLITE_ROW ){
    printf("%10d %s on %s(%s)\n", 
       sqlite3_column_int(pStmt, 2),
       sqlite3_column_text(pStmt, 1),
       sqlite3_column_text(pStmt, 0),
       sqlite3_column_text(pStmt, 3));
  }
  sqlite3_finalize(pStmt);
  pStmt = 0;

errorOut:
  sqlite3_finalize(pIncrCnt);
  sqlite3_finalize(pStmt);
  sqlite3_close(db);
  return nErr;
}