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
typedef  void* uint8_t ;
struct iovec {void** iov_base; int iov_len; } ;
struct TYPE_3__ {int /*<<< orphan*/  obj; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ cam_t ;

/* Variables and functions */
 int /*<<< orphan*/  Dump (int,void**,int) ; 
 void** SetLength (void**,size_t) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 
 scalar_t__ writev (int /*<<< orphan*/ ,struct iovec const*,int) ; 

__attribute__((used)) static int TPDUSend( cam_t * p_cam, uint8_t i_slot, uint8_t i_tag,
                     const uint8_t *p_content, size_t i_length )
{
    uint8_t p_data[9], *p = p_data;

    *(p++) = i_slot;
    *(p++) = i_slot + 1; /* TCID */
    *(p++) = i_tag;
    p = SetLength( p, i_length + 1 );

    *(p++) = i_slot + 1;
    Dump( true, p_data, p - p_data );

    const struct iovec iov[2] = {
        { .iov_base = p_data, .iov_len = p - p_data },
        { .iov_base = (void *)p_content, .iov_len = i_length },
    };

    if ( writev( p_cam->fd, iov, 2 ) <= 0 )
    {
        msg_Err( p_cam->obj, "cannot write to CAM device: %s",
                 vlc_strerror_c(errno) );
        return VLC_EGENERIC;
    }
    return VLC_SUCCESS;
}