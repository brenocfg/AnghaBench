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
struct TYPE_5__ {struct TYPE_5__* psz_fullpath; int /*<<< orphan*/  url; scalar_t__ p_session; scalar_t__ i_fd; scalar_t__ p_ns; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  netbios_ns_destroy (scalar_t__) ; 
 int /*<<< orphan*/  smb_fclose (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  smb_session_destroy (scalar_t__) ; 
 int /*<<< orphan*/  vlc_UrlClean (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Close( vlc_object_t *p_this )
{
    stream_t     *p_access = (stream_t*)p_this;
    access_sys_t *p_sys = p_access->p_sys;

    if( p_sys->p_ns )
        netbios_ns_destroy( p_sys->p_ns );
    if( p_sys->i_fd )
        smb_fclose( p_sys->p_session, p_sys->i_fd );
    if( p_sys->p_session )
        smb_session_destroy( p_sys->p_session );
    vlc_UrlClean( &p_sys->url );
    free( p_sys->psz_fullpath );

    free( p_sys );
}