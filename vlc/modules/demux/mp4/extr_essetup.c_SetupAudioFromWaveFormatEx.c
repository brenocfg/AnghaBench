#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  i_bitspersample; int /*<<< orphan*/  i_blockalign; int /*<<< orphan*/  i_rate; int /*<<< orphan*/  i_channels; } ;
struct TYPE_8__ {int i_bitrate; scalar_t__ i_extra; int /*<<< orphan*/  p_extra; TYPE_1__ audio; int /*<<< orphan*/  i_codec; } ;
typedef  TYPE_3__ es_format_t ;
struct TYPE_7__ {int nAvgBytesPerSec; int /*<<< orphan*/  wBitsPerSample; int /*<<< orphan*/  nBlockAlign; int /*<<< orphan*/  nSamplesPerSec; int /*<<< orphan*/  nChannels; int /*<<< orphan*/  wFormatTag; } ;
struct TYPE_9__ {scalar_t__ i_extra; int /*<<< orphan*/  p_extra; TYPE_2__ Format; } ;
typedef  int /*<<< orphan*/  MP4_Box_t ;

/* Variables and functions */
 TYPE_5__* BOXDATA (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wf_tag_to_fourcc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool SetupAudioFromWaveFormatEx( es_format_t *p_fmt, const MP4_Box_t *p_WMA2 )
{
    if( p_WMA2 && BOXDATA(p_WMA2) )
    {
        wf_tag_to_fourcc(BOXDATA(p_WMA2)->Format.wFormatTag, &p_fmt->i_codec, NULL);
        p_fmt->audio.i_channels = BOXDATA(p_WMA2)->Format.nChannels;
        p_fmt->audio.i_rate = BOXDATA(p_WMA2)->Format.nSamplesPerSec;
        p_fmt->i_bitrate = BOXDATA(p_WMA2)->Format.nAvgBytesPerSec * 8;
        p_fmt->audio.i_blockalign = BOXDATA(p_WMA2)->Format.nBlockAlign;
        p_fmt->audio.i_bitspersample = BOXDATA(p_WMA2)->Format.wBitsPerSample;
        p_fmt->i_extra = BOXDATA(p_WMA2)->i_extra;
        if( p_fmt->i_extra > 0 )
        {
            p_fmt->p_extra = malloc( BOXDATA(p_WMA2)->i_extra );
            memcpy( p_fmt->p_extra, BOXDATA(p_WMA2)->p_extra, p_fmt->i_extra );
        }
        return true;
    }
    return false;
}