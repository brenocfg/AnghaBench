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
typedef  int /*<<< orphan*/  sqliterk_btree ;
struct TYPE_3__ {int /*<<< orphan*/  pager; } ;
typedef  TYPE_1__ sqliterk ;

/* Variables and functions */
 int SQLITERK_MISUSE ; 
 int SQLITERK_OK ; 
 scalar_t__ sqliterkPagerGetStatus (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqliterkPagerSetStatus (int /*<<< orphan*/ ,int,scalar_t__) ; 
 scalar_t__ sqliterk_status_checking ; 

__attribute__((used)) static int
sqliterkNotify_onBeginParsePage(sqliterk *rk, sqliterk_btree *btree, int pageno)
{
    //sqliterkOSDebug(SQLITERK_OK, "sqliterkNotify_onBeginParsePage: %d", pageno);
    if (sqliterkPagerGetStatus(rk->pager, pageno) == sqliterk_status_checking) {
        return SQLITERK_MISUSE;
    }
    sqliterkPagerSetStatus(rk->pager, pageno, sqliterk_status_checking);
    return SQLITERK_OK;
}