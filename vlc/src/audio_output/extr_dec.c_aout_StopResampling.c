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
struct TYPE_4__ {int /*<<< orphan*/  resamp_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  filters; TYPE_1__ sync; } ;
typedef  TYPE_2__ aout_owner_t ;

/* Variables and functions */
 int /*<<< orphan*/  AOUT_RESAMPLING_NONE ; 
 int /*<<< orphan*/  aout_FiltersAdjustResampling (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* aout_owner (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void aout_StopResampling (audio_output_t *aout)
{
    aout_owner_t *owner = aout_owner (aout);

    owner->sync.resamp_type = AOUT_RESAMPLING_NONE;
    aout_FiltersAdjustResampling (owner->filters, 0);
}