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
struct table {scalar_t__ num_cols; } ;
typedef  scalar_t__ UINT ;

/* Variables and functions */
 scalar_t__ get_column_offset (struct table const*,scalar_t__) ; 
 scalar_t__ get_column_size (struct table const*,scalar_t__) ; 

__attribute__((used)) static UINT get_row_size( const struct table *table )
{
    return get_column_offset( table, table->num_cols - 1 ) + get_column_size( table, table->num_cols - 1 );
}