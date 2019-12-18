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
typedef  TYPE_1__ filter_t ;
struct TYPE_5__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  vttransfer; } ;
typedef  TYPE_2__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVPixelBufferPoolRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VTPixelTransferSessionInvalidate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static void
Close_CVPX_to_CVPX(vlc_object_t *obj)
{
    filter_t *filter = (filter_t *)obj;
    filter_sys_t *p_sys = filter->p_sys;

    VTPixelTransferSessionInvalidate(p_sys->vttransfer);
    CFRelease(p_sys->vttransfer);
    CVPixelBufferPoolRelease(p_sys->pool);
    free(filter->p_sys);
}