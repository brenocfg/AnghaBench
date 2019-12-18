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
struct TYPE_4__ {scalar_t__ i_rate; scalar_t__ i_physical_channels; } ;
typedef  TYPE_1__ audio_format_t ;

/* Variables and functions */

__attribute__((used)) static bool transcode_audio_format_IsSimilar( const audio_format_t *a,
                                              const audio_format_t *b )
{
    return
    a->i_rate == b->i_rate &&
    a->i_physical_channels == b->i_physical_channels;
}