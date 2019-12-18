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
typedef  int /*<<< orphan*/  vlc_decoder_device ;
typedef  int /*<<< orphan*/  filter_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * owner; int /*<<< orphan*/ * dec_device; } ;

/* Variables and functions */
 TYPE_1__ holder ; 
 int /*<<< orphan*/  vlc_decoder_device_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void
vlc_vaapi_FilterReleaseInstance(filter_t *filter,
                                vlc_decoder_device *dec_device)
{
    vlc_decoder_device_Release(dec_device);
    vlc_mutex_lock(&holder.lock);
    if (filter == holder.owner)
    {
        holder.dec_device = NULL;
        holder.owner = NULL;
    }
    vlc_mutex_unlock(&holder.lock);
}