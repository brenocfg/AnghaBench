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
struct TYPE_2__ {int index; } ;
typedef  TYPE_1__ _element ;

/* Variables and functions */

__attribute__((used)) static int __element_sort_func ( const void *ea, const void *eb, void *data __attribute__( ( unused ) ) )
{
    _element *a = *(_element * *) ea;
    _element *b = *(_element * *) eb;
    return b->index - a->index;
}