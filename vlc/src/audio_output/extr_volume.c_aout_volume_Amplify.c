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
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* amplify ) (TYPE_2__*,int /*<<< orphan*/ *,float) ;} ;
struct TYPE_4__ {float output_factor; TYPE_2__ object; int /*<<< orphan*/  gain_factor; int /*<<< orphan*/ * module; } ;
typedef  TYPE_1__ aout_volume_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *,float) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 float vlc_atomic_load_float (int /*<<< orphan*/ *) ; 

int aout_volume_Amplify(aout_volume_t *vol, block_t *block)
{
    if (unlikely(vol == NULL) || vol->module == NULL)
        return -1;

    float amp = vol->output_factor
              * vlc_atomic_load_float (&vol->gain_factor);

    vol->object.amplify(&vol->object, block, amp);
    return 0;
}