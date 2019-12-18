#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int bits; int rate; int /*<<< orphan*/  byte_format; int /*<<< orphan*/  channels; } ;
typedef  TYPE_1__ ao_sample_format ;
struct TYPE_7__ {int wBitsPerSample; int /*<<< orphan*/  nSamplesPerSec; int /*<<< orphan*/  nChannels; } ;
typedef  TYPE_2__ WAVEFORMATEX ;
struct TYPE_8__ {int /*<<< orphan*/  channels; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AO_FMT_LITTLE ; 
 int /*<<< orphan*/  False ; 
 TYPE_5__* This ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  ao_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ao_open_live (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  default_driver ; 
 int /*<<< orphan*/  g_reopened ; 
 int /*<<< orphan*/  g_samplerate ; 
 int g_samplewidth ; 
 int /*<<< orphan*/ * o_device ; 

BOOL
wave_out_set_format(WAVEFORMATEX * pwfx)
{
	ao_sample_format format;

	format.bits = pwfx->wBitsPerSample;
	format.channels = pwfx->nChannels;
	This->channels = pwfx->nChannels;
	format.rate = 44100;
	g_samplerate = pwfx->nSamplesPerSec;
	format.byte_format = AO_FMT_LITTLE;

	g_samplewidth = pwfx->wBitsPerSample / 8;

	if (o_device != NULL)
		ao_close(o_device);

	o_device = ao_open_live(default_driver, &format, NULL);
	if (o_device == NULL)
	{
		return False;
	}

	g_reopened = True;

	return True;
}