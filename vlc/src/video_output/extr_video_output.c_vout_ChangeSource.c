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
struct TYPE_4__ {TYPE_2__* p; } ;
typedef  TYPE_1__ vout_thread_t ;
struct TYPE_5__ {int /*<<< orphan*/  original; } ;
typedef  TYPE_2__ vout_thread_sys_t ;
typedef  int /*<<< orphan*/  video_format_t ;

/* Variables and functions */
 scalar_t__ video_format_IsSimilar (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int vout_ChangeSource( vout_thread_t *vout, const video_format_t *original )
{
    vout_thread_sys_t *sys = vout->p;

     /* TODO: If dimensions are equal or slightly smaller, update the aspect
     * ratio and crop settings, instead of recreating a display.
     */
    if (video_format_IsSimilar(original, &sys->original)) {
        /* It is assumed that the SPU input matches input already. */
        return 0;
    }

    return -1;
}