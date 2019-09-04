#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int sortcount; scalar_t__* sorted; } ;
typedef  TYPE_1__ string_table ;
typedef  scalar_t__ UINT ;

/* Variables and functions */
 int find_insert_index (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,int) ; 

__attribute__((used)) static void insert_string_sorted( string_table *st, UINT string_id )
{
    int i;

    i = find_insert_index( st, string_id );
    if (i == -1)
        return;

    memmove( &st->sorted[i] + 1, &st->sorted[i], (st->sortcount - i) * sizeof(UINT) );
    st->sorted[i] = string_id;
    st->sortcount++;
}