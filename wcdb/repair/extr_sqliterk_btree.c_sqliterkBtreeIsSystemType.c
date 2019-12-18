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
typedef  scalar_t__ sqliterk_btree_type ;

/* Variables and functions */
 scalar_t__ sqliterk_btree_type_system_begin ; 
 scalar_t__ sqliterk_btree_type_system_end ; 

int sqliterkBtreeIsSystemType(sqliterk_btree_type type)
{
    if (type >= sqliterk_btree_type_system_begin &&
        type < sqliterk_btree_type_system_end) {
        return 1;
    }
    return 0;
}