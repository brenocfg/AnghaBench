#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_10__ {int i; } ;
struct TYPE_11__ {TYPE_1__ value; } ;
struct TYPE_12__ {scalar_t__ type; int flags; TYPE_2__ value; } ;
typedef  TYPE_3__ VASurfaceAttrib ;
typedef  int /*<<< orphan*/  VAProfile ;
typedef  int /*<<< orphan*/  VAEntrypoint ;
typedef  int /*<<< orphan*/  VADisplay ;
typedef  scalar_t__ VAConfigID ;
struct TYPE_13__ {int value; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ VAConfigAttrib ;

/* Variables and functions */
 int /*<<< orphan*/  IsEntrypointAvailable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsVaProfileSupported (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VAConfigAttribRTFormat ; 
 scalar_t__ VASurfaceAttribPixelFormat ; 
 int /*<<< orphan*/  VA_CALL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int,scalar_t__*) ; 
 scalar_t__ VA_INVALID_ID ; 
 int VA_RT_FORMAT_YUV420 ; 
 int VA_RT_FORMAT_YUV420_10BPP ; 
 scalar_t__ VA_STATUS_SUCCESS ; 
 int VA_SURFACE_ATTRIB_SETTABLE ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  vaCreateConfig ; 
 scalar_t__ vaGetConfigAttributes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 scalar_t__ vaQuerySurfaceAttributes (int /*<<< orphan*/ ,scalar_t__,TYPE_3__*,unsigned int*) ; 
 TYPE_3__* vlc_alloc (unsigned int,int) ; 
 int /*<<< orphan*/  vlc_chroma_to_vaapi (int,unsigned int*,int*) ; 
 int /*<<< orphan*/  vlc_vaapi_DestroyConfig (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

VAConfigID
vlc_vaapi_CreateConfigChecked(vlc_object_t *o, VADisplay dpy,
                              VAProfile i_profile, VAEntrypoint entrypoint,
                              int i_force_vlc_chroma)
{
    int va_force_fourcc = 0;
    if (i_force_vlc_chroma != 0)
    {
        unsigned unused;
        vlc_chroma_to_vaapi(i_force_vlc_chroma, &unused, &va_force_fourcc);
    }

    if (!IsVaProfileSupported(dpy, i_profile))
    {
        msg_Err(o, "profile(%d) is not supported", i_profile);
        return VA_INVALID_ID;
    }
    if (!IsEntrypointAvailable(dpy, i_profile, entrypoint))
    {
        msg_Err(o, "entrypoint(%d) is not available", entrypoint);
        return VA_INVALID_ID;
    }

    /* Create a VA configuration */
    VAConfigAttrib attrib = {
        .type = VAConfigAttribRTFormat,
    };
    if (vaGetConfigAttributes(dpy, i_profile, entrypoint, &attrib, 1))
    {
        msg_Err(o, "vaGetConfigAttributes failed");
        return VA_INVALID_ID;
    }

    /* Not sure what to do if not, I don't have a way to test */
    if ((attrib.value & (VA_RT_FORMAT_YUV420|VA_RT_FORMAT_YUV420_10BPP)) == 0)
    {
        msg_Err(o, "config doesn't support VA_RT_FORMAT_YUV420*");
        return VA_INVALID_ID;
    }

    unsigned int num_sattribs;
    VASurfaceAttrib *sattribs = NULL;
    VAConfigID va_config_id = VA_INVALID_ID;
    VA_CALL(o, vaCreateConfig, dpy, i_profile, entrypoint, &attrib, 1,
            &va_config_id);

    if (va_force_fourcc == 0)
        return va_config_id;

    /* Fetch VASurfaceAttrib list to make sure the decoder can output NV12 */
    if (vaQuerySurfaceAttributes(dpy, va_config_id, NULL, &num_sattribs)
        != VA_STATUS_SUCCESS)
        goto error;

    sattribs = vlc_alloc(num_sattribs, sizeof(*sattribs));
    if (sattribs == NULL)
        goto error;
    if (vaQuerySurfaceAttributes(dpy, va_config_id, sattribs, &num_sattribs)
        != VA_STATUS_SUCCESS)
        goto error;

    for (unsigned i = 0; i < num_sattribs; ++i)
    {
        VASurfaceAttrib *sattrib = &sattribs[i];
        if (sattrib->type == VASurfaceAttribPixelFormat
         && sattrib->flags & VA_SURFACE_ATTRIB_SETTABLE
         && sattrib->value.value.i == va_force_fourcc)
        {
            free(sattribs);
            return va_config_id;
        }

    }

error:
    free(sattribs);
    if (va_config_id != VA_INVALID_ID)
    {
        msg_Err(o, "config doesn't support forced fourcc");
        vlc_vaapi_DestroyConfig(o, dpy, va_config_id);
    }
    return VA_INVALID_ID;
}