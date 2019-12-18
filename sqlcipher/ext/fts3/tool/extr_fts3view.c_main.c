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
 scalar_t__ SQLITE_ROW ; 
 char** azExtra ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  listBigSegments (int /*<<< orphan*/ *,char const*) ; 
 int nExtra ; 
 int /*<<< orphan*/ * prepare (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  showDoclist (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  showSchema (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  showSegdirMap (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  showSegment (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  showSegmentStats (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  showStat (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  showVocabulary (int /*<<< orphan*/ *,char const*) ; 
 char* sqlite3_column_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int sqlite3_open (char*,int /*<<< orphan*/ **) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char **argv){
  sqlite3 *db;
  int rc;
  const char *zTab;
  const char *zCmd;

  if( argc<2 ) usage(argv[0]);
  rc = sqlite3_open(argv[1], &db);
  if( rc ){
    fprintf(stderr, "Cannot open %s\n", argv[1]);
    exit(1);
  }
  if( argc==2 ){
    sqlite3_stmt *pStmt;
    int cnt = 0;
    pStmt = prepare(db, "SELECT b.sql"
                        "  FROM sqlite_master a, sqlite_master b"
                        " WHERE a.name GLOB '*_segdir'"
                        "   AND b.name=substr(a.name,1,length(a.name)-7)"
                        " ORDER BY 1");
    while( sqlite3_step(pStmt)==SQLITE_ROW ){
      cnt++;
      printf("%s;\n", sqlite3_column_text(pStmt, 0));
    }
    sqlite3_finalize(pStmt);
    if( cnt==0 ){
      printf("/* No FTS3/4 tables found in database %s */\n", argv[1]);
    }
    return 0;
  }
  if( argc<4 ) usage(argv[0]);
  zTab = argv[2];
  zCmd = argv[3];
  nExtra = argc-4;
  azExtra = argv+4;
  if( strcmp(zCmd,"big-segments")==0 ){
    listBigSegments(db, zTab);
  }else if( strcmp(zCmd,"doclist")==0 ){
    if( argc<7 ) usage(argv[0]);
    showDoclist(db, zTab);
  }else if( strcmp(zCmd,"schema")==0 ){
    showSchema(db, zTab);
  }else if( strcmp(zCmd,"segdir")==0 ){
    showSegdirMap(db, zTab);
  }else if( strcmp(zCmd,"segment")==0 ){
    if( argc<5 ) usage(argv[0]);
    showSegment(db, zTab);
  }else if( strcmp(zCmd,"segment-stats")==0 ){
    showSegmentStats(db, zTab);
  }else if( strcmp(zCmd,"stat")==0 ){
    showStat(db, zTab);
  }else if( strcmp(zCmd,"vocabulary")==0 ){
    showVocabulary(db, zTab);
  }else{
    usage(argv[0]);
  }
  return 0; 
}