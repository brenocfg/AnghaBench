#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_3__* sys; } ;
typedef  TYPE_2__ vout_display_t ;
struct TYPE_15__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_3__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  drmModeRes ;
struct TYPE_16__ {scalar_t__ connection; scalar_t__ count_modes; int /*<<< orphan*/  connector_id; TYPE_1__* modes; } ;
typedef  TYPE_4__ drmModeConnector ;
typedef  scalar_t__ deviceRval ;
struct TYPE_13__ {int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  hdisplay; } ;

/* Variables and functions */
 scalar_t__ CreateFB (TYPE_2__*,int) ; 
 scalar_t__ DRM_MODE_CONNECTED ; 
 int /*<<< orphan*/  DestroyFB (TYPE_3__*,int) ; 
 scalar_t__ FindCRTC (TYPE_2__*,int /*<<< orphan*/  const*,TYPE_4__ const*) ; 
 int MAXHWBUF ; 
 scalar_t__ drvSuccess ; 
 scalar_t__ drvTryNext ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*,int,...) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static deviceRval SetupDevice(vout_display_t *vd, drmModeRes const *res,
                             drmModeConnector const *conn)
{
    vout_display_sys_t *sys = vd->sys;
    deviceRval ret;
    int c, c2;

    if (conn->connection != DRM_MODE_CONNECTED || conn->count_modes == 0)
        return drvTryNext;

    sys->width = conn->modes[0].hdisplay;
    sys->height = conn->modes[0].vdisplay;
    msg_Dbg(vd, "Mode resolution for connector %u is %ux%u",
            conn->connector_id, sys->width, sys->height);

    ret = FindCRTC(vd, res, conn);
    if (ret != drvSuccess) {
        msg_Dbg(vd , "No valid CRTC for connector %d", conn->connector_id);
        return ret;
    }

    for (c = 0; c < MAXHWBUF; c++) {
        ret = CreateFB(vd, c);
        if (ret != drvSuccess) {
            msg_Err(vd, "Cannot create framebuffer %d for connector %d", c,
                    conn->connector_id);
            for (c2 = 0; c2 < c; c2++)
                DestroyFB(sys, c2);

            return ret;
        } else {
            msg_Dbg(vd, "Created HW framebuffer %d/%d", c+1, MAXHWBUF);
        }
    }
    return drvSuccess;
}