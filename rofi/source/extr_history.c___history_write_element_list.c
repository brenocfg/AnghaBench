#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int index; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ _element ;
struct TYPE_6__ {unsigned int max_history_size; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  __element_sort_func ; 
 TYPE_3__ config ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_qsort_with_data (TYPE_1__**,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __history_write_element_list ( FILE *fd, _element **list, unsigned int length )
{
    if ( list == NULL || length == 0 ) {
        return;
    }
    // Sort the list before writing out.
    g_qsort_with_data ( list, length, sizeof ( _element* ), __element_sort_func, NULL );

    // Get minimum index.
    int min_value = list[length - 1]->index;

    // Set the max length of the list.
    length = ( length > config.max_history_size ) ? config.max_history_size : length;

    // Write out entries.
    for ( unsigned int iter = 0; iter < length; iter++ ) {
        fprintf ( fd, "%ld %s\n", list[iter]->index - min_value, list[iter]->name );
    }
}