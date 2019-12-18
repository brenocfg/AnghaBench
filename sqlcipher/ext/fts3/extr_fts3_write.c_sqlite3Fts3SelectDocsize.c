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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3_int64 ;
typedef  int /*<<< orphan*/  Fts3Table ;

/* Variables and functions */
 int fts3SelectDocsize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

int sqlite3Fts3SelectDocsize(
  Fts3Table *pTab,                /* Fts3 table handle */
  sqlite3_int64 iDocid,           /* Docid to read size data for */
  sqlite3_stmt **ppStmt           /* OUT: Statement handle */
){
  return fts3SelectDocsize(pTab, iDocid, ppStmt);
}