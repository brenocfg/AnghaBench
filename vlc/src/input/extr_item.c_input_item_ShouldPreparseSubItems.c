#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int i_preparse_depth; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

bool input_item_ShouldPreparseSubItems( input_item_t *p_item )
{
    bool b_ret;

    vlc_mutex_lock( &p_item->lock );
    b_ret = p_item->i_preparse_depth == -1 ? true : p_item->i_preparse_depth > 0;
    vlc_mutex_unlock( &p_item->lock );

    return b_ret;
}