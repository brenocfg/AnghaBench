#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vt_mode {void* acqsig; void* relsig; int /*<<< orphan*/  mode; } ;
struct TYPE_7__ {int vtnr; TYPE_1__* user; } ;
struct TYPE_6__ {int /*<<< orphan*/  uid; } ;
typedef  TYPE_2__ Session ;

/* Variables and functions */
 int /*<<< orphan*/  KDSETMODE ; 
 int /*<<< orphan*/  KDSKBMODE ; 
 struct vt_mode* KD_GRAPHICS ; 
 struct vt_mode* K_OFF ; 
 void* SIGRTMIN ; 
 int /*<<< orphan*/  VT_PROCESS ; 
 int /*<<< orphan*/  VT_SETMODE ; 
 int /*<<< orphan*/  errno ; 
 int fchown (int,int /*<<< orphan*/ ,int) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct vt_mode*) ; 
 int log_error_errno (int /*<<< orphan*/ ,char*,int) ; 
 int session_open_vt (TYPE_2__*) ; 
 int /*<<< orphan*/  session_restore_vt (TYPE_2__*) ; 

__attribute__((used)) static int session_prepare_vt(Session *s) {
        int vt, r;
        struct vt_mode mode = {};

        if (s->vtnr < 1)
                return 0;

        vt = session_open_vt(s);
        if (vt < 0)
                return vt;

        r = fchown(vt, s->user->uid, -1);
        if (r < 0) {
                r = log_error_errno(errno,
                                    "Cannot change owner of /dev/tty%u: %m",
                                    s->vtnr);
                goto error;
        }

        r = ioctl(vt, KDSKBMODE, K_OFF);
        if (r < 0) {
                r = log_error_errno(errno,
                                    "Cannot set K_OFF on /dev/tty%u: %m",
                                    s->vtnr);
                goto error;
        }

        r = ioctl(vt, KDSETMODE, KD_GRAPHICS);
        if (r < 0) {
                r = log_error_errno(errno,
                                    "Cannot set KD_GRAPHICS on /dev/tty%u: %m",
                                    s->vtnr);
                goto error;
        }

        /* Oh, thanks to the VT layer, VT_AUTO does not work with KD_GRAPHICS.
         * So we need a dummy handler here which just acknowledges *all* VT
         * switch requests. */
        mode.mode = VT_PROCESS;
        mode.relsig = SIGRTMIN;
        mode.acqsig = SIGRTMIN + 1;
        r = ioctl(vt, VT_SETMODE, &mode);
        if (r < 0) {
                r = log_error_errno(errno,
                                    "Cannot set VT_PROCESS on /dev/tty%u: %m",
                                    s->vtnr);
                goto error;
        }

        return 0;

error:
        session_restore_vt(s);
        return r;
}