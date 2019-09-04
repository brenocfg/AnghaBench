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
struct table {TYPE_1__* columns; } ;
typedef  size_t UINT ;
struct TYPE_2__ {int type; } ;
typedef  int BOOL ;

/* Variables and functions */
 int COL_FLAG_METHOD ; 

BOOL is_method( const struct table *table, UINT column )
{
    return table->columns[column].type & COL_FLAG_METHOD;
}