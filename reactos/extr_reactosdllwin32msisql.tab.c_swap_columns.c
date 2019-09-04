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
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ column_info ;

/* Variables and functions */

__attribute__((used)) static void swap_columns( column_info **cols, column_info *A, int idx )
{
    column_info *preA = NULL, *preB = NULL, *B, *ptr;
    int i = 0;

    B = NULL;
    ptr = *cols;
    while( ptr )
    {
        if( i++ == idx )
            B = ptr;
        else if( !B )
            preB = ptr;

        if( ptr->next == A )
            preA = ptr;

        ptr = ptr->next;
    }

    if( preB ) preB->next = A;
    if( preA ) preA->next = B;
    ptr = A->next;
    A->next = B->next;
    B->next = ptr;
    if( idx == 0 )
      *cols = A;
}