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
 int /*<<< orphan*/  VOUT_WINDOW_STATE_ABOVE ; 
 int /*<<< orphan*/  VOUT_WINDOW_STATE_NORMAL ; 
 int /*<<< orphan*/  vout_ChangeWindowState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int AboveCallback( vlc_object_t *obj, char const *name,
                          vlc_value_t prev, vlc_value_t cur, void *data )
{
    vout_ChangeWindowState((vout_thread_t *)obj,
        cur.b_bool ? VOUT_WINDOW_STATE_ABOVE : VOUT_WINDOW_STATE_NORMAL);
    (void) name; (void) prev; (void) data;
    return VLC_SUCCESS;
}