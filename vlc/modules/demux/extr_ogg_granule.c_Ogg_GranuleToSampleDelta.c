#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  b_old; } ;
struct TYPE_8__ {TYPE_2__ dirac; } ;
struct TYPE_6__ {scalar_t__ i_codec; } ;
struct TYPE_9__ {TYPE_3__ special; TYPE_1__ fmt; } ;
typedef  TYPE_4__ logical_stream_t ;
typedef  int int64_t ;

/* Variables and functions */
 scalar_t__ VLC_CODEC_DIRAC ; 

__attribute__((used)) static int64_t Ogg_GranuleToSampleDelta( const logical_stream_t *p_stream, int64_t i_granule )
{
    if( p_stream->fmt.i_codec == VLC_CODEC_DIRAC && !p_stream->special.dirac.b_old )
        return (i_granule >> 9) & 0x1fff;
    else
        return -1;
}