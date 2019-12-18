#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ i_bitspersample; scalar_t__ i_rate; scalar_t__ i_channels; } ;
struct TYPE_6__ {TYPE_1__ audio; } ;
typedef  TYPE_2__ es_format_t ;

/* Variables and functions */

__attribute__((used)) static int fmtcmp( es_format_t *ofmt, es_format_t *nfmt )
{
    return (ofmt->audio.i_bitspersample != nfmt->audio.i_bitspersample)
        || (ofmt->audio.i_rate != nfmt->audio.i_rate)
        || (ofmt->audio.i_channels != nfmt->audio.i_channels);
}