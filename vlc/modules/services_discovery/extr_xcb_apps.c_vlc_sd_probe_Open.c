#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_connection_t ;
typedef  int /*<<< orphan*/  vlc_probe_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  SD_CAT_DEVICES ; 
 int VLC_PROBE_CONTINUE ; 
 int /*<<< orphan*/  free (char*) ; 
 char* var_InheritString (int /*<<< orphan*/ *,char*) ; 
 int vlc_sd_probe_Add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xcb_connect (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ xcb_connection_has_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_disconnect (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlc_sd_probe_Open (vlc_object_t *obj)
{
    vlc_probe_t *probe = (vlc_probe_t *)obj;

    char *display = var_InheritString (obj, "x11-display");
    xcb_connection_t *conn = xcb_connect (display, NULL);
    free (display);
    if (xcb_connection_has_error (conn))
        return VLC_PROBE_CONTINUE;
    xcb_disconnect (conn);
    return vlc_sd_probe_Add (probe, "xcb_apps",
                             N_("Screen capture"), SD_CAT_DEVICES);
}