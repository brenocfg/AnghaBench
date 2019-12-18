#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
struct TYPE_3__ {int isEof; } ;
typedef  TYPE_1__ Fts3Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  fts3ClearCursor (TYPE_1__*) ; 

__attribute__((used)) static int fts3EofMethod(sqlite3_vtab_cursor *pCursor){
  Fts3Cursor *pCsr = (Fts3Cursor*)pCursor;
  if( pCsr->isEof ){
    fts3ClearCursor(pCsr);
    pCsr->isEof = 1;
  }
  return pCsr->isEof;
}