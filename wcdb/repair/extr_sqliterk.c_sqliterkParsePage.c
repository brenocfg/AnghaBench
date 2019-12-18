#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqliterk_btree ;
struct TYPE_5__ {int /*<<< orphan*/  pager; } ;
typedef  TYPE_1__ sqliterk ;

/* Variables and functions */
 int SQLITERK_MISUSE ; 
 int SQLITERK_OK ; 
 int /*<<< orphan*/  sqliterkBtreeClose (int /*<<< orphan*/ *) ; 
 int sqliterkBtreeOpen (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 scalar_t__ sqliterkPagerGetStatus (int /*<<< orphan*/ ,int) ; 
 int sqliterkParseBtree (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ sqliterk_status_unchecked ; 

int sqliterkParsePage(sqliterk *rk, int pageno)
{
    if (!rk) {
        return SQLITERK_MISUSE;
    }
    if (sqliterkPagerGetStatus(rk->pager, pageno) !=
        sqliterk_status_unchecked) {
        return SQLITERK_OK;
    }
    int rc = SQLITERK_OK;
    sqliterk_btree *btree = NULL;
    rc = sqliterkBtreeOpen(rk, rk->pager, pageno, &btree);
    if (rc != SQLITERK_OK) {
        goto sqliterkParsePage_End;
    }
    rc = sqliterkParseBtree(rk, btree);
sqliterkParsePage_End:
    if (btree) {
        sqliterkBtreeClose(btree);
    }
    return rc;
}