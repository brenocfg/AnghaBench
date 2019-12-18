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
struct TYPE_5__ {int /*<<< orphan*/ * p_avc1394; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  raw1394_destroy_handle (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void AVCClose( stream_t *p_access )
{
    access_sys_t *p_sys = p_access->p_sys;

    if( p_sys->p_avc1394 )
    {
        raw1394_destroy_handle( p_sys->p_avc1394 );
        p_sys->p_avc1394 = NULL;
    }
}