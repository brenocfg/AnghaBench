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
struct TYPE_4__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_5__ {int ready; int /*<<< orphan*/  lock; int /*<<< orphan*/  opaque; int /*<<< orphan*/  (* cleanup ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ aout_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Stop (audio_output_t *aout)
{
    aout_sys_t *sys = aout->sys;

    vlc_mutex_lock(&sys->lock);
    if (sys->cleanup != NULL)
        sys->cleanup (sys->opaque);

    sys->ready = false;
    vlc_mutex_unlock(&sys->lock);
}