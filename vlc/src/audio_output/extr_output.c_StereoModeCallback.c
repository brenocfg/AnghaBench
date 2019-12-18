#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  i_int; } ;
typedef  TYPE_1__ vlc_value_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  audio_output_t ;
struct TYPE_7__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  requested_stereo_mode; } ;
typedef  TYPE_2__ aout_owner_t ;

/* Variables and functions */
 int /*<<< orphan*/  AOUT_RESTART_STEREOMODE ; 
 int /*<<< orphan*/  aout_RestartRequest (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* aout_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int StereoModeCallback (vlc_object_t *obj, const char *varname,
                               vlc_value_t oldval, vlc_value_t newval, void *data)
{
    audio_output_t *aout = (audio_output_t *)obj;
    (void)varname; (void)oldval; (void)newval; (void)data;

    aout_owner_t *owner = aout_owner (aout);
    vlc_mutex_lock (&owner->lock);
    owner->requested_stereo_mode = newval.i_int;
    vlc_mutex_unlock (&owner->lock);

    aout_RestartRequest (aout, AOUT_RESTART_STEREOMODE);
    return 0;
}