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
typedef  int /*<<< orphan*/  input_thread_t ;
typedef  int /*<<< orphan*/  input_item_t ;
struct TYPE_2__ {int /*<<< orphan*/ * p_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* input_priv (int /*<<< orphan*/ *) ; 

input_item_t *input_GetItem( input_thread_t *p_input )
{
    assert( p_input != NULL );
    return input_priv(p_input)->p_item;
}