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
typedef  int /*<<< orphan*/  TimeRange ;
typedef  int /*<<< orphan*/  SchemaAndName ;
typedef  int /*<<< orphan*/  Name ;

/* Variables and functions */
 int /*<<< orphan*/  spi_delete_materializations (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_insert_materializations (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spi_update_materializations(SchemaAndName partial_view, SchemaAndName materialization_table,
							Name time_column_name, TimeRange invalidation_range)
{
	spi_delete_materializations(materialization_table, time_column_name, invalidation_range);
	spi_insert_materializations(partial_view,
								materialization_table,
								time_column_name,
								invalidation_range);
}