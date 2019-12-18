#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
typedef  scalar_t__ ssize_t ;
struct TYPE_11__ {int fd; int i_current_file; int /*<<< orphan*/  offset; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int FILE_COUNT ; 
 int /*<<< orphan*/  FindSeekpoint (TYPE_1__*) ; 
 int /*<<< orphan*/  ImportNextFile (TYPE_1__*) ; 
 int /*<<< orphan*/  SwitchFile (TYPE_1__*,int) ; 
 int /*<<< orphan*/  UpdateFileSize (TYPE_1__*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int,void*,size_t) ; 
 int /*<<< orphan*/  vlc_dialog_display_error (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_strerror (scalar_t__) ; 
 int /*<<< orphan*/  vlc_strerror_c (scalar_t__) ; 

__attribute__((used)) static ssize_t Read( stream_t *p_access, void *p_buffer, size_t i_len )
{
    access_sys_t *p_sys = p_access->p_sys;

    if( p_sys->fd == -1 )
        /* no more data */
        return 0;

    ssize_t i_ret = read( p_sys->fd, p_buffer, i_len );

    if( i_ret > 0 )
    {
        /* success */
        p_sys->offset += i_ret;
        UpdateFileSize( p_access );
        FindSeekpoint( p_access );
        return i_ret;
    }
    else if( i_ret == 0 )
    {
        /* check for new files in case the recording is still active */
        if( p_sys->i_current_file >= FILE_COUNT - 1 )
            ImportNextFile( p_access );
        /* play next file */
        SwitchFile( p_access, p_sys->i_current_file + 1 );
        return -1;
    }
    else if( errno == EINTR )
    {
        /* try again later */
        return -1;
    }
    else
    {
        /* abort on read error */
        msg_Err( p_access, "failed to read (%s)", vlc_strerror_c(errno) );
        vlc_dialog_display_error( p_access, _("File reading failed"),
            _("VLC could not read the file (%s)."),
            vlc_strerror(errno) );
        SwitchFile( p_access, -1 );
        return 0;
    }
}