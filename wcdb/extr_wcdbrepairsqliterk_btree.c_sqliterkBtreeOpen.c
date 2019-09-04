#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqliterk_pager ;
struct TYPE_6__ {int maxLocal; int minLocal; int maxLeaf; int minLeaf; int /*<<< orphan*/ * rk; int /*<<< orphan*/ * pager; int /*<<< orphan*/  rootpage; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ sqliterk_btree ;
typedef  int /*<<< orphan*/  sqliterk ;

/* Variables and functions */
 int SQLITERK_DAMAGED ; 
 int SQLITERK_MISUSE ; 
 int SQLITERK_NOMEM ; 
 int SQLITERK_OK ; 
 int /*<<< orphan*/  sqliterkBtreeClose (TYPE_1__*) ; 
 int sqliterkBtreeSetMeta (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* sqliterkOSMalloc (int) ; 
 int sqliterkPageAcquire (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqliterkPageClearData (int /*<<< orphan*/ ) ; 
 int sqliterkPageGetType (int /*<<< orphan*/ ) ; 
 int sqliterkPagerGetUsableSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqliterk_btree_type_index ; 
 int /*<<< orphan*/  sqliterk_btree_type_master ; 
 int /*<<< orphan*/  sqliterk_btree_type_table ; 
#define  sqliterk_page_type_interior_index 131 
#define  sqliterk_page_type_interior_table 130 
#define  sqliterk_page_type_leaf_index 129 
#define  sqliterk_page_type_leaf_table 128 

int sqliterkBtreeOpen(sqliterk *rk,
                      sqliterk_pager *pager,
                      int rootPageno,
                      sqliterk_btree **btree)
{
    if (!pager || !btree) {
        return SQLITERK_MISUSE;
    }
    int rc = SQLITERK_OK;
    sqliterk_btree *theBtree = sqliterkOSMalloc(sizeof(sqliterk_btree));
    if (!theBtree) {
        rc = SQLITERK_NOMEM;
        goto sqliterkBtreeOpen_Failed;
    }
    theBtree->pager = pager;

    rc = sqliterkPageAcquire(theBtree->pager, rootPageno, &theBtree->rootpage);
    if (rc != SQLITERK_OK) {
        goto sqliterkBtreeOpen_Failed;
    }
    if (rootPageno == 1) {
        rc = sqliterkBtreeSetMeta(theBtree, "sqlite_master",
                                  sqliterk_btree_type_master);
        if (rc != SQLITERK_OK) {
            goto sqliterkBtreeOpen_Failed;
        }
    } else {
        switch (sqliterkPageGetType(theBtree->rootpage)) {
            case sqliterk_page_type_interior_index:
            case sqliterk_page_type_leaf_index:
                theBtree->type = sqliterk_btree_type_index;
                break;
            case sqliterk_page_type_interior_table:
            case sqliterk_page_type_leaf_table:
                theBtree->type = sqliterk_btree_type_table;
                break;
            default:
                rc = SQLITERK_DAMAGED;
                goto sqliterkBtreeOpen_Failed;
        }
    }
    // Save memory
    sqliterkPageClearData(theBtree->rootpage);

    theBtree->maxLocal =
        (sqliterkPagerGetUsableSize(theBtree->pager) - 12) * 64 / 255 - 23;
    theBtree->minLocal =
        (sqliterkPagerGetUsableSize(theBtree->pager) - 12) * 32 / 255 - 23;
    theBtree->maxLeaf = sqliterkPagerGetUsableSize(theBtree->pager) - 35;
    theBtree->minLeaf =
        (sqliterkPagerGetUsableSize(theBtree->pager) - 12) * 32 / 255 - 23;

    theBtree->rk = rk;

    *btree = theBtree;
    return SQLITERK_OK;

sqliterkBtreeOpen_Failed:
    if (theBtree) {
        sqliterkBtreeClose(theBtree);
    }
    *btree = NULL;
    return rc;
}