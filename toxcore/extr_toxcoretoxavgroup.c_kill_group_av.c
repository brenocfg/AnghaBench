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
struct TYPE_4__ {scalar_t__ audio_encoder; } ;
typedef  TYPE_1__ Group_AV ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  opus_encoder_destroy (scalar_t__) ; 

__attribute__((used)) static void kill_group_av(Group_AV *group_av)
{
    if (group_av->audio_encoder) {
        opus_encoder_destroy(group_av->audio_encoder);
    }

    free(group_av);
}