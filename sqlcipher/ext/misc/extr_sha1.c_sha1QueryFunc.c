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
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int sqlite3_uint64 ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  double sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  SHA1Context ;

/* Variables and functions */
#define  SQLITE_BLOB 132 
#define  SQLITE_FLOAT 131 
#define  SQLITE_INTEGER 130 
#define  SQLITE_NULL 129 
 scalar_t__ SQLITE_ROW ; 
#define  SQLITE_TEXT 128 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  hash_finish (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hash_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_step (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int /*<<< orphan*/  hash_step_vformat (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memcpy (int*,double*,int) ; 
 unsigned char* sqlite3_column_blob (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_bytes (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_count (int /*<<< orphan*/ *) ; 
 double sqlite3_column_double (int /*<<< orphan*/ *,int) ; 
 double sqlite3_column_int64 (int /*<<< orphan*/ *,int) ; 
 unsigned char* sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * sqlite3_context_db_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*,...) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ **,char const**) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 char* sqlite3_sql (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_stmt_readonly (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void sha1QueryFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  sqlite3 *db = sqlite3_context_db_handle(context);
  const char *zSql = (const char*)sqlite3_value_text(argv[0]);
  sqlite3_stmt *pStmt = 0;
  int nCol;                   /* Number of columns in the result set */
  int i;                      /* Loop counter */
  int rc;
  int n;
  const char *z;
  SHA1Context cx;
  char zOut[44];

  assert( argc==1 );
  if( zSql==0 ) return;
  hash_init(&cx);
  while( zSql[0] ){
    rc = sqlite3_prepare_v2(db, zSql, -1, &pStmt, &zSql);
    if( rc ){
      char *zMsg = sqlite3_mprintf("error SQL statement [%s]: %s",
                                   zSql, sqlite3_errmsg(db));
      sqlite3_finalize(pStmt);
      sqlite3_result_error(context, zMsg, -1);
      sqlite3_free(zMsg);
      return;
    }
    if( !sqlite3_stmt_readonly(pStmt) ){
      char *zMsg = sqlite3_mprintf("non-query: [%s]", sqlite3_sql(pStmt));
      sqlite3_finalize(pStmt);
      sqlite3_result_error(context, zMsg, -1);
      sqlite3_free(zMsg);
      return;
    }
    nCol = sqlite3_column_count(pStmt);
    z = sqlite3_sql(pStmt);
    n = (int)strlen(z);
    hash_step_vformat(&cx,"S%d:",n);
    hash_step(&cx,(unsigned char*)z,n);

    /* Compute a hash over the result of the query */
    while( SQLITE_ROW==sqlite3_step(pStmt) ){
      hash_step(&cx,(const unsigned char*)"R",1);
      for(i=0; i<nCol; i++){
        switch( sqlite3_column_type(pStmt,i) ){
          case SQLITE_NULL: {
            hash_step(&cx, (const unsigned char*)"N",1);
            break;
          }
          case SQLITE_INTEGER: {
            sqlite3_uint64 u;
            int j;
            unsigned char x[9];
            sqlite3_int64 v = sqlite3_column_int64(pStmt,i);
            memcpy(&u, &v, 8);
            for(j=8; j>=1; j--){
              x[j] = u & 0xff;
              u >>= 8;
            }
            x[0] = 'I';
            hash_step(&cx, x, 9);
            break;
          }
          case SQLITE_FLOAT: {
            sqlite3_uint64 u;
            int j;
            unsigned char x[9];
            double r = sqlite3_column_double(pStmt,i);
            memcpy(&u, &r, 8);
            for(j=8; j>=1; j--){
              x[j] = u & 0xff;
              u >>= 8;
            }
            x[0] = 'F';
            hash_step(&cx,x,9);
            break;
          }
          case SQLITE_TEXT: {
            int n2 = sqlite3_column_bytes(pStmt, i);
            const unsigned char *z2 = sqlite3_column_text(pStmt, i);
            hash_step_vformat(&cx,"T%d:",n2);
            hash_step(&cx, z2, n2);
            break;
          }
          case SQLITE_BLOB: {
            int n2 = sqlite3_column_bytes(pStmt, i);
            const unsigned char *z2 = sqlite3_column_blob(pStmt, i);
            hash_step_vformat(&cx,"B%d:",n2);
            hash_step(&cx, z2, n2);
            break;
          }
        }
      }
    }
    sqlite3_finalize(pStmt);
  }
  hash_finish(&cx, zOut);
  sqlite3_result_text(context, zOut, 40, SQLITE_TRANSIENT);
}