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
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  i64 ;

/* Variables and functions */
 int /*<<< orphan*/  FTS5_SEGMENT_ROWID (int,int) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_stricmp (char const*,char*) ; 
 int sqlite3_value_int (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fts5RowidFunction(
  sqlite3_context *pCtx,          /* Function call context */
  int nArg,                       /* Number of args (always 2) */
  sqlite3_value **apVal           /* Function arguments */
){
  const char *zArg;
  if( nArg==0 ){
    sqlite3_result_error(pCtx, "should be: fts5_rowid(subject, ....)", -1);
  }else{
    zArg = (const char*)sqlite3_value_text(apVal[0]);
    if( 0==sqlite3_stricmp(zArg, "segment") ){
      i64 iRowid;
      int segid, pgno;
      if( nArg!=3 ){
        sqlite3_result_error(pCtx, 
            "should be: fts5_rowid('segment', segid, pgno))", -1
        );
      }else{
        segid = sqlite3_value_int(apVal[1]);
        pgno = sqlite3_value_int(apVal[2]);
        iRowid = FTS5_SEGMENT_ROWID(segid, pgno);
        sqlite3_result_int64(pCtx, iRowid);
      }
    }else{
      sqlite3_result_error(pCtx, 
        "first arg to fts5_rowid() must be 'segment'" , -1
      );
    }
  }
}