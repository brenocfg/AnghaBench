#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * device_select; int /*<<< orphan*/ * mute_set; int /*<<< orphan*/ * volume_set; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_12__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  module; } ;
typedef  TYPE_2__ aout_owner_t ;

/* Variables and functions */
 int /*<<< orphan*/  FilterCallback ; 
 int /*<<< orphan*/  StereoModeCallback ; 
 int /*<<< orphan*/  ViewpointCallback ; 
 int /*<<< orphan*/  aout_Release (TYPE_1__*) ; 
 TYPE_2__* aout_owner (TYPE_1__*) ; 
 int /*<<< orphan*/  module_unneed (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_Copy ; 
 int /*<<< orphan*/  var_CopyDevice ; 
 int /*<<< orphan*/  var_DelCallback (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  var_SetFloat (TYPE_1__*,char*,float) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_object_parent (TYPE_1__*) ; 

void aout_Destroy (audio_output_t *aout)
{
    aout_owner_t *owner = aout_owner (aout);

    vlc_mutex_lock(&owner->lock);
    module_unneed (aout, owner->module);
    /* Protect against late call from intf.c */
    aout->volume_set = NULL;
    aout->mute_set = NULL;
    aout->device_select = NULL;
    vlc_mutex_unlock(&owner->lock);

    var_DelCallback (aout, "viewpoint", ViewpointCallback, NULL);
    var_DelCallback (aout, "audio-filter", FilterCallback, NULL);
    var_DelCallback(aout, "device", var_CopyDevice, vlc_object_parent(aout));
    var_DelCallback(aout, "mute", var_Copy, vlc_object_parent(aout));
    var_SetFloat (aout, "volume", -1.f);
    var_DelCallback(aout, "volume", var_Copy, vlc_object_parent(aout));
    var_DelCallback (aout, "stereo-mode", StereoModeCallback, NULL);
    aout_Release(aout);
}