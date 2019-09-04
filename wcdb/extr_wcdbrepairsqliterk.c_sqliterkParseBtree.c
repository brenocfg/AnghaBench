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
typedef  int /*<<< orphan*/  sqliterk_page ;
typedef  int /*<<< orphan*/  sqliterk_btree ;
struct TYPE_3__ {int /*<<< orphan*/  listen; int /*<<< orphan*/  pager; } ;
typedef  TYPE_1__ sqliterk ;

/* Variables and functions */
 int SQLITERK_MISUSE ; 
 int SQLITERK_OK ; 
 int /*<<< orphan*/ * sqliterkBtreeGetRootPage (int /*<<< orphan*/ *) ; 
 int sqliterkBtreeParse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqliterkBtreeSetNotify (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sqliterkPageGetPageno (int /*<<< orphan*/ *) ; 
 int sqliterkPagerIsPagenoValid (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sqliterkParseBtree(sqliterk *rk, sqliterk_btree *btree)
{
    if (!rk) {
        return SQLITERK_MISUSE;
    }
    sqliterk_page *page = sqliterkBtreeGetRootPage(btree);
    int pageno = sqliterkPageGetPageno(page);
    if (!page || sqliterkPagerIsPagenoValid(rk->pager, pageno) != SQLITERK_OK) {
        return SQLITERK_MISUSE;
    }
    int rc = SQLITERK_OK;
    sqliterkBtreeSetNotify(btree, &rk->listen);
    rc = sqliterkBtreeParse(btree);
    return rc;
}