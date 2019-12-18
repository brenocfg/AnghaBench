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
#define  SQLITE_BLOB 132 
 int SQLITE_DONE ; 
#define  SQLITE_FLOAT 131 
#define  SQLITE_INTEGER 130 
#define  SQLITE_NULL 129 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
#define  SQLITE_TEXT 128 
 int eVerbosity ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ isspace (char const) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (unsigned char const) ; 
 scalar_t__ sqlite3_column_blob (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_bytes (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_count (int /*<<< orphan*/ *) ; 
 char* sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_type (int /*<<< orphan*/ *,int) ; 
 char* sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int runDbSql(sqlite3 *db, const char *zSql){
  int rc;
  sqlite3_stmt *pStmt;
  while( isspace(zSql[0]&0x7f) ) zSql++;
  if( zSql[0]==0 ) return SQLITE_OK;
  if( eVerbosity>=4 ){
    printf("RUNNING-SQL: [%s]\n", zSql);
    fflush(stdout);
  }
  rc = sqlite3_prepare_v2(db, zSql, -1, &pStmt, 0);
  if( rc==SQLITE_OK ){
    while( (rc = sqlite3_step(pStmt))==SQLITE_ROW ){
      if( eVerbosity>=5 ){
        int j;
        for(j=0; j<sqlite3_column_count(pStmt); j++){
          if( j ) printf(",");
          switch( sqlite3_column_type(pStmt, j) ){
            case SQLITE_NULL: {
              printf("NULL");
              break;
            }
            case SQLITE_INTEGER:
            case SQLITE_FLOAT: {
              printf("%s", sqlite3_column_text(pStmt, j));
              break;
            }
            case SQLITE_BLOB: {
              int n = sqlite3_column_bytes(pStmt, j);
              int i;
              const unsigned char *a;
              a = (const unsigned char*)sqlite3_column_blob(pStmt, j);
              printf("x'");
              for(i=0; i<n; i++){
                printf("%02x", a[i]);
              }
              printf("'");
              break;
            }
            case SQLITE_TEXT: {
              int n = sqlite3_column_bytes(pStmt, j);
              int i;
              const unsigned char *a;
              a = (const unsigned char*)sqlite3_column_blob(pStmt, j);
              printf("'");
              for(i=0; i<n; i++){
                if( a[i]=='\'' ){
                  printf("''");
                }else{
                  putchar(a[i]);
                }
              }
              printf("'");
              break;
            }
          } /* End switch() */
        } /* End for() */
        printf("\n");
        fflush(stdout);
      } /* End if( eVerbosity>=5 ) */
    } /* End while( SQLITE_ROW */
    if( rc!=SQLITE_DONE && eVerbosity>=4 ){
      printf("SQL-ERROR: (%d) %s\n", rc, sqlite3_errmsg(db));
      fflush(stdout);
    }
  }else if( eVerbosity>=4 ){
    printf("SQL-ERROR (%d): %s\n", rc, sqlite3_errmsg(db));
    fflush(stdout);    
  } /* End if( SQLITE_OK ) */
  return sqlite3_finalize(pStmt);
}