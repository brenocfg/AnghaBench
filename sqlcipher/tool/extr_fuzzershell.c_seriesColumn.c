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
typedef  int /*<<< orphan*/  sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_2__ {int /*<<< orphan*/  iValue; int /*<<< orphan*/  iStep; int /*<<< orphan*/  mxValue; int /*<<< orphan*/  mnValue; } ;
typedef  TYPE_1__ series_cursor ;

/* Variables and functions */
#define  SERIES_COLUMN_START 130 
#define  SERIES_COLUMN_STEP 129 
#define  SERIES_COLUMN_STOP 128 
 int SQLITE_OK ; 
 int /*<<< orphan*/  sqlite3_result_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int seriesColumn(
  sqlite3_vtab_cursor *cur,   /* The cursor */
  sqlite3_context *ctx,       /* First argument to sqlite3_result_...() */
  int i                       /* Which column to return */
){
  series_cursor *pCur = (series_cursor*)cur;
  sqlite3_int64 x = 0;
  switch( i ){
    case SERIES_COLUMN_START:  x = pCur->mnValue; break;
    case SERIES_COLUMN_STOP:   x = pCur->mxValue; break;
    case SERIES_COLUMN_STEP:   x = pCur->iStep;   break;
    default:                   x = pCur->iValue;  break;
  }
  sqlite3_result_int64(ctx, x);
  return SQLITE_OK;
}