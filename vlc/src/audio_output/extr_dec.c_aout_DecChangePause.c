#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* flush ) (TYPE_2__*) ;int /*<<< orphan*/  (* pause ) (TYPE_2__*,int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ audio_output_t ;
struct TYPE_9__ {scalar_t__ i_format; } ;
struct TYPE_11__ {TYPE_1__ mixer_format; } ;
typedef  TYPE_3__ aout_owner_t ;

/* Variables and functions */
 TYPE_3__* aout_owner (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

void aout_DecChangePause (audio_output_t *aout, bool paused, vlc_tick_t date)
{
    aout_owner_t *owner = aout_owner (aout);

    if (owner->mixer_format.i_format)
    {
        if (aout->pause != NULL)
            aout->pause(aout, paused, date);
        else if (paused)
            aout->flush(aout);
    }
}