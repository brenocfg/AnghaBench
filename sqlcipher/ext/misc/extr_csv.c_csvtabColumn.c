#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ pVtab; } ;
typedef  TYPE_1__ sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_7__ {scalar_t__* azVal; } ;
struct TYPE_6__ {int nCol; } ;
typedef  TYPE_2__ CsvTable ;
typedef  TYPE_3__ CsvCursor ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int csvtabColumn(
  sqlite3_vtab_cursor *cur,   /* The cursor */
  sqlite3_context *ctx,       /* First argument to sqlite3_result_...() */
  int i                       /* Which column to return */
){
  CsvCursor *pCur = (CsvCursor*)cur;
  CsvTable *pTab = (CsvTable*)cur->pVtab;
  if( i>=0 && i<pTab->nCol && pCur->azVal[i]!=0 ){
    sqlite3_result_text(ctx, pCur->azVal[i], -1, SQLITE_STATIC);
  }
  return SQLITE_OK;
}