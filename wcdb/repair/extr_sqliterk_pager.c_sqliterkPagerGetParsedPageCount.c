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
struct TYPE_3__ {scalar_t__* pagesStatus; int pagecount; } ;
typedef  TYPE_1__ sqliterk_pager ;

/* Variables and functions */
 scalar_t__ sqliterk_status_checked ; 

int sqliterkPagerGetParsedPageCount(sqliterk_pager *pager)
{
    if (!pager || !pager->pagesStatus) {
        return 0;
    }

    int i, count = 0;
    for (i = 0; i < pager->pagecount; i++) {
        if (pager->pagesStatus[i] == sqliterk_status_checked) {
            count++;
        }
    }
    return count;
}