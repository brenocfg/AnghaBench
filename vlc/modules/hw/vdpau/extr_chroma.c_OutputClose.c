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
struct TYPE_4__ {int /*<<< orphan*/  vdp; int /*<<< orphan*/  pool; int /*<<< orphan*/  mixer; } ;
typedef  TYPE_1__ vlc_vdp_mixer_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {TYPE_1__* p_sys; } ;
typedef  TYPE_2__ filter_t ;

/* Variables and functions */
 int /*<<< orphan*/  Flush (TYPE_2__*) ; 
 int /*<<< orphan*/  picture_pool_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdp_release_x11 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdp_video_mixer_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void OutputClose(vlc_object_t *obj)
{
    filter_t *filter = (filter_t *)obj;
    vlc_vdp_mixer_t *sys = filter->p_sys;

    Flush(filter);
    vdp_video_mixer_destroy(sys->vdp, sys->mixer);
    picture_pool_Release(sys->pool);
    vdp_release_x11(sys->vdp);
}