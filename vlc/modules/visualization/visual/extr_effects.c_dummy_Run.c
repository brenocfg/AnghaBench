#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  const vlc_object_t ;
typedef  int /*<<< orphan*/  const visual_effect_t ;
typedef  int /*<<< orphan*/  const picture_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int dummy_Run( visual_effect_t * p_effect, vlc_object_t *p_aout,
                      const block_t * p_buffer , picture_t * p_picture)
{
    VLC_UNUSED(p_effect); VLC_UNUSED(p_aout); VLC_UNUSED(p_buffer);
    VLC_UNUSED(p_picture);
    return 0;
}