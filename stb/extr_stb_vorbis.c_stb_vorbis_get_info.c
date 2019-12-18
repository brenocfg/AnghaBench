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
struct TYPE_5__ {int max_frame_size; int /*<<< orphan*/  temp_memory_required; int /*<<< orphan*/  setup_temp_memory_required; int /*<<< orphan*/  setup_memory_required; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  channels; } ;
typedef  TYPE_1__ stb_vorbis_info ;
struct TYPE_6__ {int blocksize_1; int /*<<< orphan*/  temp_memory_required; int /*<<< orphan*/  setup_temp_memory_required; int /*<<< orphan*/  setup_memory_required; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  channels; } ;
typedef  TYPE_2__ stb_vorbis ;

/* Variables and functions */

stb_vorbis_info stb_vorbis_get_info(stb_vorbis *f)
{
   stb_vorbis_info d;
   d.channels = f->channels;
   d.sample_rate = f->sample_rate;
   d.setup_memory_required = f->setup_memory_required;
   d.setup_temp_memory_required = f->setup_temp_memory_required;
   d.temp_memory_required = f->temp_memory_required;
   d.max_frame_size = f->blocksize_1 >> 1;
   return d;
}