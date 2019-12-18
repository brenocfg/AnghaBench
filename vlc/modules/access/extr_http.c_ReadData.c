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
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_5__ {int /*<<< orphan*/  stream; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ errno ; 
 int vlc_tls_Read (int /*<<< orphan*/ ,void*,size_t,int) ; 

__attribute__((used)) static int ReadData( stream_t *p_access, int *pi_read,
                     void *p_buffer, size_t i_len )
{
    access_sys_t *p_sys = p_access->p_sys;

    *pi_read = vlc_tls_Read(p_sys->stream, p_buffer, i_len, false);
    if( *pi_read < 0 && errno != EINTR && errno != EAGAIN )
        return VLC_EGENERIC;
    return VLC_SUCCESS;
}