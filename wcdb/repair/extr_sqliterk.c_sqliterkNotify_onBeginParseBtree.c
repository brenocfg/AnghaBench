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
typedef  int /*<<< orphan*/  sqliterk_table ;
typedef  int /*<<< orphan*/  sqliterk_page ;
typedef  int /*<<< orphan*/  sqliterk_btree ;
struct TYPE_5__ {int /*<<< orphan*/  (* onBeginParseTable ) (TYPE_2__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {TYPE_1__ notify; } ;
typedef  TYPE_2__ sqliterk ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITERK_OK ; 
 int /*<<< orphan*/  sqliterkBtreeGetName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqliterkBtreeGetRootPage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqliterkBtreeGetType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqliterkBtreeGetTypeName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqliterkOSDebug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqliterkPageGetPageno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sqliterkNotify_onBeginParseBtree(sqliterk *rk,
                                             sqliterk_btree *btree)
{
    if (rk->notify.onBeginParseTable) {
        rk->notify.onBeginParseTable(rk, (sqliterk_table *) btree);
    }
    sqliterk_page *rootpage = sqliterkBtreeGetRootPage(btree);
    sqliterkOSDebug(
        SQLITERK_OK, "Parsing B-tree -> [root: %d, name: %s, type: %s]",
        sqliterkPageGetPageno(rootpage), sqliterkBtreeGetName(btree),
        sqliterkBtreeGetTypeName(sqliterkBtreeGetType(btree)));
}