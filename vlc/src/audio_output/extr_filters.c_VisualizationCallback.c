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
struct TYPE_4__ {char* psz_string; } ;
typedef  TYPE_1__ vlc_value_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  audio_output_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_VAR_STRING ; 
 int /*<<< orphan*/  aout_InputRequestRestart (int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  var_Create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_SetString (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static int VisualizationCallback (vlc_object_t *obj, const char *var,
                                  vlc_value_t oldval, vlc_value_t newval,
                                  void *data)
{
    const char *mode = newval.psz_string;

    if (!*mode)
        mode = "none";
    /* FIXME: This ugly hack enforced by visual effect-list, as is the need for
     * separate "visual" (external) and "audio-visual" (internal) variables...
     * The visual plugin should have one submodule per effect instead. */
    if (strcasecmp (mode, "none") && strcasecmp (mode, "goom")
     && strcasecmp (mode, "projectm") && strcasecmp (mode, "vsxu")
     && strcasecmp (mode, "glspectrum"))
    {
        var_Create (obj, "effect-list", VLC_VAR_STRING);
        var_SetString (obj, "effect-list", mode);
        mode = "visual";
    }

    var_SetString (obj, "audio-visual", mode);
    aout_InputRequestRestart ((audio_output_t *)obj);
    (void) var; (void) oldval; (void) data;
    return VLC_SUCCESS;
}