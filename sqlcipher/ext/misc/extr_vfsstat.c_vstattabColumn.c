#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_2__ {size_t i; } ;
typedef  TYPE_1__ VfsStatCursor ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 size_t VFSSTAT_ANY ; 
 size_t VFSSTAT_nStat ; 
#define  VSTAT_COLUMN_COUNT 130 
#define  VSTAT_COLUMN_FILE 129 
#define  VSTAT_COLUMN_STAT 128 
 int /*<<< orphan*/ * aVfsCnt ; 
 char const** azFile ; 
 char** azStat ; 
 char** azStatAny ; 
 int /*<<< orphan*/  sqlite3_result_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vstattabColumn(
  sqlite3_vtab_cursor *cur,   /* The cursor */
  sqlite3_context *ctx,       /* First argument to sqlite3_result_...() */
  int i                       /* Which column to return */
){
  VfsStatCursor *pCur = (VfsStatCursor*)cur;
  switch( i ){
    case VSTAT_COLUMN_FILE: {
      sqlite3_result_text(ctx, azFile[pCur->i/VFSSTAT_nStat], -1, SQLITE_STATIC);
      break;
    }
    case VSTAT_COLUMN_STAT: {
      const char **az;
      az = (pCur->i/VFSSTAT_nStat)==VFSSTAT_ANY ? azStatAny : azStat;
      sqlite3_result_text(ctx, az[pCur->i%VFSSTAT_nStat], -1, SQLITE_STATIC);
      break;
    }
    case VSTAT_COLUMN_COUNT: {
      sqlite3_result_int64(ctx, aVfsCnt[pCur->i]);
      break;
    }
  }
  return SQLITE_OK;
}