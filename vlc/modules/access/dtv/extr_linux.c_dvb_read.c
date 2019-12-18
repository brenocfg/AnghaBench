#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pollfd {int fd; scalar_t__ revents; int /*<<< orphan*/  events; } ;
struct dvb_frontend_event {int /*<<< orphan*/  status; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int demux; int frontend; int /*<<< orphan*/  obj; int /*<<< orphan*/ * cam; } ;
typedef  TYPE_1__ dvb_device_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EOVERFLOW ; 
 int /*<<< orphan*/  FE_GET_EVENT ; 
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  POLLPRI ; 
 int /*<<< orphan*/  dvb_frontend_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  en50221_Poll (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct dvb_frontend_event*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*,...) ; 
 int read (int,void*,size_t) ; 
 int vlc_poll_i11e (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  vlc_strerror_c (scalar_t__) ; 

ssize_t dvb_read (dvb_device_t *d, void *buf, size_t len, int ms)
{
    struct pollfd ufd[2];
    int n;

    if (d->cam != NULL)
        en50221_Poll (d->cam);

    ufd[0].fd = d->demux;
    ufd[0].events = POLLIN;
    if (d->frontend != -1)
    {
        ufd[1].fd = d->frontend;
        ufd[1].events = POLLPRI;
        n = 2;
    }
    else
        n = 1;

    errno = 0;
    n = vlc_poll_i11e (ufd, n, ms);
    if (n == 0)
        errno = EAGAIN;
    if (n <= 0)
        return -1;

    if (d->frontend != -1 && ufd[1].revents)
    {
        struct dvb_frontend_event ev;

        if (ioctl (d->frontend, FE_GET_EVENT, &ev) < 0)
        {
            if (errno == EOVERFLOW)
            {
                msg_Err (d->obj, "cannot dequeue events fast enough!");
                return -1;
            }
            msg_Err (d->obj, "cannot dequeue frontend event: %s",
                     vlc_strerror_c(errno));
            return 0;
        }

        dvb_frontend_status(d->obj, ev.status);
    }

    if (ufd[0].revents)
    {
        ssize_t val = read (d->demux, buf, len);
        if (val == -1 && (errno != EAGAIN && errno != EINTR))
        {
            if (errno == EOVERFLOW)
            {
                msg_Err (d->obj, "cannot demux data fast enough!");
                return -1;
            }
            msg_Err (d->obj, "cannot demux: %s", vlc_strerror_c(errno));
            return 0;
        }
        return val;
    }

    return -1;
}