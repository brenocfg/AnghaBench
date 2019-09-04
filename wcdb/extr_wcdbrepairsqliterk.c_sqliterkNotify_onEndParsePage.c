#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqliterk_btree ;
struct TYPE_5__ {int /*<<< orphan*/  (* didParsePage ) (TYPE_2__*,int) ;} ;
struct TYPE_6__ {TYPE_1__ notify; int /*<<< orphan*/  pager; } ;
typedef  TYPE_2__ sqliterk ;

/* Variables and functions */
#define  SQLITERK_CANCELLED 130 
#define  SQLITERK_DAMAGED 129 
 int /*<<< orphan*/  SQLITERK_MISUSE ; 
#define  SQLITERK_OK 128 
 int /*<<< orphan*/  sqliterkOSDebug (int const,char*,int) ; 
 int /*<<< orphan*/  sqliterkOSWarning (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sqliterkPagerSetStatus (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqliterk_status_checked ; 
 int /*<<< orphan*/  sqliterk_status_damaged ; 
 int /*<<< orphan*/  sqliterk_status_invalid ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 

__attribute__((used)) static void sqliterkNotify_onEndParsePage(sqliterk *rk,
                                          sqliterk_btree *btree,
                                          int pageno,
                                          int result)
{
    if (!rk) {
        return;
    }
    switch (result) {
        case SQLITERK_OK:
            sqliterkPagerSetStatus(rk->pager, pageno, sqliterk_status_checked);
            break;
        case SQLITERK_DAMAGED:
            sqliterkPagerSetStatus(rk->pager, pageno, sqliterk_status_damaged);
            break;
        case SQLITERK_CANCELLED:
            sqliterkOSDebug(SQLITERK_CANCELLED, "Cancelled parsing page %d.",
                            pageno);
            break;
        default:
            sqliterkOSWarning(SQLITERK_MISUSE,
                              "Cannot parse page %d. Invalid type.", pageno);
            sqliterkPagerSetStatus(rk->pager, pageno, sqliterk_status_invalid);
            break;
    }
    //sqliterkOSDebug(result, "sqliterkNotify_onEndParsePage: %d", pageno);
    if (rk->notify.didParsePage) {
        rk->notify.didParsePage(rk, pageno);
    }
}