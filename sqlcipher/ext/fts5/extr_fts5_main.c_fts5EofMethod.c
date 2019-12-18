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
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  Fts5Cursor ;

/* Variables and functions */
 scalar_t__ CsrFlagTest (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTS5CSR_EOF ; 

__attribute__((used)) static int fts5EofMethod(sqlite3_vtab_cursor *pCursor){
  Fts5Cursor *pCsr = (Fts5Cursor*)pCursor;
  return (CsrFlagTest(pCsr, FTS5CSR_EOF) ? 1 : 0);
}