#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  imem_sys_t ;
struct TYPE_2__ {scalar_t__ p_sys; } ;
typedef  TYPE_1__ demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  CloseCommon (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void CloseDemux(vlc_object_t *object)
{
    demux_t *demux = (demux_t *)object;

    CloseCommon((imem_sys_t*)demux->p_sys);
}