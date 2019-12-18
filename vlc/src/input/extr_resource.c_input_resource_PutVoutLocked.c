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
typedef  int /*<<< orphan*/  vout_thread_t ;
struct TYPE_3__ {scalar_t__ i_vout; int /*<<< orphan*/  lock_hold; int /*<<< orphan*/ ** pp_vout; int /*<<< orphan*/  p_parent; int /*<<< orphan*/ * p_vout_free; } ;
typedef  TYPE_1__ input_resource_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAB_FIND (scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TAB_REMOVE (scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_Close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void input_resource_PutVoutLocked(input_resource_t *p_resource,
                                         vout_thread_t *vout)
{
    assert(vout != NULL);
    vlc_mutex_lock(&p_resource->lock_hold);
    assert( p_resource->i_vout > 0 );

    if (p_resource->pp_vout[0] == vout)
    {
        vlc_mutex_unlock(&p_resource->lock_hold);

        assert(p_resource->p_vout_free == NULL || p_resource->p_vout_free == vout);
        msg_Dbg(p_resource->p_parent, "saving a free vout");
        p_resource->p_vout_free = vout;
    }
    else
    {
        msg_Dbg(p_resource->p_parent, "destroying vout (already one saved or active)");
#ifndef NDEBUG
        {
            int index;
            TAB_FIND(p_resource->i_vout, p_resource->pp_vout, vout, index);
            assert(index >= 0);
        }
#endif

        TAB_REMOVE(p_resource->i_vout, p_resource->pp_vout, vout);
        vlc_mutex_unlock(&p_resource->lock_hold);
        vout_Close(vout);
    }
}