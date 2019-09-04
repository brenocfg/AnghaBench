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
typedef  int sqliterk_btree_type ;

/* Variables and functions */
#define  sqliterk_btree_type_autoindex 133 
#define  sqliterk_btree_type_index 132 
#define  sqliterk_btree_type_master 131 
#define  sqliterk_btree_type_sequence 130 
#define  sqliterk_btree_type_stat 129 
#define  sqliterk_btree_type_table 128 

const char *sqliterkBtreeGetTypeName(sqliterk_btree_type type)
{
    char *name;
    switch (type) {
        case sqliterk_btree_type_autoindex:
            name = "sqlite_autoindex";
            break;
        case sqliterk_btree_type_sequence:
            name = "sqlite_sequence";
            break;
        case sqliterk_btree_type_stat:
            name = "sqlite_stat";
            break;
        case sqliterk_btree_type_master:
            name = "sqlite_master";
            break;
        case sqliterk_btree_type_table:
            name = "table";
            break;
        case sqliterk_btree_type_index:
            name = "index";
            break;
        default:
            name = "unknown";
            break;
    }
    return name;
}