#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_display_t ;
struct TYPE_14__ {int drm_fd; scalar_t__ crtc; int /*<<< orphan*/  drm_fourcc; int /*<<< orphan*/  vlc_fourcc; } ;
typedef  TYPE_2__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_15__ {int count_connectors; int /*<<< orphan*/ * connectors; } ;
typedef  TYPE_3__ drmModeRes ;
typedef  int /*<<< orphan*/  drmModeConnector ;

/* Variables and functions */
 int /*<<< orphan*/  ChromaNegotiation (TYPE_1__*) ; 
 int /*<<< orphan*/  DRM_CAP_DUMB_BUFFER ; 
 int /*<<< orphan*/  DRM_CLIENT_CAP_UNIVERSAL_PLANES ; 
 int /*<<< orphan*/  KMS_VAR ; 
 int /*<<< orphan*/  O_RDWR ; 
 int SetupDevice (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  drmDropMaster (int) ; 
 int drmGetCap (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drmModeFreeConnector (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drmModeFreeResources (TYPE_3__*) ; 
 int /*<<< orphan*/ * drmModeGetConnector (int,int /*<<< orphan*/ ) ; 
 TYPE_3__* drmModeGetResources (int) ; 
 int /*<<< orphan*/  drmSetClientCap (int,int /*<<< orphan*/ ,int) ; 
 int drvSuccess ; 
 int drvTryNext ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,char*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,...) ; 
 char* var_InheritString (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_close (int) ; 
 int vlc_open (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int OpenDisplay(vout_display_t *vd)
{
    vout_display_sys_t *sys = vd->sys;
    char *psz_device;
    int ret;
    uint64_t dumbRet;
    drmModeConnector *conn;
    drmModeRes *modeRes;
    int c;
    bool found_connector = false;

    /*
     * Open framebuffer device
     */
    psz_device = var_InheritString(vd, KMS_VAR);
    if (psz_device == NULL) {
        msg_Err(vd, "Don't know which DRM device to open");
        return VLC_EGENERIC;
    }

    sys->drm_fd = vlc_open(psz_device, O_RDWR);
    if (sys->drm_fd == -1) {
        msg_Err(vd, "cannot open %s", psz_device);
        free(psz_device);
        return VLC_EGENERIC;
    }
    free(psz_device);

    drmSetClientCap(sys->drm_fd, DRM_CLIENT_CAP_UNIVERSAL_PLANES, 1);

    if (!ChromaNegotiation(vd))
        goto err_out;

    msg_Dbg(vd, "Using VLC chroma '%.4s', DRM chroma '%.4s'",
            (char*)&sys->vlc_fourcc, (char*)&sys->drm_fourcc);

    ret = drmGetCap(sys->drm_fd, DRM_CAP_DUMB_BUFFER, &dumbRet);
    if (ret < 0 || !dumbRet) {
        msg_Err(vd, "Device '%s' does not support dumb buffers", psz_device);
        goto err_out;
    }

    modeRes = drmModeGetResources(sys->drm_fd);
    if (modeRes == NULL) {
        msg_Err(vd, "Didn't get DRM resources");
        goto err_out;
    }

    for (c = 0; c < modeRes->count_connectors && sys->crtc == 0; c++) {

        conn = drmModeGetConnector(sys->drm_fd, modeRes->connectors[c]);
        if (conn == NULL)
            continue;

        found_connector = true;

        ret = SetupDevice(vd, modeRes, conn);
        if (ret != drvSuccess) {
            if (ret != drvTryNext) {
                msg_Err(vd, "Cannot do setup for connector %u:%u", c,
                        modeRes->connectors[c]);

                drmModeFreeConnector(conn);
                drmModeFreeResources(modeRes);
                goto err_out;
            }
            drmModeFreeConnector(conn);
            found_connector = false;
            continue;
        }
        drmModeFreeConnector(conn);
    }
    drmModeFreeResources(modeRes);

    if (!found_connector)
        goto err_out;

    return VLC_SUCCESS;
err_out:
    drmDropMaster(sys->drm_fd);
    vlc_close(sys->drm_fd);
    sys->drm_fd = 0;
    return VLC_EGENERIC;
}