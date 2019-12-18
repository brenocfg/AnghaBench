#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct pollfd {int fd; scalar_t__ revents; void* events; } ;
typedef  int nfds_t ;
struct TYPE_9__ {int /*<<< orphan*/  out; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_10__ {int fd; int /*<<< orphan*/ * vbi; int /*<<< orphan*/  es; int /*<<< orphan*/  block_flags; int /*<<< orphan*/  bufv; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_11__ {int /*<<< orphan*/  i_pts; int /*<<< orphan*/  i_flags; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int GetFdVBI (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GrabVBI (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* GrabVideo (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* POLLIN ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_1__*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  es_out_SetPCR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 
 int /*<<< orphan*/  vlc_strerror_c (scalar_t__) ; 

__attribute__((used)) static void *MmapThread (void *data)
{
    demux_t *demux = data;
    demux_sys_t *sys = demux->p_sys;
    int fd = sys->fd;
    struct pollfd ufd[2];
    nfds_t numfds = 1;

    ufd[0].fd = fd;
    ufd[0].events = POLLIN;

#ifdef ZVBI_COMPILED
    if (sys->vbi != NULL)
    {
        ufd[1].fd = GetFdVBI (sys->vbi);
        ufd[1].events = POLLIN;
        numfds++;
    }
#endif

    for (;;)
    {
        /* Wait for data */
        if (poll (ufd, numfds, -1) == -1)
        {
           if (errno != EINTR)
               msg_Err (demux, "poll error: %s", vlc_strerror_c(errno));
           continue;
        }

        if( ufd[0].revents )
        {
            int canc = vlc_savecancel ();
            block_t *block = GrabVideo (VLC_OBJECT(demux), fd, sys->bufv);
            if (block != NULL)
            {
                block->i_flags |= sys->block_flags;
                es_out_SetPCR(demux->out, block->i_pts);
                es_out_Send (demux->out, sys->es, block);
            }
            vlc_restorecancel (canc);
        }
#ifdef ZVBI_COMPILED
        if (sys->vbi != NULL && ufd[1].revents)
            GrabVBI (demux, sys->vbi);
#endif
    }

    vlc_assert_unreachable ();
}