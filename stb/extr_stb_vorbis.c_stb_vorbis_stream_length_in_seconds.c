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
struct TYPE_4__ {scalar_t__ sample_rate; } ;
typedef  TYPE_1__ stb_vorbis ;

/* Variables and functions */
 float stb_vorbis_stream_length_in_samples (TYPE_1__*) ; 

float stb_vorbis_stream_length_in_seconds(stb_vorbis *f)
{
   return stb_vorbis_stream_length_in_samples(f) / (float) f->sample_rate;
}