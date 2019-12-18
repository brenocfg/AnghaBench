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
typedef  int /*<<< orphan*/  overlay_t ;
struct TYPE_3__ {int /*<<< orphan*/ * pp_head; int /*<<< orphan*/ * pp_tail; } ;
typedef  TYPE_1__ list_t ;

/* Variables and functions */
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/ * calloc (int,int) ; 

int do_ListInit( list_t *p_list )
{
    p_list->pp_head = calloc( 16, sizeof( overlay_t * ) );
    if( p_list->pp_head == NULL )
        return VLC_ENOMEM;

    p_list->pp_tail = p_list->pp_head + 16;
    return VLC_SUCCESS;
}