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
struct TYPE_2__ {int /*<<< orphan*/  nStr; int /*<<< orphan*/  zStr; scalar_t__ iRowid; } ;
typedef  TYPE_1__ prefixes_cursor ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int prefixesColumn(
  sqlite3_vtab_cursor *cur,   /* The cursor */
  sqlite3_context *ctx,       /* First argument to sqlite3_result_...() */
  int i                       /* Which column to return */
){
  prefixes_cursor *pCur = (prefixes_cursor*)cur;
  switch( i ){
    case 0:
      sqlite3_result_text(ctx, pCur->zStr, pCur->nStr - (int)pCur->iRowid,
                          0); 
      break;
    default:
      sqlite3_result_text(ctx, pCur->zStr, pCur->nStr, 0);
      break;
  }
  return SQLITE_OK;
}