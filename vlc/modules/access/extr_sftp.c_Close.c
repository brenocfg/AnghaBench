#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_5__ {int /*<<< orphan*/  psz_base_url; scalar_t__ sftp_session; scalar_t__ file; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  SSHSessionDestroy (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libssh2_sftp_close_handle (scalar_t__) ; 
 int /*<<< orphan*/  libssh2_sftp_shutdown (scalar_t__) ; 

__attribute__((used)) static void Close( vlc_object_t* p_this )
{
    stream_t*   p_access = (stream_t*)p_this;
    access_sys_t* p_sys = p_access->p_sys;

    if( p_sys->file )
        libssh2_sftp_close_handle( p_sys->file );
    if( p_sys->sftp_session )
        libssh2_sftp_shutdown( p_sys->sftp_session );
    SSHSessionDestroy( p_access );

    free( p_sys->psz_base_url );
}