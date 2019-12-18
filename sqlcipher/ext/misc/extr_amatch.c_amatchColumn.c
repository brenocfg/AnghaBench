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
struct TYPE_4__ {int /*<<< orphan*/  nWord; int /*<<< orphan*/  iLang; TYPE_1__* pCurrent; } ;
typedef  TYPE_2__ amatch_cursor ;
struct TYPE_3__ {int /*<<< orphan*/  rCost; int /*<<< orphan*/  zWord; } ;

/* Variables and functions */
#define  AMATCH_COL_DISTANCE 131 
#define  AMATCH_COL_LANGUAGE 130 
#define  AMATCH_COL_NWORD 129 
#define  AMATCH_COL_WORD 128 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amatchColumn(sqlite3_vtab_cursor *cur, sqlite3_context *ctx, int i){
  amatch_cursor *pCur = (amatch_cursor*)cur;
  switch( i ){
    case AMATCH_COL_WORD: {
      sqlite3_result_text(ctx, pCur->pCurrent->zWord+2, -1, SQLITE_STATIC);
      break;
    }
    case AMATCH_COL_DISTANCE: {
      sqlite3_result_int(ctx, pCur->pCurrent->rCost);
      break;
    }
    case AMATCH_COL_LANGUAGE: {
      sqlite3_result_int(ctx, pCur->iLang);
      break;
    }
    case AMATCH_COL_NWORD: {
      sqlite3_result_int(ctx, pCur->nWord);
      break;
    }
    default: {
      sqlite3_result_null(ctx);
      break;
    }
  }
  return SQLITE_OK;
}