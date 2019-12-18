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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int i_rate; int /*<<< orphan*/  i_bitspersample; int /*<<< orphan*/  i_blockalign; int /*<<< orphan*/  i_channels; } ;
struct TYPE_5__ {int i_bitrate; int /*<<< orphan*/  p_extra; int /*<<< orphan*/  i_extra; TYPE_1__ audio; int /*<<< orphan*/  i_codec; } ;
typedef  TYPE_2__ es_format_t ;
typedef  int /*<<< orphan*/  bo_t ;

/* Variables and functions */
 int /*<<< orphan*/  bo_add_16le (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bo_add_32le (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bo_add_mem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * box_new (char const*) ; 
 int /*<<< orphan*/  fourcc_to_wf_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bo_t *GetWaveFormatExTag(es_format_t *p_fmt, const char *tag)
{
    bo_t *box = box_new(tag);
    if(!box)
        return NULL;

    uint16_t wFormatTag;
    fourcc_to_wf_tag(p_fmt->i_codec, &wFormatTag);
    bo_add_16le(box, wFormatTag); //wFormatTag
    bo_add_16le(box, p_fmt->audio.i_channels); //nChannels
    bo_add_32le(box, p_fmt->audio.i_rate); //nSamplesPerSec
    bo_add_32le(box, p_fmt->i_bitrate / 8); //nAvgBytesPerSec
    bo_add_16le(box, p_fmt->audio.i_blockalign); //nBlockAlign
    bo_add_16le(box, p_fmt->audio.i_bitspersample);  //wBitsPerSample
    bo_add_16le(box, p_fmt->i_extra); //cbSize

    bo_add_mem(box, p_fmt->i_extra, p_fmt->p_extra);

    return box;
}