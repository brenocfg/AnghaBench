#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char const* table_name; } ;
typedef  size_t CatalogTable ;

/* Variables and functions */
 TYPE_1__* catalog_table_names ; 

__attribute__((used)) static const char *
catalog_table_name(CatalogTable table)
{
	return catalog_table_names[table].table_name;
}