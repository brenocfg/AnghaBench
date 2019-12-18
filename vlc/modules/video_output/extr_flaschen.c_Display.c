#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* sys; } ;
typedef  TYPE_2__ vout_display_t ;
struct TYPE_11__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_3__ vout_display_sys_t ;
struct TYPE_12__ {int i_width; int i_height; } ;
typedef  TYPE_4__ video_format_t ;
typedef  char uint8_t ;
struct msghdr {int msg_iovlen; int /*<<< orphan*/  msg_flags; int /*<<< orphan*/  msg_controllen; int /*<<< orphan*/ * msg_control; struct iovec* msg_iov; int /*<<< orphan*/  msg_namelen; int /*<<< orphan*/ * msg_name; } ;
struct iovec {char* iov_base; int iov_len; } ;
struct TYPE_13__ {TYPE_1__* p; TYPE_4__ format; } ;
typedef  TYPE_5__ picture_t ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_9__ {char* p_pixels; int /*<<< orphan*/  i_pitch; } ;

/* Variables and functions */
 long IOV_MAX ; 
 int /*<<< orphan*/  _SC_IOV_MAX ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*,int) ; 
 int sendmsg (int /*<<< orphan*/ ,struct msghdr*,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,int,int) ; 
 long sysconf (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int vlc_strerror_c (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Display(vout_display_t *vd, picture_t *picture)
{
#ifdef IOV_MAX
    const long iovmax = IOV_MAX;
#else
    const long iovmax = sysconf(_SC_IOV_MAX);
#endif
    vout_display_sys_t *sys = vd->sys;
    video_format_t *fmt = &picture->format;
    int result;

    char buffer[64];
    int header_len = snprintf(buffer, sizeof(buffer), "P6\n%d %d\n255\n",
                              fmt->i_width, fmt->i_height);
    /* TODO: support offset_{x,y,z}? (#FT:...) */
    /* Note the protocol doesn't include any picture order field. */
    /* (maybe add as comment?) */

    int iovcnt = 1 + fmt->i_height;
    if (unlikely(iovcnt > iovmax))
        return;

    struct iovec iov[iovcnt];
    iov[0].iov_base = buffer;
    iov[0].iov_len = header_len;

    uint8_t *src = picture->p->p_pixels;
    for (int i = 1; i < iovcnt; i++)
    {
        iov[i].iov_base = src;
        iov[i].iov_len = fmt->i_width * 3;
        src += picture->p->i_pitch;
    }

    struct msghdr hdr = {
        .msg_name = NULL,
        .msg_namelen = 0,
        .msg_iov = iov,
        .msg_iovlen = iovcnt,
        .msg_control = NULL,
        .msg_controllen = 0,
        .msg_flags = 0 };

    result = sendmsg(sys->fd, &hdr, 0);
    if (result < 0)
        msg_Err(vd, "sendmsg: error %s in vout display flaschen", vlc_strerror_c(errno));
    else if (result < (int)(header_len + fmt->i_width * fmt->i_height * 3))
        msg_Err(vd, "sendmsg only sent %d bytes in vout display flaschen", result);
        /* we might want to drop some frames? */
}