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
struct TYPE_4__ {int f_float; } ;
typedef  TYPE_1__ vlc_value_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  vout_ChangeZoom (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int ZoomCallback( vlc_object_t *obj, char const *name,
                         vlc_value_t prev, vlc_value_t cur, void *data )
{
    vout_thread_t *p_vout = (vout_thread_t *)obj;

    (void) name; (void) prev; (void) data;
    vout_ChangeZoom(p_vout, 1000 * cur.f_float, 1000);
    return VLC_SUCCESS;
}