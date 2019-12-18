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
typedef  int /*<<< orphan*/  sqliterk_table ;
typedef  int /*<<< orphan*/  sqliterk_btree ;

/* Variables and functions */
 void* sqliterkBtreeGetUserInfo (int /*<<< orphan*/ *) ; 

void *sqliterk_table_get_user_info(sqliterk_table *table)
{
    return sqliterkBtreeGetUserInfo((sqliterk_btree *) table);
}