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
struct TYPE_2__ {int nToken; int /*<<< orphan*/  iPos; int /*<<< orphan*/  iEnd; int /*<<< orphan*/  iStart; int /*<<< orphan*/  zToken; int /*<<< orphan*/  zInput; } ;
typedef  TYPE_1__ Fts3tokCursor ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fts3tokColumnMethod(
  sqlite3_vtab_cursor *pCursor,   /* Cursor to retrieve value from */
  sqlite3_context *pCtx,          /* Context for sqlite3_result_xxx() calls */
  int iCol                        /* Index of column to read value from */
){
  Fts3tokCursor *pCsr = (Fts3tokCursor *)pCursor;

  /* CREATE TABLE x(input, token, start, end, position) */
  switch( iCol ){
    case 0:
      sqlite3_result_text(pCtx, pCsr->zInput, -1, SQLITE_TRANSIENT);
      break;
    case 1:
      sqlite3_result_text(pCtx, pCsr->zToken, pCsr->nToken, SQLITE_TRANSIENT);
      break;
    case 2:
      sqlite3_result_int(pCtx, pCsr->iStart);
      break;
    case 3:
      sqlite3_result_int(pCtx, pCsr->iEnd);
      break;
    default:
      assert( iCol==4 );
      sqlite3_result_int(pCtx, pCsr->iPos);
      break;
  }
  return SQLITE_OK;
}