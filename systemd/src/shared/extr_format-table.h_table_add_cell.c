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
typedef  int /*<<< orphan*/  TableDataType ;
typedef  int /*<<< orphan*/  TableCell ;
typedef  int /*<<< orphan*/  Table ;

/* Variables and functions */
 int table_add_cell_full (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,void const*,size_t,size_t,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static inline int table_add_cell(Table *t, TableCell **ret_cell, TableDataType type, const void *data) {
        return table_add_cell_full(t, ret_cell, type, data, (size_t) -1, (size_t) -1, (unsigned) -1, (unsigned) -1, (unsigned) -1);
}