#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_4__ {int p; int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct audio_packet {TYPE_1__ s; int /*<<< orphan*/  index; int /*<<< orphan*/  tick; } ;
struct TYPE_5__ {int /*<<< orphan*/  dsp_bu; } ;
typedef  TYPE_1__* STREAM ;

/* Variables and functions */
 size_t MAX_QUEUE ; 
 TYPE_3__* This ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ) ; 
 struct audio_packet* packet_queue ; 
 size_t queue_hi ; 
 unsigned int queue_lo ; 
 int /*<<< orphan*/  wave_out_play () ; 

void
wave_out_write(STREAM s, uint16 tick, uint8 index)
{
	struct audio_packet *packet = &packet_queue[queue_hi];
	unsigned int next_hi = (queue_hi + 1) % MAX_QUEUE;

	if (next_hi == queue_lo)
	{
		error("No space to queue audio packet\n");
		return;
	}

	queue_hi = next_hi;

	packet->s = *s;
	packet->tick = tick;
	packet->index = index;
	packet->s.p += 4;

	/* we steal the data buffer from s, give it a new one */
	s->data = malloc(s->size);

	if (!This->dsp_bu)
		wave_out_play();
}