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
typedef  int sqliterk_page_type ;

/* Variables and functions */
#define  sqliterk_page_type_interior_index 131 
#define  sqliterk_page_type_interior_table 130 
#define  sqliterk_page_type_leaf_index 129 
#define  sqliterk_page_type_leaf_table 128 

const char *sqliterkPageGetTypeName(sqliterk_page_type type)
{
    char *name;
    switch (type) {
        case sqliterk_page_type_interior_index:
            name = "interior-index btree";
            break;
        case sqliterk_page_type_interior_table:
            name = "interior-table btree";
            break;
        case sqliterk_page_type_leaf_index:
            name = "leaf-index btree";
            break;
        case sqliterk_page_type_leaf_table:
            name = "leaf-table btree";
            break;
        default:
            name = "unknown page";
            break;
    }
    return name;
}