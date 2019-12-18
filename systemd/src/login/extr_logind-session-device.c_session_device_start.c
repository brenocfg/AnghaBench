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
struct TYPE_6__ {int active; int type; int fd; int /*<<< orphan*/  session; } ;
typedef  TYPE_1__ SessionDevice ;

/* Variables and functions */
#define  DEVICE_TYPE_DRM 130 
#define  DEVICE_TYPE_EVDEV 129 
#define  DEVICE_TYPE_UNKNOWN 128 
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int log_error_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  safe_close (int) ; 
 int sd_drmsetmaster (int) ; 
 int session_device_open (TYPE_1__*,int) ; 
 TYPE_1__* session_is_active (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int session_device_start(SessionDevice *sd) {
        int r;

        assert(sd);
        assert(session_is_active(sd->session));

        if (sd->active)
                return 0;

        switch (sd->type) {

        case DEVICE_TYPE_DRM:
                if (sd->fd < 0)
                        return log_error_errno(SYNTHETIC_ERRNO(EBADF),
                                               "Failed to re-activate DRM fd, as the fd was lost (maybe logind restart went wrong?)");

                /* Device is kept open. Simply call drmSetMaster() and hope there is no-one else. In case it fails, we
                 * keep the device paused. Maybe at some point we have a drmStealMaster(). */
                r = sd_drmsetmaster(sd->fd);
                if (r < 0)
                        return r;
                break;

        case DEVICE_TYPE_EVDEV:
                /* Evdev devices are revoked while inactive. Reopen it and we are fine. */
                r = session_device_open(sd, true);
                if (r < 0)
                        return r;

                /* For evdev devices, the file descriptor might be left uninitialized. This might happen while resuming
                 * into a session and logind has been restarted right before. */
                safe_close(sd->fd);
                sd->fd = r;
                break;

        case DEVICE_TYPE_UNKNOWN:
        default:
                /* fallback for devices without synchronizations */
                break;
        }

        sd->active = true;
        return 0;
}