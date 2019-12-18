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
typedef  int /*<<< orphan*/  audio_output_t ;
struct TYPE_4__ {scalar_t__ i_format; } ;
struct TYPE_5__ {int /*<<< orphan*/ * volume; int /*<<< orphan*/  filters; TYPE_1__ mixer_format; } ;
typedef  TYPE_2__ aout_owner_t ;

/* Variables and functions */
 int /*<<< orphan*/  aout_DecFlush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aout_FiltersDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aout_OutputDelete (int /*<<< orphan*/ *) ; 
 TYPE_2__* aout_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aout_volume_Delete (int /*<<< orphan*/ *) ; 

void aout_DecDelete (audio_output_t *aout)
{
    aout_owner_t *owner = aout_owner (aout);

    if (owner->mixer_format.i_format)
    {
        aout_DecFlush(aout);
        aout_FiltersDelete (aout, owner->filters);
        aout_OutputDelete (aout);
    }
    aout_volume_Delete (owner->volume);
    owner->volume = NULL;
}