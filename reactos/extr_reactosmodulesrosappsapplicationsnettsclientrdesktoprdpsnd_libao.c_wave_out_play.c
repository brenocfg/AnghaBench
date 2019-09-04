#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timeval {long tv_sec; long tv_usec; } ;
struct TYPE_3__ {scalar_t__ p; scalar_t__ end; int /*<<< orphan*/  data; } ;
struct audio_packet {int tick; int /*<<< orphan*/  index; TYPE_1__ s; } ;
struct TYPE_4__ {int dsp_bu; int channels; } ;
typedef  TYPE_1__* STREAM ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*) ; 
 scalar_t__ False ; 
 size_t MAX_QUEUE ; 
 TYPE_2__* This ; 
 int WAVEOUTBUF ; 
 int abs (int) ; 
 int /*<<< orphan*/  ao_play (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 scalar_t__ g_reopened ; 
 int g_samplerate ; 
 int g_samplewidth ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  o_device ; 
 struct audio_packet* packet_queue ; 
 size_t queue_hi ; 
 size_t queue_lo ; 
 int /*<<< orphan*/  rdpsnd_send_completion (unsigned int,int /*<<< orphan*/ ) ; 

void
wave_out_play(void)
{
	struct audio_packet *packet;
	STREAM out;
	char outbuf[WAVEOUTBUF];
	int offset, len, i;
	static long prev_s, prev_us;
	unsigned int duration;
	struct timeval tv;
	int next_tick;

	if (g_reopened)
	{
		g_reopened = False;
		gettimeofday(&tv, NULL);
		prev_s = tv.tv_sec;
		prev_us = tv.tv_usec;
	}

	if (queue_lo == queue_hi)
	{
		This->dsp_bu = 0;
		return;
	}

	packet = &packet_queue[queue_lo];
	out = &packet->s;

	if (((queue_lo + 1) % MAX_QUEUE) != queue_hi)
	{
		next_tick = packet_queue[(queue_lo + 1) % MAX_QUEUE].tick;
	}
	else
	{
		next_tick = (packet->tick + 65535) % 65536;
	}

	len = 0;

	if (g_samplerate == 22050)
	{
		/* Resample to 44100 */
		for (i = 0; (i < ((WAVEOUTBUF / 4) * (3 - g_samplewidth))) && (out->p < out->end);
		     i++)
		{
			/* On a stereo-channel we must make sure that left and right
			   does not get mixed up, so we need to expand the sample-
			   data with channels in mind: 1234 -> 12123434
			   If we have a mono-channel, we can expand the data by simply
			   doubling the sample-data: 1234 -> 11223344 */
			if (This->channels == 2)
				offset = ((i * 2) - (i & 1)) * g_samplewidth;
			else
				offset = (i * 2) * g_samplewidth;

			memcpy(&outbuf[offset], out->p, g_samplewidth);
			memcpy(&outbuf[This->channels * g_samplewidth + offset], out->p, g_samplewidth);

			out->p += g_samplewidth;
			len += 2 * g_samplewidth;
		}
	}
	else
	{
		len = (WAVEOUTBUF > (out->end - out->p)) ? (out->end - out->p) : WAVEOUTBUF;
		memcpy(outbuf, out->p, len);
		out->p += len;
	}

	ao_play(o_device, outbuf, len);

	gettimeofday(&tv, NULL);

	duration = ((tv.tv_sec - prev_s) * 1000000 + (tv.tv_usec - prev_us)) / 1000;

	if (packet->tick > next_tick)
		next_tick += 65536;

	if ((out->p == out->end) || duration > next_tick - packet->tick + 500)
	{
		prev_s = tv.tv_sec;
		prev_us = tv.tv_usec;

		if (abs((next_tick - packet->tick) - duration) > 20)
		{
			DEBUG(("duration: %d, calc: %d, ", duration, next_tick - packet->tick));
			DEBUG(("last: %d, is: %d, should: %d\n", packet->tick,
			       (packet->tick + duration) % 65536, next_tick % 65536));
		}

		/* Until all drivers are using the windows sound-ticks, we need to
		   substract the 50 ticks added later by rdpsnd.c */
		rdpsnd_send_completion(((packet->tick + duration) % 65536) - 50, packet->index);
		free(out->data);
		queue_lo = (queue_lo + 1) % MAX_QUEUE;
	}

	This->dsp_bu = 1;
	return;
}