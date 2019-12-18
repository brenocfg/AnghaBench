#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* p; } ;
typedef  TYPE_2__ vout_thread_t ;
typedef  void* vlc_value_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_9__ {int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int /*<<< orphan*/  DeinterlaceIsModeValid (char*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (void*) ; 
 int /*<<< orphan*/  VOUT_CONTROL_CHANGE_INTERLACE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*,int const,char*,int const) ; 
 char* var_CreateGetString (TYPE_2__*,char*) ; 
 int var_GetBool (TYPE_2__*,char*) ; 
 int var_GetInteger (TYPE_2__*,char*) ; 
 char* var_GetString (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  var_SetString (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  vout_control_PushBool (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int DeinterlaceCallback(vlc_object_t *object, char const *cmd,
                               vlc_value_t oldval, vlc_value_t newval, void *data)
{
    VLC_UNUSED(cmd); VLC_UNUSED(oldval); VLC_UNUSED(newval); VLC_UNUSED(data);
    vout_thread_t *vout = (vout_thread_t *)object;

    /* */
    const int  deinterlace_state = var_GetInteger(vout, "deinterlace");
    char       *mode             = var_GetString(vout,  "deinterlace-mode");
    const bool is_needed         = var_GetBool(vout,    "deinterlace-needed");
    if (!mode || !DeinterlaceIsModeValid(mode))
    {
        free(mode);
        return VLC_EGENERIC;
    }

    /* */
    char *old = var_CreateGetString(vout, "sout-deinterlace-mode");
    var_SetString(vout, "sout-deinterlace-mode", mode);

    msg_Dbg(vout, "deinterlace %d, mode %s, is_needed %d", deinterlace_state, mode, is_needed);
    if (deinterlace_state == 0 || (deinterlace_state < 0 && !is_needed))
        vout_control_PushBool(&vout->p->control,
                              VOUT_CONTROL_CHANGE_INTERLACE, false);
    else
        vout_control_PushBool(&vout->p->control,
                              VOUT_CONTROL_CHANGE_INTERLACE, true);

    /* */
    free(old);
    free(mode);
    return VLC_SUCCESS;
}