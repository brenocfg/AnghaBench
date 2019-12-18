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
typedef  int /*<<< orphan*/  input_item_t ;
struct TYPE_3__ {int /*<<< orphan*/  rc; } ;
typedef  TYPE_1__ input_item_owner_t ;

/* Variables and functions */
 TYPE_1__* item_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_atomic_rc_inc (int /*<<< orphan*/ *) ; 

input_item_t *input_item_Hold( input_item_t *p_item )
{
    input_item_owner_t *owner = item_owner(p_item);

    vlc_atomic_rc_inc( &owner->rc );
    return p_item;
}