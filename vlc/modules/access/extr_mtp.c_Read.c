#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* p_sys; } ;
typedef  TYPE_1__ stream_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
#define  EAGAIN 129 
#define  EINTR 128 
 int /*<<< orphan*/  _ (char*) ; 
 int errno ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int,void*,size_t) ; 
 int /*<<< orphan*/  vlc_dialog_display_error (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_strerror (int) ; 
 int /*<<< orphan*/  vlc_strerror_c (int) ; 

__attribute__((used)) static ssize_t Read( stream_t *p_access, void *p_buffer, size_t i_len )
{
    int *fdp = p_access->p_sys, fd = *fdp;
    ssize_t i_ret = read( fd, p_buffer, i_len );

    if( i_ret < 0 )
    {
        switch( errno )
        {
            case EINTR:
            case EAGAIN:
                break;

            default:
                msg_Err( p_access, "read failed: %s", vlc_strerror_c(errno) );
                vlc_dialog_display_error( p_access, _( "File reading failed" ),
                    _( "VLC could not read the file: %s" ),
                    vlc_strerror(errno) );
                return 0;
        }
    }

    return i_ret;
}