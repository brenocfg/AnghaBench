#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int (* volume_set ) (TYPE_1__*,float) ;} ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ aout_owner_t ;

/* Variables and functions */
 TYPE_2__* aout_owner (TYPE_1__*) ; 
 int stub1 (TYPE_1__*,float) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

int aout_VolumeSet (audio_output_t *aout, float vol)
{
    aout_owner_t *owner = aout_owner(aout);
    int ret;

    vlc_mutex_lock(&owner->lock);
    ret = aout->volume_set(aout, vol);
    vlc_mutex_unlock(&owner->lock);
    return ret ? -1 : 0;
}