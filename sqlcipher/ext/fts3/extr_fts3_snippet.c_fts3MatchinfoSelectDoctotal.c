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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  scalar_t__ sqlite3_int64 ;
typedef  int /*<<< orphan*/  Fts3Table ;

/* Variables and functions */
 int FTS_CORRUPT_VTAB ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3Fts3GetVarint (char const*,scalar_t__*) ; 
 int sqlite3Fts3SelectDoctotal (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 char* sqlite3_column_blob (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_data_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts3MatchinfoSelectDoctotal(
  Fts3Table *pTab,
  sqlite3_stmt **ppStmt,
  sqlite3_int64 *pnDoc,
  const char **paLen
){
  sqlite3_stmt *pStmt;
  const char *a;
  sqlite3_int64 nDoc;

  if( !*ppStmt ){
    int rc = sqlite3Fts3SelectDoctotal(pTab, ppStmt);
    if( rc!=SQLITE_OK ) return rc;
  }
  pStmt = *ppStmt;
  assert( sqlite3_data_count(pStmt)==1 );

  a = sqlite3_column_blob(pStmt, 0);
  a += sqlite3Fts3GetVarint(a, &nDoc);
  if( nDoc==0 ) return FTS_CORRUPT_VTAB;
  *pnDoc = (u32)nDoc;

  if( paLen ) *paLen = a;
  return SQLITE_OK;
}