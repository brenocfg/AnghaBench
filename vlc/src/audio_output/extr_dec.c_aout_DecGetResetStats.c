#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  audio_output_t ;
struct TYPE_3__ {int /*<<< orphan*/  buffers_played; int /*<<< orphan*/  buffers_lost; } ;
typedef  TYPE_1__ aout_owner_t ;

/* Variables and functions */
 TYPE_1__* aout_owner (int /*<<< orphan*/ *) ; 
 unsigned int atomic_exchange_explicit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_order_relaxed ; 

void aout_DecGetResetStats(audio_output_t *aout, unsigned *restrict lost,
                           unsigned *restrict played)
{
    aout_owner_t *owner = aout_owner (aout);

    *lost = atomic_exchange_explicit(&owner->buffers_lost, 0,
                                     memory_order_relaxed);
    *played = atomic_exchange_explicit(&owner->buffers_played, 0,
                                       memory_order_relaxed);
}