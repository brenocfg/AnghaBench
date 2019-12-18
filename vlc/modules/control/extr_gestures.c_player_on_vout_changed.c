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
typedef  int /*<<< orphan*/  vout_thread_t ;
typedef  int /*<<< orphan*/  vlc_player_t ;
typedef  int /*<<< orphan*/  vlc_es_id_t ;
struct TYPE_7__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ intf_thread_t ;
struct TYPE_9__ {size_t size; int /*<<< orphan*/ ** data; } ;
struct TYPE_8__ {TYPE_3__ vout_vector; } ;
typedef  TYPE_2__ intf_sys_t ;
typedef  enum vlc_vout_order { ____Placeholder_vlc_vout_order } vlc_vout_order ;
typedef  enum vlc_player_vout_action { ____Placeholder_vlc_player_vout_action } vlc_player_vout_action ;

/* Variables and functions */
 int /*<<< orphan*/  ButtonEvent ; 
 int /*<<< orphan*/  MovedEvent ; 
 scalar_t__ VIDEO_ES ; 
#define  VLC_PLAYER_VOUT_STARTED 129 
#define  VLC_PLAYER_VOUT_STOPPED 128 
 int /*<<< orphan*/  VLC_UNUSED (int) ; 
 int /*<<< orphan*/  var_AddCallback (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  var_DelCallback (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 scalar_t__ vlc_es_id_GetCat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_vector_push (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_vector_remove (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  vout_Hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
player_on_vout_changed(vlc_player_t *player,
                       enum vlc_player_vout_action action,
                       vout_thread_t *vout,
                       enum vlc_vout_order order,
                       vlc_es_id_t *es_id, void *data)
{
    VLC_UNUSED(player); VLC_UNUSED(order);
    intf_thread_t *intf = data;
    intf_sys_t *sys = intf->p_sys;

    if (vlc_es_id_GetCat(es_id) != VIDEO_ES)
        return;

    switch (action)
    {
        case VLC_PLAYER_VOUT_STARTED:
            if (vlc_vector_push(&sys->vout_vector, vout))
            {
                vout_Hold(vout);
                var_AddCallback(vout, "mouse-moved", MovedEvent, intf);
                var_AddCallback(vout, "mouse-button-down", ButtonEvent, intf);
            }
            break;
        case VLC_PLAYER_VOUT_STOPPED:
            for (size_t i = 0; i < sys->vout_vector.size; ++i)
            {
                vout_thread_t *it = sys->vout_vector.data[i];
                if (it == vout)
                {
                    vlc_vector_remove(&sys->vout_vector, i);
                    var_DelCallback(vout, "mouse-moved", MovedEvent, intf);
                    var_DelCallback(vout, "mouse-button-down", ButtonEvent, intf);
                    vout_Release(vout);
                    break;
                }
            }
            break;
        default:
            vlc_assert_unreachable();
    }
}