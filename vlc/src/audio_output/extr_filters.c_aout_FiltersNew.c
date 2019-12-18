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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  audio_sample_format_t ;
typedef  int /*<<< orphan*/  aout_filters_t ;
typedef  int /*<<< orphan*/  aout_filters_cfg_t ;

/* Variables and functions */
 int /*<<< orphan*/ * aout_FiltersNewWithClock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

aout_filters_t *aout_FiltersNew(vlc_object_t *obj,
                                const audio_sample_format_t *restrict infmt,
                                const audio_sample_format_t *restrict outfmt,
                                const aout_filters_cfg_t *cfg)
{
    return aout_FiltersNewWithClock(obj, NULL, infmt, outfmt, cfg);
}