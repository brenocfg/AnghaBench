#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_3__ {scalar_t__ iRowid; size_t iDb; int /*<<< orphan*/ * aVal; int /*<<< orphan*/ * azDb; } ;
typedef  TYPE_1__ memstat_cursor ;
struct TYPE_4__ {int mNull; int /*<<< orphan*/  zName; } ;

/* Variables and functions */
#define  MSV_COLUMN_HIWTR 131 
#define  MSV_COLUMN_NAME 130 
#define  MSV_COLUMN_SCHEMA 129 
#define  MSV_COLUMN_VALUE 128 
 scalar_t__ MSV_NROW ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 TYPE_2__* aMemstatColumn ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3_result_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int memstatColumn(
  sqlite3_vtab_cursor *cur,   /* The cursor */
  sqlite3_context *ctx,       /* First argument to sqlite3_result_...() */
  int iCol                    /* Which column to return */
){
  memstat_cursor *pCur = (memstat_cursor*)cur;
  int i;
  assert( pCur->iRowid>0 && pCur->iRowid<=MSV_NROW );
  i = (int)pCur->iRowid - 1;
  if( (aMemstatColumn[i].mNull & (1<<iCol))!=0 ){
    return SQLITE_OK;
  }
  switch( iCol ){
    case MSV_COLUMN_NAME: {
      sqlite3_result_text(ctx, aMemstatColumn[i].zName, -1, SQLITE_STATIC);
      break;
    }
    case MSV_COLUMN_SCHEMA: {
      sqlite3_result_text(ctx, pCur->azDb[pCur->iDb], -1, 0);
      break;
    }
    case MSV_COLUMN_VALUE: {
      sqlite3_result_int64(ctx, pCur->aVal[0]);
      break;
    }
    case MSV_COLUMN_HIWTR: {
      sqlite3_result_int64(ctx, pCur->aVal[1]);
      break;
    }
  }
  return SQLITE_OK;
}