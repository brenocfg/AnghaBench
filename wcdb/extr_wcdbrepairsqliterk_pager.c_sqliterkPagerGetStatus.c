#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqliterk_status ;
struct TYPE_4__ {int /*<<< orphan*/ * pagesStatus; } ;
typedef  TYPE_1__ sqliterk_pager ;

/* Variables and functions */
 scalar_t__ SQLITERK_OK ; 
 scalar_t__ sqliterkPagerIsPagenoValid (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sqliterk_status_invalid ; 

sqliterk_status sqliterkPagerGetStatus(sqliterk_pager *pager, int pageno)
{
    if (!pager || !pager->pagesStatus ||
        sqliterkPagerIsPagenoValid(pager, pageno) != SQLITERK_OK) {
        return sqliterk_status_invalid;
    }
    return pager->pagesStatus[pageno - 1];
}