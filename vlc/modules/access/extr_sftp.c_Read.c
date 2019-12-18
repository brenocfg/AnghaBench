#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
typedef  scalar_t__ ssize_t ;
struct TYPE_6__ {int /*<<< orphan*/  file; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 scalar_t__ libssh2_sftp_read (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 

__attribute__((used)) static ssize_t Read( stream_t *p_access, void *buf, size_t len )
{
    access_sys_t *p_sys = p_access->p_sys;

    ssize_t val = libssh2_sftp_read(  p_sys->file, buf, len );
    if( val < 0 )
    {
        msg_Err( p_access, "read failed" );
        return 0;
    }

    return val;
}