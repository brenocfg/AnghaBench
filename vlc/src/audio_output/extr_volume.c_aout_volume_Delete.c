#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  audio_volume_t ;
struct TYPE_4__ {int /*<<< orphan*/ * module; int /*<<< orphan*/  object; } ;
typedef  TYPE_1__ aout_volume_t ;

/* Variables and functions */
 int /*<<< orphan*/  ReplayGainCallback ; 
 int /*<<< orphan*/  module_unneed (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  var_DelCallback (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_object_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_parent (int /*<<< orphan*/ *) ; 

void aout_volume_Delete(aout_volume_t *vol)
{
    if (vol == NULL)
        return;

    audio_volume_t *obj = &vol->object;

    if (vol->module != NULL)
        module_unneed(obj, vol->module);
    var_DelCallback(vlc_object_parent(obj), "audio-replay-gain-mode",
                    ReplayGainCallback, vol);
    vlc_object_delete(obj);
}