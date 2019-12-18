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
struct TYPE_5__ {scalar_t__ pagecount; scalar_t__ pagesize; struct TYPE_5__* pagesStatus; int /*<<< orphan*/ * file; } ;
typedef  TYPE_1__ sqliterk_pager ;

/* Variables and functions */
 int SQLITERK_MISUSE ; 
 int SQLITERK_OK ; 
 int /*<<< orphan*/  sqliterkCryptoFreeCodec (TYPE_1__*) ; 
 int sqliterkOSClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqliterkOSFree (TYPE_1__*) ; 

int sqliterkPagerClose(sqliterk_pager *pager)
{
    if (!pager) {
        return SQLITERK_MISUSE;
    }
    int rc = SQLITERK_OK;
    if (pager->file) {
        rc = sqliterkOSClose(pager->file);
        pager->file = NULL;
    }
    if (pager->pagesStatus) {
        sqliterkOSFree(pager->pagesStatus);
        pager->pagesStatus = NULL;
    }
    pager->pagesize = 0;
    pager->pagecount = 0;

    sqliterkCryptoFreeCodec(pager);

    sqliterkOSFree(pager);
    return rc;
}