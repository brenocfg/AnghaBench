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
struct column {scalar_t__ name; } ;
typedef  struct column WCHAR ;
typedef  size_t UINT ;

/* Variables and functions */
 int /*<<< orphan*/  heap_free (struct column*) ; 

void free_columns( struct column *columns, UINT num_cols )
{
    UINT i;

    for (i = 0; i < num_cols; i++) { heap_free( (WCHAR *)columns[i].name ); }
    heap_free( columns );
}