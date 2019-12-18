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
struct TYPE_3__ {int version; unsigned int channels; unsigned int nb_streams; unsigned int input_sample_rate; int channel_mapping; scalar_t__ gain; scalar_t__ nb_coupled; } ;
typedef  TYPE_1__ OpusHeader ;

/* Variables and functions */

void opus_prepare_header(unsigned channels, unsigned rate, OpusHeader *header)
{
    header->version = 1;
    header->channels = channels;
    header->nb_streams = header->channels;
    header->nb_coupled = 0;
    header->input_sample_rate = rate;
    header->gain = 0; // 0dB
    header->channel_mapping = header->channels > 8 ? 255 :
                              header->channels > 2;
}