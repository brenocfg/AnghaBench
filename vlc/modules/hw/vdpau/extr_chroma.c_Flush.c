#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* history; } ;
typedef  TYPE_2__ vlc_vdp_mixer_t ;
struct TYPE_7__ {TYPE_2__* p_sys; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_5__ {int /*<<< orphan*/ * field; } ;

/* Variables and functions */
 unsigned int MAX_FUTURE ; 
 unsigned int MAX_PAST ; 
 int /*<<< orphan*/  vlc_vdp_video_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Flush(filter_t *filter)
{
    vlc_vdp_mixer_t *sys = filter->p_sys;

    for (unsigned i = 0; i < MAX_PAST + MAX_FUTURE; i++)
        if (sys->history[i].field != NULL)
        {
            vlc_vdp_video_destroy(sys->history[i].field);
            sys->history[i].field = NULL;
        }
}