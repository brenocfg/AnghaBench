#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_guid_t ;
struct TYPE_3__ {TYPE_2__* p_next; int /*<<< orphan*/  i_object_id; TYPE_2__* p_first; } ;
struct TYPE_4__ {TYPE_1__ common; } ;
typedef  TYPE_2__ asf_object_t ;

/* Variables and functions */
 scalar_t__ guidcmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int ASF_CountObject( void *_p_obj, const vlc_guid_t *p_guid )
{
    int i_count;
    asf_object_t *p_child, *p_obj;

    p_obj = (asf_object_t *)_p_obj;
    if( !p_obj )
        return 0;

    i_count = 0;
    p_child = p_obj->common.p_first;
    while( p_child )
    {
        if( guidcmp( &p_child->common.i_object_id, p_guid ) )
            i_count++;

        p_child = p_child->common.p_next;
    }
    return i_count;
}