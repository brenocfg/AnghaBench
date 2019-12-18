#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int i_int; } ;
typedef  TYPE_1__ vlc_value_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_8__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ intf_thread_t ;
struct TYPE_9__ {int i_button_mask; int b_button_pressed; int /*<<< orphan*/  lock; int /*<<< orphan*/  i_last_y; int /*<<< orphan*/  i_last_x; } ;
typedef  TYPE_3__ intf_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  ProcessGesture (TYPE_2__*) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  var_GetCoords (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ButtonEvent( vlc_object_t *p_this, char const *psz_var,
                        vlc_value_t oldval, vlc_value_t val, void *p_data )
{
    intf_thread_t *p_intf = p_data;
    intf_sys_t *p_sys = p_intf->p_sys;

    (void) psz_var; (void) oldval;

    vlc_mutex_lock( &p_sys->lock );
    if( val.i_int & p_sys->i_button_mask )
    {
        if( !p_sys->b_button_pressed )
        {
            p_sys->b_button_pressed = true;
            var_GetCoords( p_this, "mouse-moved",
                           &p_sys->i_last_x, &p_sys->i_last_y );
        }
    }
    else
    {
        if( p_sys->b_button_pressed )
        {
            p_sys->b_button_pressed = false;
            ProcessGesture( p_intf );
        }
    }
    vlc_mutex_unlock( &p_sys->lock );

    return VLC_SUCCESS;
}