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
typedef  int /*<<< orphan*/  vout_thread_t ;
struct TYPE_4__ {scalar_t__ b_bool; } ;
typedef  TYPE_1__ vlc_value_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VOUT_WINDOW_STATE_BELOW ; 
 int /*<<< orphan*/  var_TriggerCallback (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vout_ChangeFullscreen (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_ChangeWindowState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int WallPaperCallback( vlc_object_t *obj, char const *name,
                              vlc_value_t prev, vlc_value_t cur, void *data )
{
    vout_thread_t *vout = (vout_thread_t *)obj;

    if( cur.b_bool )
    {
        vout_ChangeWindowState(vout, VOUT_WINDOW_STATE_BELOW);
        vout_ChangeFullscreen(vout, NULL);
    }
    else
    {
        var_TriggerCallback( obj, "fullscreen" );
        var_TriggerCallback( obj, "video-on-top" );
    }
    (void) name; (void) prev; (void) data;
    return VLC_SUCCESS;
}