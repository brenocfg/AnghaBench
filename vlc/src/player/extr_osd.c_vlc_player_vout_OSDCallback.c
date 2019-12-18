#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vout_thread_t ;
struct TYPE_6__ {float i_int; char* psz_string; float f_float; scalar_t__ b_bool; } ;
typedef  TYPE_1__ vlc_value_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (TYPE_1__) ; 
 int /*<<< orphan*/  VLC_VAR_FLOAT ; 
 int /*<<< orphan*/  VLC_VAR_STRING ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int var_GetInteger (int /*<<< orphan*/ *,char*) ; 
 char* var_GetString (int /*<<< orphan*/ *,char*) ; 
 int vout_osd_PrintVariableText (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vouts_osd_Message (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,...) ; 

int
vlc_player_vout_OSDCallback(vlc_object_t *this, const char *var,
                            vlc_value_t oldval, vlc_value_t newval, void *data)
{
    VLC_UNUSED(oldval);

    vout_thread_t *vout = (vout_thread_t *)this;

    if (strcmp(var, "aspect-ratio") == 0)
        vout_osd_PrintVariableText(vout, var, VLC_VAR_STRING,
                                   newval, _("Aspect ratio: %s"));

    else if (strcmp(var, "autoscale") == 0)
        vouts_osd_Message(&vout, 1, newval.b_bool ?
                          _("Scaled to screen") : _("Original size"));

    else if (strcmp(var, "crop") == 0)
        vout_osd_PrintVariableText(vout, var, VLC_VAR_STRING, newval,
                                   _("Crop: %s"));

    else if (strcmp(var, "crop-bottom") == 0)
        vouts_osd_Message(&vout, 1, _("Bottom crop: %d px"), newval.i_int);

    else if (strcmp(var, "crop-top") == 0)
        vouts_osd_Message(&vout, 1, _("Top crop: %d px"), newval.i_int);

    else if (strcmp(var, "crop-left") == 0)
        vouts_osd_Message(&vout, 1, _("Left crop: %d px"), newval.i_int);

    else if (strcmp(var, "crop-right") == 0)
        vouts_osd_Message(&vout, 1, _("Right crop: %d px"), newval.i_int);

    else if (strcmp(var, "deinterlace") == 0 ||
             strcmp(var, "deinterlace-mode") == 0)
    {
        bool varmode = strcmp(var, "deinterlace-mode") == 0;
        int on = !varmode ?
            newval.i_int : var_GetInteger(vout, "deinterlace");
        char *mode = varmode ?
            newval.psz_string : var_GetString(vout, "deinterlace-mode");
        vouts_osd_Message(&vout, 1, _("Deinterlace %s (%s)"),
                          on == 1 ? _("On") : _("Off"), mode);
        if (!varmode)
            free(mode);
    }

    else if (strcmp(var, "sub-margin") == 0)
        vouts_osd_Message(&vout, 1, _("Subtitle position %d px"), newval.i_int);

    else if (strcmp(var, "secondary-sub-margin") == 0)
        vouts_osd_Message(&vout, 1, _("Secondary subtitle position %d px"), newval.i_int);

    else if (strcmp(var, "sub-text-scale") == 0)
        vouts_osd_Message(&vout, 1, _("Subtitle text scale %d%%"), newval.i_int);

    else if (strcmp(var, "zoom") == 0)
    {
        if (newval.f_float == 1.f)
            vouts_osd_Message(&vout, 1, _("Zooming reset"));
        else
        {
            bool found =  vout_osd_PrintVariableText(vout, var, VLC_VAR_FLOAT,
                                                     newval, _("Zoom mode: %s"));
            if (!found)
                vouts_osd_Message(&vout, 1, _("Zoom: x%f"), newval.f_float);
        }
    }

    (void) data;
    return VLC_SUCCESS;
}